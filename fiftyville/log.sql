-- Keep a log of any SQL queries you execute as you solve the mystery.

--To get crime scene report id of the theft which is 295
SELECT * FROM crime_scene_reports WHERE year=2021 AND month=7 AND day=28 AND street='Humphrey Street';

--To get the interviews from the witnesses of the theft
SELECT * FROM interviews WHERE transcript LIKE '%bakery%' AND year=2021 AND month=7 AND day=28;

/* 1) Drove away after 10 MINUTES of theft in CAR. Bakery security footage.
   2) Earlier same morning(July 28, 2021) WITHDREW CASH from ATM on LEGGETT STREET
   3) After leaving bakery talked to someone for LESS THAN A MINUTE about leaving tomorrow
      with the EARLIEST flight and TOLD THEM TO BOOK THE FLIGHT.
   4) Someone came in bakery suspiciously whispering in a phone for HALF AN HOUR, and NEVER BOUGHT ANYTHING
*/

--To get list of cars leaving and entering bakery parking lot on day of theft
SELECT * FROM bakery_security_logs WHERE year=2021 AND month=7 AND day=28;

--To get list of phone calls made that day that were less than a minute long
SELECT * FROM phone_calls WHERE year=2021 AND month=7 AND day=28 AND duration<60;

--To get list of people who withdrews cash from atm on Humphery Lane that day
SELECT people.name, people.phone_number FROM atm_transactions AS tra
JOIN bank_accounts AS acc ON acc.account_number = tra.account_number
JOIN people ON people.id = acc.person_id
WHERE year=2021 AND month=7 AND day=28 AND atm_location = 'Humphrey Lane' AND transaction_type = 'withdraw';

--To get people who withdrew money + called that day
SELECT * FROM people WHERE phone_number IN

(SELECT caller FROM phone_calls WHERE year=2021 AND month=7 AND day=28 AND duration<60

INTERSECT

SELECT people.phone_number FROM atm_transactions AS tra
JOIN bank_accounts AS acc ON acc.account_number = tra.account_number
JOIN people ON people.id = acc.person_id
WHERE year=2021 AND month=7 AND day=28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw');

/*
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+---------+----------------+-----------------+---------------+
*/

/*4 liscence plates are sus, suspects are: Bruce, Taylor, Diana*/
SELECT * FROM bakery_security_logs WHERE year=2021 AND month=7 AND day=28 AND license_plate IN
(SELECT license_plate FROM people WHERE phone_number IN

(SELECT caller FROM phone_calls WHERE year=2021 AND month=7 AND day=28 AND duration<60

INTERSECT

SELECT people.phone_number FROM atm_transactions AS tra
JOIN bank_accounts AS acc ON acc.account_number = tra.account_number
JOIN people ON people.id = acc.person_id
WHERE year=2021 AND month=7 AND day=28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')
);

--We get to know that flight id 36 was the earliest flight on 29th July, 2021
SELECT flights.id, flights.hour, flights.destination_airport_id
FROM flights JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = 2021 AND month = 7 AND day = 29 AND flights.origin_airport_id = 8;

--Flight number 36 was headed to LaGuardia Airport in New York City
SELECT * from airports WHERE id = 4;

--Diana is no longer a suspect
SELECT * FROM passengers JOIN people ON passengers.passport_number = people.passport_number
WHERE flight_id = 36;

--Looks like suspect is Bruce when you look at bakery security locks

--Checking who Brice called
select * from phone_calls where caller
=(select phone_number from people WHERE name = 'Bruce') AND duration < 60;

--Seems like the accomplice is Robin
select * from people where phone_number='(375) 555-8161';