from cs50 import get_float


def main():
    dollars = get_dollars()
    cents = int(dollars * 100.00)

    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    nickles = calculate_nickles(cents)
    cents = cents - nickles * 5

    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    coins = quarters + dimes + nickles + pennies
    print(coins)


def get_dollars():
    while(True):
        dollars = get_float("How many dollars? ")
        if dollars >= 0:
            break
    return dollars


def calculate_quarters(cents):

    i = 0
    while(True):
        if cents < 25:
            return i

        cents = cents - 25
        i += 1


def calculate_dimes(cents):

    i = 0
    while(True):
        if cents < 10:
            return i

        cents = cents - 10
        i += 1


def calculate_nickles(cents):

    i = 0
    while(True):
        if cents < 5:
            return i

        cents = cents - 5
        i += 1


def calculate_pennies(cents):

    i = 0
    while(True):
        if cents < 1:
            return i

        cents = cents - 1
        i+=1


if __name__ == "__main__":
    main()
