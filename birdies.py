import csv
from cs50 import SQL


db = SQL("sqlite:///favorites.db")


bird = input("Bird for which you would like to see quantity...")

rows = db.execute("SELECT COUNT (*) AS n FROM birdies WHERE 'Bird Species' = ?;",bird)

row = rows[0]

print(row["n"])


def main():
    with open(f"birdies.csv","r") as file:
        reader = csv.DictReader(file)
        count = {}
        for row in reader:
            if row["Bird Species"] not in count:
                count[row["Bird Species"]] = 1
            else:
               count[row["Bird Species"]] += 1
        def get_value(bird_species):
            return count[bird_species]
        for entry in sorted(count,key= lambda Bird_Species: count[Bird_Species] ,reverse= True):
            print(f'{entry}:{count[entry]}')


main()