'''
Written By Prashant Thirumal

This is a simple web scraper that lets you check prices of a particular item on Amazon
'''

# To access URL's
import requests
from bs4 import BeautifulSoup

# To send emails
import smtplib

import time

# desired price of my object
desired_price = 50.00

# Amazon link
URL = 'https://www.amazon.com/BRIGHTFOCAL-THINKPAD-Full-HD-REPLACEMENT-Display/dp/B07D4PK253/ref=sr_1_4?keywords=t440+screen&qid=1573270816&sr=8-4'

# Gives us some information about browser
headers = {
    "User-agent": 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.97 Safari/537.36'}


def price_checker():
    # Make a call to the page
    page = requests.get(URL, headers=headers)

    '''
    Thanks to the internet, I found a way to parse amazon.com
    Amazon makes the html code with javascript. To trick them, you
    use two soup and that lets you do all the fun stuff
    '''

    # Use beautiful soup to parse everything for us
    soup = BeautifulSoup(page.content, 'html.parser')
    soup_actual = BeautifulSoup(soup.prettify(), 'html.parser')

    # Get the title of the object you are looking for
    title = soup_actual.find(id="productTitle").get_text()

    # Remove all the white space
    title_actual = title.strip()

    # Get the price
    price = soup_actual.find(id='priceblock_ourprice').get_text()

    # Convert the string to a float
    # Need to remove the $ first
    price = price[1:]
    price_float = float(price)

    if price_float <= desired_price:
        send_mail()
        return True
    return False


def send_mail():
    server = smtplib.SMTP('smtp.gmail.com', 587)
    # command sent by email server to identify itself
    # helps us connect basically
    server.ehlo()
    server.starttls()
    server.ehlo()
    server.login('#########@gmail.com', '################')

    # Define the subject and body of the email
    subject = 'Desired Price Reached'
    body = 'Check the amazon link: ' + URL
    msg = f'Subject: {subject}\n\n {body}'

    # Send the email
    server.sendmail('##########@gmail.com', '###########@gmail.com', msg)

    # Print out that email has been sent
    print("Email has been sent! Your broke ass must be happy")


# Check the price once every 5 hours
num_seconds_in_five_hrs = 60 * 60 * 5
while not price_checker():
    price_checker()
    time.sleep(num_seconds_in_five_hrs)
