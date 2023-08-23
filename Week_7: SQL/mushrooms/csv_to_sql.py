import csv
import cs50


db = cs50.SQL("sqlite:///mushrooms.db")

with open("mushrooms.csv","r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        #This will enter details for mushroom_name
        db.execute("INSERT INTO mushroom_names(mushroom_name) VALUES (?)",row["Name"])
        #This will enter details for mushroom_rarity
        db.execute("INSERT INTO mushroom_rarity(mushroom_id,mushroom_location,mushroom_rarity) VALUES (?,?,?)",row["ID"],row["Continent"],row["Rarity"])
        #This will enter details for mushroom_edibility
        db.execute("INSERT INTO mushroom_edibility(mushroom_id,mushroom_toxicity,mushroom_edibility) VALUES (?,?,?)",row["ID"],row["Toxicity"],row["Edibility"])