import csv
import names
import random

with open("phonebook.csv","a") as file:
    writer = csv.DictWriter(file,fieldnames =["name","number"])
    for i in range(100):
        name = names.get_full_name()
        number = "0"
        while len(number) < 10:
            number += str(random.randint(0,9))
        writer.writerow({"name":name,"number":number})

