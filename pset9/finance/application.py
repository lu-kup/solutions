import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")






@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    data_table = db.execute('SELECT DISTINCT symbol FROM purchases WHERE user_id = ?;', session["user_id"])
    for row in data_table:
        row['t_shares'] = db.execute('SELECT SUM(shares) FROM purchases WHERE user_id = ? AND symbol = ?;', session["user_id"], row['symbol'])[0]['SUM(shares)']
        row['t_price'] = lookup(row['symbol'])['price']
        row['t_name'] = lookup(row['symbol'])['name']
        print(row['t_shares'] )
        print(row['t_price'])
        row['total'] = row['t_shares'] * row['t_price']

    t_cash = db.execute('SELECT cash FROM users WHERE id = ?;', session["user_id"])
    total = t_cash[0]['cash']
    for row in data_table:
        print( total )
        print(row['total'])
        total = total + row['total']

    return render_template("index.html", data_table = data_table, cash = t_cash[0]['cash'], total = total)





@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        if not request.form.get("symbol") or lookup(request.form.get("symbol")) == None:
            return apology("must provide valid symbol")

        if not request.form.get("shares"):
            return apology("must provide number of shares")

        if not request.form.get("shares").isnumeric():
            return apology("number of shares must be numeric")

        elif not float(request.form.get("shares")).is_integer() or float(request.form.get("shares")) <= 0:
            return apology("number of shares must be a positive integer")

        shares = float(request.form.get("shares"))
        symbol = request.form.get("symbol")
        current_price = lookup(symbol)['price']
        cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])[0]['cash']
        print(current_price)
        print(shares)
        print(cash)

        if current_price * shares > cash:
            return apology("You cannot buy shares at current price")

        else:
            cash = cash - current_price * shares
            db.execute('INSERT INTO purchases(user_id,symbol,shares,price) VALUES (?, ?, ?, ?);', session["user_id"], symbol, shares, current_price)
            db.execute('UPDATE users SET cash = ? WHERE id = ?;', cash, session["user_id"])
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    full = db.execute('SELECT * FROM purchases WHERE user_id = ?;', session["user_id"])
    return render_template("history.html", full = full)



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

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol")

        symbol = request.form.get("symbol")

        if lookup(symbol) != None:
            info = lookup(symbol)
        else:
            return apology("no such stock")

        # Render the page with answer data
        return render_template("quoted.html", info = info)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():


    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":


        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        existing = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(existing) != 0:
            return apology("the username is taken, please try again")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        elif not request.form.get("confirmation"):
            return apology("must provide password")

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("the passwords do not match")

        #Submit user's input and generate hash
        username = request.form.get("username")
        password = request.form.get("password")
        hash = generate_password_hash(password)

        #Update database
        db.execute('INSERT INTO users(username, hash) VALUES (?, ?)', username, hash)


        # Redirect user to home page
        return redirect("/")


    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""


    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide valid symbol", 403)

        elif not request.form.get("shares"):
            return apology("must provide number of shares", 403)

        elif not float(request.form.get("shares")).is_integer or int(request.form.get("shares")) <= 0:
            return apology("number of shares must be a positive integer", 403)

        symbol = request.form.get("symbol")
        amount_owned = db.execute('SELECT SUM(shares) FROM purchases WHERE user_id = ? AND symbol = ?;', session["user_id"],symbol)[0]['SUM(shares)']
        shares = int(request.form.get("shares"))
        current_price = lookup(symbol)['price']
        cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])[0]['cash']

        if shares > amount_owned:
            return apology("You do not own enough shares")

        else:
            cash = cash + current_price * shares
            db.execute('INSERT INTO purchases(user_id,symbol,shares,price) VALUES (?, ?, ?, ?);', session["user_id"], symbol, (-1 * shares), current_price)
            db.execute('UPDATE users SET cash = ? WHERE id = ?;', cash, session["user_id"])
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        choices = db.execute("SELECT DISTINCT symbol FROM purchases WHERE user_id = ?;", session["user_id"])
        print(choices)
        return render_template("sell.html", choices = choices)



@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add cash to the user's account"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        if not request.form.get("amount") or float(request.form.get("amount")) <= 0:
            return apology("must provide valid amount")

        amount = float(request.form.get("amount"))
        cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])[0]['cash']

        cash = cash + amount
        db.execute('UPDATE users SET cash = ? WHERE id = ?;', cash, session["user_id"])
        return redirect("/")

    else:
        return render_template("add_cash.html")




def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
