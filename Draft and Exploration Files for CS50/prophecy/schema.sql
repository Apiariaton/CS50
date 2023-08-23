-- The first table will be the table for students: Primary Key NOT NULL and Student ID; Student Name
CREATE TABLE students(
    student_id INTEGER,
    student_name TEXT NOT NULL,
    PRIMARY KEY(student_id)
);


-- The second table will be the table for houses: Primary Key Not NULL House Name, House ID and House Head
CREATE TABLE houses (
    house_id INTEGER,
    house_name TEXT NOT NULL,
    house_head TEXT NOT NULL,
    PRIMARY KEY(house_id)
);



--The third table will be the table for the Connector Table: Foreign Keys for the Student ID and for the House ID
CREATE TABLE students_houses (
    student_id INTEGER,
    house_id INTEGER,
    FOREIGN KEY (student_id) REFERENCES students(student_id),
    FOREIGN KEY (house_id) REFERENCES houses(house_id)
);