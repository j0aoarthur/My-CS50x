import os
import sqlite3
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    
    # Configure CS50 Library to use SQLite database
    conn = sqlite3.connect("birthdays.db")
    db = conn.cursor()

    if request.method == "POST": 
        
        name = request.form.get("name_input")
        date = request.form.get("date_input")
        month = date[5:7]
        day = date[8:]
        
        db.execute('INSERT INTO birthdays (name, month, day) VALUES ( ?, ?, ?)', (name, month, day))
        conn.commit()

        return redirect("/")
    else:
        db.execute('SELECT name, month, day FROM birthdays ORDER by month,day ')
        data = db.fetchall()

        return render_template("index.html", userdata=data)