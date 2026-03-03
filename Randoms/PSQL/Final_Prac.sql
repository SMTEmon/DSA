-- 1. 

SELECT title, release_year, (rental_rate * 0.5) + (length * 0.1) + (replacement_cost * 0.2) as Score FROM film ORDER BY Score DESC LIMIT 3;


-- 2.

SELECT c.customer_id, c.first_name, c.last_name, SUM(amount) AS TOTAL FROM customer c join payment p on c.customer_id = p.customer_id GROUP BY c.customer_id  
ORDER BY TOTAL DESC LIMIT 5;


-- 3. 

SELECT film.title, count(distinct customer.customer_id) as cnt from film join inventory on film.film_id = inventory.film_id
        join rental on inventory.inventory_id = rental.inventory_id
        join customer on rental.customer_id = customer.customer_id
        where film.title IN
        (--titles
        SELECT title from film where title like '% %' AND title IN (

            --film rented on more then 2 diff city
            SELECT title from film join inventory on film.film_id = inventory.film_id
            join rental ON inventory.inventory_id = rental.inventory_id
            join customer ON rental.customer_id = customer.customer_id
            join address on address.address_id = customer.address_id
            group by film.title having count(distinct address.city_id) >= 2
        ))
        group by film.title 
        Order by cnt DESC;

-- 4.

SELECT country.country, count(city.city_id) as COUNT
FROM country JOIN city on country.country_id = city.country_id 
where city.city_id IN 
    
    (SELECT city.city_id FROM city

    EXCEPT

    SELECT city.city_id
    FROM city JOIN address ON address.city_id = city.city_id
    JOIN customer ON customer.address_id = address.address_id)
    
GROUP BY country.country_id
ORDER BY COUNT DESC LIMIT 1;

-- 5.
CREATE OR REPLACE PROCEDURE update_customer_email(
    id int,
    new_email VARCHAR(50)
) LANGUAGE plpgsql AS $$
BEGIN
    UPDATE customer SET email = new_email,
    last_update = CURRENT_TIMESTAMP    
    WHERE customer_id = id;
    RAISE NOTICE 'UPDATED ID: %', id;
END;
$$;

-- 6.

DO $$
DECLARE
    id INT;
    has_active BOOLEAN;
    rec RECORD;
BEGIN
    id := 99;
    has_active := false;

    FOR rec IN (SELECT return_date FROM rental WHERE customer_id = id)
    LOOP
        IF rec.return_date IS NULL THEN has_active := true;
        END IF;
    END LOOP;

    IF has_active = false THEN
        RAISE NOTICE 'CUSTOMER has no active rentals';
    ELSIF has_active = true THEN
        RAISE NOTICE 'CUSTOMER has active rentals';
    END IF;
END;
$$;




-- Loops and Records 



-- 7. "Write an anonymous block to show all films with a replacement cost greater than 28.00."
DO $$
DECLARE 
    r RECORD;
BEGIN
    FOR r IN (SELECT * from film where replacement_cost >28.00)
    LOOP
        RAISE NOTICE 'Film % , Cost %', r.title, r.replacement_cost;
    END LOOP;
END;
$$;


-- 8.
 
DO $$
DECLARE 
    ID int;
    startDate TIMESTAMP;
    total NUMERIC;
BEGIN
    ID := 1;
    startDate := '2025-08-19';

    SELECT SUM(amount) INTO total FROM payment WHERE customer_id = id AND payment_date >= startDate;

    RAISE NOTICE 'TOTAL: %', total;
END;
$$;

-- 9. "Create a function that prints customers who did not rent any film in the last N days..."
CREATE OR REPLACE FUNCTION inactiveCustomer(
    N_days INT
)
RETURNS VOID
LANGUAGE plpgsql
AS $$
DECLARE
    rec RECORD;
    cutoff_date TIMESTAMP;
BEGIN
    cutoff_date := CURRENT_DATE - (N_days * INTERVAL '1 day');

    RAISE NOTICE 'Looking for customer who hav''t rented since %', cutoff_date;


    FOR rec in (
        SELECT (c.first_name || ' ' || c.last_name) as full_name from rental r join customer c ON r.customer_id = c.customer_id EXCEPT 
        SELECT (c.first_name || ' ' || c.last_name) as full_name from rental r join customer c ON r.customer_id = c.customer_id where r.rental_date >= cutoff_date
    )

    LOOP 
        RAISE NOTICE 'CUSTOMER: %', rec.full_name;
    END LOOP;
END;
$$;


-- 10.

DO $$
DECLARE 
    recStore RECORD;
    recCus RECORD;
    total NUMERIC;
    per NUMERIC;
    full_name VARCHAR;
BEGIN
    for recStore in (SELECT store_id FROM store)
    LOOP
        SELECT SUM(amount) INTO total 
            FROM payment p JOIN staff s ON p.staff_id = s.staff_id
            JOIN store ON s.store_id = store.store_id 
            WHERE recStore.store_id = store.store_id; 

        FOR recCus in (SELECT customer_id from payment)
        LOOP
            SELECT (c.first_name || ' ' || c.last_name), (SUM(p.amount) / total * 100) INTO full_name, per FROM payment p JOIN customer c ON c.customer_id = p.customer_id 
            WHERE c.store_id = recStore.store_id AND recCus.customer_id = p.customer_id GROUP BY c.customer_id;

            RAISE NOTICE 'NAME: %, STORE ID: %, PER:%', full_name, recStore.store_id, per;
        END LOOP;
    END LOOP;
END;
$$;