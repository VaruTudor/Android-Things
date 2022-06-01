# Team Project Speedometer

## Description

The project idea is to measure the distance between an object and the sensor. Due to hardware constraints, there might be some issues regarding very close or very far measurements. (distance < 0.5 cm and distance > 400 cm)

The sensor will measure the distance from its position to the first object met in a forward direction and continues to check it after short intervals of time.

For the UI, we'll build an app blanck ionic-angular template where the user can see the corresponding distance.

## Schematics

![image](https://user-images.githubusercontent.com/58001743/167450207-002589b0-830c-44a0-87cb-b0fe4ec164b3.png)

## Pre-requisites

### Hardware

* Raspberry Pi Zero W ([details and specifications](https://itsfoss.com/raspberry-pi-zero-w/))
* Breadboard
* Male-to-female jumper wires
* HC-SR04+ distance sensor

### Software

* [Visual Studio Code](https://code.visualstudio.com/)  //change this
* [JetBrain WebStorm](https://www.jetbrains.com/webstorm/)

## Setup and Build

1. Connect the Raspberry Pi to power
2. Connect the distance sensor to the breadboard with some jumpers according to the schematics
3. Connect the breadboard to the Raspberry Pi according to the schematics (if the pins are not matched correctly, it will not work)

## Running

* In order to run this project you need to clone the repository and then `cd TeamProjectSpeedometer`
* **For backend** run `pip install bottle` or `sudo apt-get bottle` from a terminal and do the same for `RPi.GPIO` (**note:** the RPi.GPIO library is not supported on Windows so you might want to use a Linux based operating system)
* To start the server, simply run `python distance.py`
* **For frontend** run `ionic serve`

## Demo

The demo of how the sensor is capturing the data and how the app is running are in the demo folder of this repository

