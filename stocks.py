import math
import csv
import uuid
import pandas as pd
import requests


"""
# Function to set the bank's starting balance
# Function to add a new customer
# Function to check whether the customer is in the list of existing customers
# Function to invest in stocks by checking against customer list
# Function to withdraw money that was invested, checking that it is less than the total money invested by the customer

"""

class Trading_Platform:
    def __init__(self,balance,customer_number,acceptable_currencies=["USD", "GBP","EUR"],max_trading_allowance = "£30,000"):
        self.trading_balance = balance
        self.customer_numbers = customer_number
        self.transaction_number = 0
        self.transactional_history = {}
        self._customer_number = 0

    @property
    def transaction_number(self):
        return self._transaction_number

    @transaction_number.setter
    def transaction_number(self, value):
        self._transaction_number = 0


    @property
    def balance(self):
        return self._trading_balance

    @balance.setter
    def balance(self,value):
        if 30000 < value:
            self._trading_balance = value
            self.trading_balance = self._trading_balance
            self.transactional_history[self._transaction_number] = [self._trading_balance,"Starting balance"]
            self._transaction_number += 1
        else:
            print("Value insufficient to start trading platform...")
            raise ValueError

    @property
    def customer_number(self):
        with open(f"{name_of_trading_platform}_customer_list.csv") as file:
            reader = csv.reader(file)
            for row in reader:
                if len(row) >= 6:
                    if row[0] == "Unique_ID":
                        self.customer_numbers = self._customer_number
                        return self._customer_number #removed suffixed hyphen
        with open(f"{name_of_trading_platform}_customer_list.csv","a") as file:
            writer = csv.DictWriter(file, fieldnames = ["unique_ID","first_name","last_name","username","password","current_investment"])
            writer.writerow({"unique_ID":"Unique_ID","first_name":"First_Name","last_name":"Last_Name","username":"Username","password":"Password","current_investment":"Current_total_invested"})
        self.customer_numbers = self._customer_number
        return self._customer_number #removed suffixed hyphen

    @customer_number.setter
    def customer_number(self,value):
        self.customer_number = 0
        self._customer_number = 0


    def add_customer(self,first_n,last_n,username):
        with open(f"{name_of_trading_platform}_customer_list.csv") as file:
            customer_datalist = csv.reader(file)
            rows = []
            for row in customer_datalist:
                if len(row) == 6:
                    if (row[1] == first_n and row[2] == last_n and row[3] == username) or (row[2] == last_n and row[3] == username):
                        print("A user with this name already exists: try logging in with your existing details or click to indicate you forgot password.")
                        return False
                    elif row[3] == username:
                        print("A user already exists with this username... Please devise a new username.")
                        return False
                password = ""
            while (len(password) < 8):
                password = input("Please enter password, which is 8 character or more: ")
                if (len(password) < 8):
                    print("Password too short")
            unique_id = str(uuid.uuid4())
            unique_id = unique_id[0:8]
            customer_info = {"unique_ID":unique_id,"first_name":first_n,"last_name":last_n,"username":username, "password":password, "current_investment":"£0"}
        with open(f"{name_of_trading_platform}_customer_list.csv", "a") as file:
            add_new_customer = csv.DictWriter(file,fieldnames=["unique_ID","first_name","last_name","username","password","current_investment"])
            add_new_customer.writerow(customer_info)


    def invest_money(self,username):
        sum = input("How much would you like to invest? ")
        sum = int(sum)
        self.trading_balance += sum
        df = pd.read_csv(f"{name_of_trading_platform}_customer_list.csv")
        print(df)
        correct_row_index = df.loc[df['Username']== username].index.item()
        correct_column_to_update = 'Current_total_invested'
        value = df.loc[correct_row_index,correct_column_to_update]
        sum_invested = "£" + str(int(value[1:]) + sum)
        df.loc[correct_row_index,correct_column_to_update] = sum_invested
        df.to_csv(f"{name_of_trading_platform}_customer_list.csv",index=False)

"""






with open("phonebook.csv","a") as file:
    writer = csv.DictWriter(file,fieldnames =["name","number"])
    for i in range(100):
        name = names.get_full_name()
        number = "0"
        while len(number) < 10:
            number += str(random.randint(0,9))
        writer.writerow({"name":name,"number":number})
"""

name_of_trading_platform = input("Enter your trading platform name: ")
globals()[name_of_trading_platform] = Trading_Platform(balance = 20000, customer_number = 0)
globals()[name_of_trading_platform].customer_number

"""
for i in range(5):
    my_name = input("Enter your first name: ")
    my_l_name = input("Enter your second name: ")
    my_username = input("Enter your desired username: ")
    globals()[name_of_trading_platform].add_customer(my_name,my_l_name,my_username)
"""

globals()[name_of_trading_platform].invest_money("TravinNoir")

print(globals()[name_of_trading_platform].transaction_number)
