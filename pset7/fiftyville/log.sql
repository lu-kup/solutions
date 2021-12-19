-- Keep a log of any SQL queries you execute as you solve the mystery.

--Check the relevant crime scene report
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = "Chamberlin Street";

SELECT transcript, id
FROM interviews
WHERE month = 7 AND day = 28;
--Last interview notes that the thief was planning to take first flight out of Fiftyville the next day

--Check flight times out of Fiftyville the next day, according to interviews
SELECT destination_airport_id, hour, minute
FROM flights
WHERE month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY hour ASC, minute ASC;

--Check the destinations of those flights
SELECT city, hour, minute
FROM flights JOIN airports ON flights.destination_airport_id = airports.id
WHERE month = 7 AND day = 29
ORDER BY hour ASC, minute ASC;
-- First flight the next day was to London


--Suspect phone numbers, according to interviews
SELECT caller, receiver, duration
FROM phone_calls
WHERE month = 7 AND day = 28 AND duration <= 60;

--Suspect licence plates, according to interviews
SELECT license_plate, activity
FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour = 10 AND minute >15 AND minute <= 25 AND activity = "exit";

--Suspect passengers, according to interviews
SELECT passport_number
FROM passengers
WHERE flight_id IN
(
SELECT id FROM flights
WHERE month = 7 AND day = 29
AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
AND destination_airport_id = (SELECT id FROM airports WHERE city = "London")
);


--Finding the thief from 'people' using lists generated above

--Suspects by phone number
SELECT name FROM people
WHERE phone_number IN
(
SELECT caller
FROM phone_calls
WHERE month = 7 AND day = 28 AND duration <= 60
);

--Suspects by passport number
SELECT name FROM people
WHERE passport_number IN
(
SELECT passport_number
FROM passengers
WHERE flight_id IN
(
SELECT id FROM flights
WHERE month = 7 AND day = 29
--AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
AND destination_airport_id = (SELECT id FROM airports WHERE city = "London")
)
);

-- Suspects by  license_plate
SELECT name FROM people
WHERE license_plate IN
(
SELECT license_plate
FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour = 10 --AND minute >15 AND minute <= 25
AND activity = "exit"
);

-- Suspects by bank account
SELECT name
FROM people
WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN
(
SELECT account_number
FROM atm_transactions
WHERE atm_location = "Fifer Street" AND month = 7 AND day = 28 AND transaction_type = "withdraw"
)
);

-- Ernest is the only one that appears in all lists, he is the thief

--We can find out the accomplice by checking who Ernest talked to in the phone call

SELECT name
FROM people
WHERE phone_number =
(
SELECT receiver
FROM phone_calls
WHERE month = 7 AND day = 28 AND caller = (SELECT phone_number FROM people WHERE name = "Ernest")
);
-- The results show that accomplice is Berthold
