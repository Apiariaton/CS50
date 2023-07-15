import csv
import cs50
#from cs50 import SQL
#Plan: create a table for students, create a table for heads of houses and houses and a table which connects the student with their house
#Do this using SQL

db = cs50.SQL("sqlite:///roster.db")
houses = set()
house_index = dict()
starting_index = 1

with open("students.csv","r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        update_students_only_table = db.execute("INSERT INTO students(student_name) VALUES (:student_n);", student_n = row["student_name"])
        if row["house"] not in houses:
            update_houses_only_table = db.execute("INSERT INTO houses(house_name,house_head) VALUES (?,?);",row["house"],row["head"])
            houses.add(row["house"])
            house_index[row["house"]] = starting_index
            starting_index += 1
        update_students_houses_table = db.execute("INSERT INTO students_houses(student_id,house_id) VALUES (?,?);", row["id"],house_index[row["house"]])



#Then, using the csv library, on a row by row basis, and skipping the first row, execute the relevant database queries
#Relevant query: Insert Student into Student Table: an ID will be created as a primary key.
# Check whether house exists in the set of added houses.
# If not, Insert House into House Table, together with House Head.
# Create a third query, which inserts the key from Student ID, and inserts the House Key into the third "Connector" table.
