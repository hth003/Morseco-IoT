# Morseco - The Morse code IoT station 

It has been years since Morse code was the main telecommunication method. With Morseco, communicating with friends on chatroom no longer a boring task of typing the text on smartphone, but an interactive and fun experience for people who love the old school technology. Plus, for people who want to learn Morse code, this is a good tools to memorize complex combination of dash and dot. Morseco also provides a bonus of a real time internet-updated clock, so that you never need to fiddle with the code to switch time when day time saving comes. Everytime you start the machine, fun LED and Star Wars music create butterfly in your stomach. Oh the good old time! 

In a nutshell, this is a Morse code communication system which automatically translate morse code between an Arduino station and Telegram chat bot. 

## Motivation
* To create a project that is fun to do, which rekindle my interest for embedded programing
* To explore the potential of Intenet of Things
* To satisfy my interest for old school stuffs
* To learn Morse code, which might help for future survival in case of apocolyse
* To spend time doing something useful during this free buffer time between finishing grad school and the real world 

## Functionality
* Greet you with a fun Star War song and LED flashing in red and blue, symbolic color of the Jedi and the Sith.
* Even if you don't like Morse code, it is a great real-time internet-updated clock, where the time is showed on the LCD display. 
* Three button interface (dot, dash, space) to input the Morse code of your choice, where the imput Morse code is displayed on LCD for visual aid.
* Input Morse code is translated to human language, then is sent to the designate Telegram Bot
* Any response is then sent to the Morse code station, translated back to Morse code, which create light and sound pattern on the LED and the buzzer. 

## Components and Supplies

* 1 Arduino MKR1000 board
* 1 micro USB cable
* 1 400-point breadboard
* 3 pushbuttons (for dot, dash, and space)
* 3 10k ohm resistor for button pull down resistors
* 1 alphanumeric LCD (16 x 2 characters)
* a 220 Ohm resistor for LCD
* 1 RGB LED
* 1 buzzer

Pin connection can be infered from the code. 


## Some explaination of algorithms and library used

Morse code encoder and decoder is based from the following tree. More explaination is in the comment of Translator.h

![Morse code](https://i.pinimg.com/originals/33/46/ed/3346ed3bec1ef39f389fd69a10886234.png)

The most current ArduinoJson version is version 6, but the Telegram Bot library used version 5, thus in order for the code to work, Arduino Json library version 5.13.5 was used.

If the board cannot connect to WiFi, reset the board until you hear the greeting Star War song.


