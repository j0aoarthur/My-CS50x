SELECT title FROM movies WHERE id IN
(SELECT movie_id FROM stars WHERE person_id IN
(SELECT people.id FROM people WHERE name LIKE 'Johnny Depp')
INTERSECT
SELECT movie_id FROM stars WHERE person_id IN
(SELECT people.id FROM people WHERE name LIKE 'Helena Bonham Carter'));