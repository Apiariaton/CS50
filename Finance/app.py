import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, validate

from datetime import datetime


# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Libra\fry to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response



#Add transaction successful message for successful purchase/sale
@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    print(session["user_id"])
    #Listed dictionary
    stock_info = db.execute("SELECT * FROM stock_portfolio WHERE id = ?", session["user_id"])
    print(stock_info)

    #What do we need to happen? Take the symbol value and quantity value from stock info which is a list of dictionaries
    #Then use these to compute total stock price per symbol and allocate this as a value to
    #the individual_total_stock_value dictionary

    individual_total_stock_value = dict()
    value_of_all_stock = 0
    for i in stock_info:
        print(i)
        individual_total_stock_value[i['stock_name']] = (lookup((i['stock_name']))['price']) * i['stock_quantity']
        value_of_all_stock += individual_total_stock_value[i['stock_name']]

    print(value_of_all_stock)
    total_cash_balance = db.execute("SELECT cash FROM users WHERE id = ?",session["user_id"])
    total_cash_balance = float(total_cash_balance[0]['cash'])

    count = 1

    if count == 0:
        return render_template("index.html",message="No stocks purchased...")
    else:
        return render_template("index.html",stock_info = stock_info, value_of_all_stock = value_of_all_stock, individual_total_stock_value = individual_total_stock_value,  total_cash_balance = total_cash_balance)


#To Do - find a way to convert user_id to username or to use username
#user_id = users[user_id]


#Parse sqlite3 return values


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    elif request.method == "POST":
        #Obtain values for symbol and quantity
        symbol = request.form.get("symbol")
        quantity = request.form.get("quantity")
        quantity = int(quantity)

        if not symbol:
             return apology("Please enter a stock symbol...")

        stock_traits = lookup(symbol)
        #Stock with this name does not exist
        if stock_traits == None:
            return apology("No stock was found with this symbol...")
        if quantity <= 0 or isinstance(quantity,int) == False:
            return apology("Please enter a stock quantity greater than 0, which is a whole number...")

        remaining_balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        for i in remaining_balance:
            print(i)
        if quantity * stock_traits["price"] > float(remaining_balance[0]['cash']):
            return apology("The proposed transaction exceeds your current balance...")
        else:
            # Get current financial balance for user
            old_balance = db.execute("SELECT cash FROM users WHERE id = ?",session["user_id"])
            old_balance = float(old_balance[0]['cash'])
            # Get current no. stocks for stock symbol - issue is the most recent stock quantity has not been found
            cumulative_stock_total = db.execute("SELECT stock_quantity FROM stock_portfolio WHERE id = ? AND stock_name = ?;",session["user_id"],stock_traits["symbol"])

            print(f"CSD before new stock number added: {cumulative_stock_total}")

            #If stock symbol does not exist, cumulative_stock_total = 0
            if not cumulative_stock_total:
                cumulative_stock_total = 0
            else:
                cumulative_stock_total = int(cumulative_stock_total[0]['stock_quantity'])
                print(f"CST: {cumulative_stock_total}")


            # Get price of transaction
            deduction = quantity * stock_traits["price"]
            new_cumulative_stock_total = cumulative_stock_total + quantity
            # Change value of financial balance, subtracting transaction
            new_balance = old_balance - deduction
            # Get time/date of transaction
            now = datetime.now()
            transaction_time = now.strftime("%H %M  %S %D/%M/%Y")

            # Add new row to transaction history
            db.execute("INSERT INTO transaction_history(id, cash, share_name, share_quantity_change,cumulative_stock_quantity,transaction_date) VALUES(?,?,?,?,?,?);",session["user_id"], new_balance, stock_traits["symbol"], quantity, new_cumulative_stock_total,transaction_time)

            # Update row on stock_portfolio table
            count_of_stock_requested_for_purchase = db.execute("SELECT COUNT(id) FROM stock_portfolio WHERE id = ? AND stock_name = ?;",session["user_id"], stock_traits["symbol"])
            print(count_of_stock_requested_for_purchase)
            count_of_stock_requested_for_purchase = int(str(count_of_stock_requested_for_purchase[0]['COUNT(id)']))

            if ((count_of_stock_requested_for_purchase) > 0):
                db.execute("UPDATE stock_portfolio SET stock_quantity = ?, price_per_stock = ?, total_price_of_all_stock = ? WHERE id = ? AND stock_name = ?;", new_cumulative_stock_total,stock_traits["price"],deduction, session["user_id"],stock_traits["symbol"])
            else: #Insert row as no stock purchased
                db.execute("INSERT INTO stock_portfolio (id,stock_name,stock_quantity,price_per_stock,total_price_of_all_stock) VALUES(?,?,?,?,?);",session["user_id"], stock_traits["symbol"], new_cumulative_stock_total,stock_traits["price"],deduction)

            #Update data for users table
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])

            return redirect("/")




@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transaction_history_tb = db.execute("SELECT * FROM transaction_history WHERE id = ? ORDER BY transaction_date ASC", session["user_id"])
    return render_template("history.html",transaction_history_table = transaction_history_tb)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        symbol = request.form.get("symbol")
        stock_traits = lookup(symbol)
        if stock_traits == None:
            return apology("The symbol not found within the IEX database...")
        else:
            return render_template("quoted.html",message="  found...",stock_traits = stock_traits)



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    elif request.method == "POST":
        #Get values for username, confirmation and password
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        database = db.execute("SELECT username FROM users;")

        #Error handling - add function to screen out harmful expressions
        if not username:
            return render_template("apology.html", top="The username provided is blank: please provide a full username...")
        if not password:
            return render_template("apology.html", top="The password provided is blank: please provide a full password...")
        if not confirmation:
            return render_template("apology.html", top="The confirmation provided is blank: please re-type your password below...")
        if username in database:
            return render_template("apology.html", top="A user with this name already exists...") #Potential to add forgot password feature
        if password != confirmation:
            return render_template("apology.html", top="The password and confirmation do not match: please check both are correctly typed...")
        if validate(password) == False:
            return render_template("apology.html", top="Please use a password, 8 characters or more in length, which includes a character, number and special character...")

        #Hash password


        #Add to finance db
        hashed_password = generate_password_hash(password)
        db.execute("INSERT INTO users(username,hash) VALUES (?, ?)",username,hashed_password)

        #Provide message to confirm that applicant has successfully registered: they are then redirected to login page with the message -> You have successfully registered
        return render_template("login.html",message="Congratulations, you have successfully registered for an account...")






@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        return render_template("sell.html")
    elif request.method == "POST":
        # Initialise values
        symbol = request.form.get("symbol")
        quantity = request.form.get("quantity")
        quantity = int(quantity)

        # Guard against malicious request
        if symbol.isalpha() == False:
            return apology("Stock symbol field contains characters which are non-alphabetical")

        stock_traits = lookup(symbol)
        #Cases where an error message is raised:
        #   Stock number not a number; the stock number is not an integer
        if isinstance(quantity,int) == False:
            return apology("Stock number is not a number...")
        #   Stock number lower than or equal to 0
        if quantity <= 0:
            return apology("Please enter a number greater than 0, which does not exceed the number of stocks owned...")
        #   Stock symbol does not exist
        if stock_traits == None:
            return apology("A stock with this name was not found...")
        #   The stock number exceeds that which is owned by the user
        quantity_of_this_stock_owned = db.execute("SELECT stock_quantity FROM stock_portfolio WHERE id = ? AND stock_name = ?", session["user_id"],stock_traits["symbol"])
        quantity_of_this_stock_owned = quantity_of_this_stock_owned[0]['stock_quantity']
        if quantity_of_this_stock_owned == None:
            return apology("The number of stock to be sold exceeds that which the user owns...")
        #   The user owns no such stock
        if quantity_of_this_stock_owned < quantity:
            return apology("No such stock is owned...")
        if not symbol:
            return apology("Please enter a value for symbol, which includes only alphabetical characters...")
        #   Stock symbol field is blank
        if not quantity:
            return apology("Please enter a value for stock number, which is an integer greater than 0 and lower or equal to the number of stock owned...")
        #   Stock number field is blank

        #SQL Code
        # Update cash value for users in response to the sale of the stock
        # Retrieve cash balance value
        cash_balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash_balance = cash_balance[0]['cash']
        new_balance = cash_balance + (quantity * stock_traits['price'])
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])

        current_no_stock = db.execute("SELECT stock_quantity FROM stock_portfolio WHERE id = ? AND stock_name = ?", session["user_id"], stock_traits["symbol"])
        current_no_stock = current_no_stock[0]['stock_quantity']

        new_stock_quantity = 0

        if current_no_stock == quantity:
            db.execute("DELETE FROM stock_portfolio WHERE id = ? AND stock_name = ?", session["user_id"],stock_traits["symbol"])
        else:
            new_stock_quantity = current_no_stock - quantity
            db.execute("UPDATE stock_portfolio SET stock_quantity = ? WHERE id = ? AND stock_name = ?", new_stock_quantity, session["user_id"], stock_traits["symbol"])
        # If the quantity equals that owned by the user, db.execute("DELETE FROM stock_portfolio WHERE id = ? AND symbol = ?,")


        #Redirect to index
        return redirect("/")


