import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import date
import time

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":

        #Check if input is valid
        quote = request.form.get("quote")
        shares = request.form.get("shares")
        stinfo = lookup(quote)

        if not stinfo:
            return apology("STOCK NOT FOUND")

        try:
            shares = int(shares)
        except ValueError:
             return apology("INVALID NUMBER OF SHARES")

        if shares <= 0:
            return apology("INVALID NUMBER OF SHARES")

        #Identify current user
        current_user = session["user_id"]

        #Check if user has enough cash to buy the shares
        cur_price = stinfo["price"]
        moni = cur_price * shares

        moni_list = db.execute("SELECT cash FROM users WHERE username=?", current_user)
        moni_in_hand1 = moni_list[0]
        moni_in_hand = moni_in_hand1["cash"]

        if moni_in_hand < moni:
            return apology("YOU BROKE")

        else:
            #Update Ownership to reflect purchase: Create new field in table / update existing field
            alr_own_or_not = db.execute("SELECT amount FROM ownership WHERE user_id=? AND stock_quote=?", current_user, quote)

            if len(alr_own_or_not) == 0:
                add_new_row = db.execute("INSERT INTO ownership (user_id, stock_quote, amount) VALUES(?, ?, ?)", current_user, quote, shares)
            else:
                update_existing_row = ("UPDATE ownership SET amount=amount+? WHERE user_id=? AND stock_quote=?", shares, current_user, quote)

            #Update History to show the new transaction
            today = date.today()
            seconds = time.time()
            local_time = time.ctime(seconds)

            update_history = db.execute("INSERT INTO history (user_id, stock_quote, act, date, time, amount) VALUES(?, ?, ?, ?, ?, ?)", current_user, quote, "buy", today, local_time, shares)

            #Update user's cash
            update_cash = db.execute("UPDATE users SET cash = cash-? WHERE username=?", moni, current_user)

            #Redirect to index
            return redirect("/")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":
        symbol = request.form.get("quote")
        stinfo = lookup(symbol)

        if stinfo:
            name = stinfo["name"]
            price = usd(stinfo["price"])
            sym = stinfo["symbol"]

            return render_template("quoted.html", name=name, price=price, sym=sym)

        else:
            return apology("stock not found", 403)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Shows registration page
    if request.method == "GET":
        return render_template("register.html")

    # TODO: Implement POST:
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password was confirmed
        elif not request.form.get("conf_password"):
            return apology("please confirm password", 403)

        # Ensure username is not taken
        un = request.form.get("username")
        rows = db.execute("SELECT * FROM users WHERE username = ?", un)

        if len(rows) != 0:
            return apology("username taken", 403)

        # Ensure passwords match
        pswd = request.form.get("password")
        conf = request.form.get("conf_password")

        if pswd != conf:
            return apology("passwords dont match", 403)

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", un, generate_password_hash(pswd))

        #Log User In
        session["user_id"] = un

        return redirect("/")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
