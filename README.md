# Node-RED Based Room Sensors Monitoring

<div style="text-align:center"><img src="https://i.ibb.co/qnr0Bbg/image1.png" style="width: 80%;" /></div>

> This is an academic project, which aims to use Node-RED for the monitoring of data coming from several sensors
---

### Table of Contents

- [Description](#description)
- [Specifications](#specifications)
- [The Hardware](#the-hardware)
- [Global System Architecture](#global-system-architecture)
- [Electronic Circuit](#electronic-circuit)
- [Connecting To Node-RED](#connecting-to-node-red)
- [Programming On Node-RED](#programming-on-node-red)
- [Demonstration](#demonstration)
- [Project Files](#project-files)
- [Author Info](#author-info)

---

## Description

The application is based on the analysis of data provided by :

1. Brightness sensor (photoresistor), located into the room
2. RFID (Radio Frequency Identification) reader, located next to the room's door

- The role of the RFID reader is to identify persons asking to get into the room. Based on their identifiers we can decide eather to authorize them to enter or to deney their access
- The objective is to remotely supervise the data specific to the use of the room. Namely, the brightness value and information about the people who frequent it

<div style="text-align:center"><img src="https://i.ibb.co/xfrbFBK/image2.png" style="width: 70%;" /></div>

---

## Specifications

The platform will be used as follows :

1. Sending email if there is someone who identifies himself to enter :
    - inform the administrator of the name of the incoming person
    - inform him of the brightness value in the room at that moment

2. Room brightness monitoring :
    - view the brightness value all the time, on a gauge and on a timeline graph
    - customize the classification of the brightness values corresponding to the alert levels (minimum value and maximum value)
    - communicate alerts via administrator's email

---

## The Hardware

- 2 x Arduino Uno : acquisition of sensors values and interfacing with Node-RED *
- 1 x RFID Module and Tags : users identification
- 1 x Photoresistence : brightness level detection
- 1 x Buzzer Alarm : sound effects accompanying RFID identification

<div style="text-align:center"><img src="https://i.ibb.co/QHDVkVn/image3.png" style="width: 70%;" /></div>

---

## Global System Architecture

<div style="text-align:center"><img src="https://i.ibb.co/Jp9zLyx/image4.png" /></div>

**Note :*

    The reason behind using two Arduino instead of one is as follows :
        - First, the Arduino executing the main program initially contains a program called "Firmata Standard" which we modify by adding what we need to ensure interfacing between Arduino and external components (sensors and actuators)
        - This “Firmata Standard” program, which is part of the “Firmata” library, has the functionality of implementing the “Firmata” protocol which ensures communication between the program and the server; it is therefore essential to be able to work with Node-RED
        - It should be noted that this protocol is very encumbered. On the other hand, the code for reading RFID Tags takes a relatively long time. So to optimize and lighten the program, it was necessary to make this separation

---

## Electronic Circuit

<div style="text-align:center"><img src="https://i.ibb.co/s9Lh2DP/image5.png" /></div>

---

## Connecting To Node-RED

After compiling and uploading the two Arduino programs, we connect the Arduino representing the interface with Node-RED to a serial port (USB) on the computer (this port will ensure communication between Arduino and Node-RED). Then we launch Node-RED on the command line as follows :

<div style="text-align:center"><img src="https://i.ibb.co/VCB39TL/image6.png" /></div>

- In this case, the communication is supported by the **COM16** port at the speed of **9600 baud**

- Node-RED is therefore ready to use

---

## Programming On Node-RED

1. Back-end : **Flow**

This part is dedicated to programming various functions and operations that will be applied to data coming from Arduino. Below is the overview of the **Flow,** with the program carried out.

<div style="text-align:center"><img src="https://i.ibb.co/y81S7Xk/image7.png" /></div>

2. Front-end : **Dashboard**

This part constitutes the user interface. This is where we see the change in sensor values, etc. As you can also control parameters, but graphically.
Below the **Dashboard** that heve been made.

<div style="text-align:center"><img src="https://i.ibb.co/xYVBqb8/image8.png" style="width: 80%;" /></div>

---

## Demonstration

<div style="text-align:center"><img src="https://i.ibb.co/cywr0zd/image9.png" style="width: 70%;" /></div>

This is an illustrative scenario of use :

1. Set Min and Max alert levels
<div style="text-align:center"><img src="https://i.ibb.co/z7kWDN6/image10.png" /></div>

2. Access made by *Oussama Oulkaid*
<div style="text-align:center"><img src="https://i.ibb.co/G5dH9Sx/image11.png" style="width: 80%;" /></div>

3. The administrator receives a message via email
<div style="text-align:center"><img src="https://i.ibb.co/Vqhv9Ly/image12.png" style="width: 80%;" /></div>

4. Access made by an unknown person
<div style="text-align:center"><img src="https://i.ibb.co/9tPw1Gq/image13.png" style="width: 80%;" /></div>

5. The administrator receives a message via email
<div style="text-align:center"><img src="https://i.ibb.co/NrzxyWt/image14.png" style="width: 80%;" /></div>

6. Maximal alert level acheied
<div style="text-align:center"><img src="https://i.ibb.co/dQvNdgC/image15.png" style="width: 80%;" /></div>

7. The administrator receives a message via email
<div style="text-align:center"><img src="https://i.ibb.co/J7nzfrw/image16.png" style="width: 80%;" /></div>

---

## Project Files

The project contains two files :

1. [RFID_Arduino_Interface.ino](RFID_Arduino_Interface.ino) : reading RFID tags and inform the second arduino about the tags' values
2. [Node-RED_Arduino_Interface.ino](Node-RED_Arduino_Interface.ino) : connecting the arduino to the Node-RED platform, in order to send data via a serial communication

---

## Author Info

- Email - oussama.oulkaid@gmail.com
- LinkedIn - [Oussama Oulkaid](https://www.linkedin.com/in/oulkaid)
