"""
*   Credits: www.plusivo.com
*
*   Lesson 21: Display the distance in web
*
*   This code is similar with the one included in the lesson "Ultrasonic
*   HC-SR04+", but this time we will display the distance in a web page
*   hosted by the development board.
*
*   More information about the code can be found in the guide.
*
"""

#import the necessary modules from the bottle library
from bottle import route, run, template, request
#we will import the RPi.GPIO library with the name of GPIO
import RPi.GPIO as GPIO
import time

#we will set the pin numbering to the GPIO.BOARD numbering
GPIO.setmode(GPIO.BOARD)

#declare the pins used by the ultrasonic module
trig = 16
echo = 18

#set the trigger pin as OUTPUT and the echo as INPUT
GPIO.setup(trig, GPIO.OUT)
GPIO.setup(echo, GPIO.IN)

def calculate_distance():
    #set the trigger to HIGH
    GPIO.output(trig, GPIO.HIGH)

    #sleep 0.00001 s and the set the trigger to LOW
    time.sleep(0.00001)
    GPIO.output(trig, GPIO.LOW)

    #save the start and stop times
    start = time.time()
    stop = time.time()

    #modify the start time to be the last time until
    #the echo becomes HIGH
    while GPIO.input(echo) == 0:
        start = time.time()

    #modify the stop time to be the last time until
    #the echo becomes LOW
    while  GPIO.input(echo) == 1:
        stop = time.time()

    #get the duration of the echo pin as HIGH
    duration = stop - start

    #calculate the distance
    distance = 34300/2 * duration

    if distance < 0.5 and distance > 400:
        return 0
    else:
        #return the distance
        return distance

#define the route for the main page
@route('/')
def index():
    #at the '/' route we will return the index.html
    #template that is in the views folder
    return template('index.html')

@route('/refresh')
#define a function to send data to client
def refresh():
    #calculate the distance
    dist = calculate_distance()

    #return the distance to client
    return '%d' % dist

try:
    #we will run the app on port 5000
    run(host = '0.0.0.0', port = '5000')

except KeyboardInterrupt:
    pass

#clean the used ports
GPIO.cleanup()
