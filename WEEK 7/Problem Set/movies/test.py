from cs50 import SQL


db = SQL("sqlite:///movies.db")

testing = db.execute( """SELECT name FROM people WHERE id IN
                     (SELECT person_id FROM stars WHERE person_id NOT IN
                      (SELECT id FROM people WHERE name LIKE 'Kevin Bacon' AND birth = 1958)
                      AND movie_id IN (SELECT movie_id FROM stars
                        WHERE person_id = (SELECT id FROM people WHERE name LIKE 'Kevin Bacon' AND birth = 1958))) ORDER BY name; """ )

for row in testing:
    print(row)