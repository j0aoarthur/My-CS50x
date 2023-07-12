
-------- DRAFT -------------

SELECT * FROM crime_scene_reports
WHERE day = '28' AND month = '7' AND year = '2021' AND street LIKE 'Humphrey Street';
295 is our theft at 10:15am

-- | 295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the
-- Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at
-- the time – each of their interview transcripts mentions the bakery. |


SELECT * FROM interviews WHERE day = '28' AND month = '7' AND year = '2021';

-- | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

-- GET eugene license_plate to get time he arrived and match with atm logs
SELECT * FROM people WHERE name LIKE 'eugene%';
-- license_plate = 47592FJ

-- CHECK ARRIVAL OF EUGENE IN THE BAKERY
SELECT * FROM bakery_security_logs WHERE license_plate = (SELECT license_plate FROM people WHERE name LIKE 'Eugene');

-- 10 minutes after 10:15 the thief left 10:25
SELECT * FROM bakery_security_logs JOIN people ON license_plate
WHERE day = '28' AND month = '7' AND year = '2021' AND hour = '10';
-- plates that left

-- check lisence plates that left the bakery in the time frame ruth said
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = '28' AND month = '7' AND year = '2021' AND hour = '10' AND minute <= 25);

-- check atm day,month,year, withdraw money, one of this account_numbers is the thief could get name of him
SELECT * FROM atm_transactions WHERE atm_location LIKE 'Humphrey%' AND day = '28' AND month = '7' AND year = '2021' and transaction_type = 'withdraw'

-- check first flight of 29 july 2021
SELECT * FROM flights WHERE day = '29' AND month = '7' AND year = '2021' AND origin_airport_id = '8' ORDER by hour LIMIT 1;



destination_airport of first flight of 29 = 4 and flight id = 36

SELECT * FROM airports WHERE id = '4';
-- DESTINATION CITY NEW YORK LA GUARDIA AIRPORT


-- ID AIRPORT FIFTHYVILLE
SELECT id FROM airports WHERE city LIKE 'Fiftyville';
id = 8


-- Check call made as the thief was leaving the bakery with the numbers that were found in the passengers of the flight
SELECT caller,receiver,duration FROM phone_calls
WHERE caller IN (SELECT phone_number FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE passport_number IN
(SELECT passport_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE day = '28' AND month = '7' AND year = '2021' AND hour = '10' AND minute LIKE '2%'))
AND flight_id = '36')) AND day = '28' AND month = '7' AND year = '2021' AND duration < 60;

Kelsey called to (892) 555-8872 and (717) 555-1342  less than a minute
Sofia called to (996) 555-8899 less than a minute

-- check when thiefs arrived in the bakery
SELECT * FROM bakery_security_logs WHERE license_plate IN
(SELECT license_plate FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE passport_number IN
(SELECT passport_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE day = '28' AND month = '7' AND year = '2021' AND hour = '10'))
AND flight_id = '36'));

-- check atm transactions, since they dont have a account, lets check if they accessed their friends account



-- first get the number of the receivers

-- get account_number by phone_number passing through id and person_id
SELECT account_number FROM bank_accounts WHERE person_id IN
(SELECT id FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE caller IN

--

-- CHECK file OF FRIEND AND PHONE NUMBER
SELECT * FROM people WHERE id = (SELECT person_id FROM bank_accounts WHERE account_number = '');

--------------------------------------- END DRAFT ----------------------------------------------------

 -------- SOLUTION ---------

-------- FINAL QUERY -----------


-- 1º -------------- LOCATION IS LA GUARDIA - NEW YORK

-- Origin airport id

    SELECT id FROM airports WHERE city LIKE 'Fiftyville';
    -- 8

-- FIND THE FIRST FLIGHT ON 29TH JULY AND ITS ID

    SELECT id FROM flights WHERE day = '29' AND month = '7' AND year = '2021'
    AND origin_airport_id = (SELECT id FROM airports WHERE city LIKE 'Fiftyville')
    ORDER by hour LIMIT 1;

-- FIND THE destination airport

    SELECT city FROM airports
    WHERE id = (SELECT destination_airport_id FROM flights WHERE day = '29' AND month = '7' AND year = '2021'
    AND origin_airport_id = (SELECT id FROM airports WHERE city LIKE 'Fiftyville')
    ORDER by hour LIMIT 1);
    -- NEW YORK CITY

-- 2º -------------- THIEF IS BRUCE

-- Check who left the bakery at the time said by Ruth

    SELECT * FROM people WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE day = '28' AND month = '7' AND year = '2021' AND hour = '10' AND minute <= 25);

-- Check file of the people that were in the bakery and went on the first flight the day after the theft
    SELECT * FROM people WHERE passport_number IN
    (SELECT passport_number FROM passengers WHERE passport_number IN
    (SELECT passport_number FROM people WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE day = '28' AND month = '7' AND year = '2021' AND hour = '10' AND minute <= 25))
    AND flight_id = '36');

-- check who called someone on the day and was less then a minute

    SELECT account_number,name,phone_number FROM bank_accounts
    JOIN people ON person_id = people.id
    JOIN phone_calls ON caller = phone_number
    WHERE person_id IN
    (SELECT id FROM people WHERE passport_number IN
    (SELECT passport_number FROM passengers WHERE passport_number IN
    (SELECT passport_number FROM people WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE day = '28' AND month = '7' AND year = '2021' AND hour = '10' AND minute <= 25))
    AND flight_id = '36')) AND day = '28' AND month = '7' and year = '2021' AND duration < 60;

    -- Bruce | (367) 555-5533 | (375) 555-8161 | 49610011

-- BRUCE IS THE THIEF

-- Check who's the accomplice

    SELECT * FROM people WHERE phone_number =
    (SELECT receiver FROM bank_accounts
    JOIN people ON person_id = people.id
    JOIN phone_calls ON caller = phone_number
    WHERE person_id IN
    (SELECT id FROM people WHERE passport_number IN
    (SELECT passport_number FROM passengers WHERE passport_number IN
    (SELECT passport_number FROM people WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE day = '28' AND month = '7' AND year = '2021' AND hour = '10' AND minute <= 25))
    AND flight_id = '36')) AND day = '28' AND month = '7' and year = '2021' AND duration < 60);

-- ROBIN IS THE ACCOMPLICE