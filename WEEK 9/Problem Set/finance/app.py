import os
import yfinance as yf

from cs50 import SQL
from flask import Flask, g, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash


from helpers import apology, login_required, usd, get_stock

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd



# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# To make the greet button beside the log out button
@app.before_request
def before_request():
    # Set the 'username' attribute on the global 'g' object
    if session.get('user_id'):
        username = db.execute('SELECT username FROM users WHERE id LIKE ?', session.get('user_id'))
        g.username = username[0]['username']
    else:
        g.username = None

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")



@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == 'POST':

        # Get stock that user wants to buy and standards checks
        stock = request.form.get("stock_ticker", None)
        if stock == None:
            return render_template("quote.html")
        purchase_stock = get_stock(stock)
        purchase_stock['quantity'] = request.form.get("stock_quantity", None)

        # Check if stock exists
        if purchase_stock == None:
            return apology("No stocks found with this name", 404)
        
        # Make math to get the total purchase
        purchase_stock['totalPrice'] = purchase_stock['price'] * float(purchase_stock['quantity'])

        # Get current cash of user
        dictcash_user = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])
        cash_user = dictcash_user[0]['cash']

        # Check if he can afford the stock
        if cash_user < purchase_stock['totalPrice']:
            return apology('You cannot afford this purchase', 403)
        
        # Subtract purchase value from cash
        cash_user -= purchase_stock['totalPrice']
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_user, session['user_id'])

        # Log stock's infos into a log table
        db.execute("INSERT INTO logs (id, companyName, symbol, transactionPrice, quantity, action) VALUES (?,?,?,?,?,?)", 
                   session["user_id"], purchase_stock['name'], 
                    purchase_stock['symbol'], purchase_stock['price'], 
                    purchase_stock['quantity'], 'purchase')
        
        # Update prices to fit us dollar format
        purchase_stock['price'] = usd(purchase_stock['price'])
        purchase_stock['totalPrice'] = usd(purchase_stock['totalPrice'])

        
        return render_template("bought.html", purchase_stock=purchase_stock, currentCash=usd(cash_user))
        

    return render_template("buy.html")










    return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
        username_corner = rows[0]["username"]

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
    """
    USING CS50'S API
    if request.method == 'POST':
        return render_template("quoted.html")
    stock = request.args.get("stock_ticker", "")
    searched_stock = lookup(stock)
    return render_template("quote.html", stocks=searched_stock)
    """

    # USING YFINANCE

    stock = request.args.get("stock_ticker", None)
    if stock == None:
        return render_template("quote.html")

    purchase_stock = get_stock(stock)

    if purchase_stock == None:
        return apology("No stocks found with this name", 404)

    return render_template("quote.html", stocks=purchase_stock, search=request.args.get("stock_ticker", None))


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == 'POST':

        # Get passwords and username inputed
        username = request.form.get("username")
        password = request.form.get("password")
        password_confirmation = request.form.get("password_confirmation")

        # List of all users in the system
        list_users = db.execute("SELECT username FROM users")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 403)

        # Ensure password_confirmation was submitted
        elif not password_confirmation:
            return apology("must type password confirmation", 403)

        elif password != password_confirmation:
            return apology("Verification password does not equal to password", 403)

        # Check if username equals to any other in the system
        elif username in (name_user['username'] for name_user in list_users):
            return apology("Username already taken", 403)

        #Create password_hash
        password_hash = generate_password_hash(password)

        # Save user and hash_password in the database
        db.execute("INSERT INTO users (username, hash) VALUES ( ?, ?)", username, password_hash)

        return redirect("/")

    return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


# CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
#                       username TEXT NOT NULL, hash TEXT NOT NULL,
#                       cash NUMERIC NOT NULL DEFAULT 10000.00);
# CREATE TABLE sqlite_sequence(name,seq);
# CREATE UNIQUE INDEX username ON users (username);

"""
CREATE TABLE logs (
    id INTEGER NOT NULL,
    companyName TEXT NOT NULL,
    symbol TEXT NOT NULL,
    transactionPrice NUMERIC NOT NULL,
    action TEXT NOT NULL,
    quantity INTEGER NOT NULL,
    totalPrice NUMERIC GENERATED ALWAYS AS (transactionPrice * quantity) STORED,
    time DATETIME DEFAULT CURRENT_TIMESTAMP, 
    FOREIGN KEY(id) REFERENCES users(id)
);


INSERT INTO purchases (id, companyName, symbol, transactionPrice, quantity, action) VALUES (?,?,?,?,?), 
(session["user_id"], purchase_stock['name'], purchase_stock['symbol'], purchase_stock['price'], purchase_stock['quantity'], 'purchase')








INSERT INTO purchases (id, companyName, symbol, purchasePrice, quantity) VALUES (1, 'Netflix', 'NFLX', 360, 2); 

"""

