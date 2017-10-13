# User-space application for RGB LED display

==================================================================
Getting Started
==================================================================

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

==================================================================
 Running the tests
==================================================================
(Please set the mouse event in RGBled.c . Currently its set event3)

1) "make all" -- The program will begin preparing the executable files which is cross compiled.

2) RGBLed is the executable file that needs to be transferred to galelio board.

3) Setting up Galileo Board 
Connect the TTL & Ethernet cable to Galileo Board & host system & set up static ip address 
open terminal & execute : sudo screen /dev/ttyUSB0 115200
Double click enter & you can get the console of Galileo Board.
Set up static ip address using :
ifconfig enp0s20f6192.168.1.5 netmask 255.255.0.0 up
Ensure that host Ethernet connection is on same netmask & you will be able execute:  ping 192.168.1.5 with successful transmission of bytes to the board

4) Now that you have setup Connection execute on a new terminal:
	"scp RGBLed root@192.168.1.5:/home"

5)In console window navigate to home Directory & Execute :

	"./RGBLed 50 0 1 2"

This implies 50% duty cycle & 0,1,2 are the arduino sheild connectors that various LED Pins are connected to i.e(IO0 , IO1 , IO2)

Note : Range of Duty Cycle : 0-100
	  Range of IO pin numbers :0-13 (Ensure that you enter the same Pin numbers as input argumets that you have connected the digital Connectors to)

6) Left Click on mouse would terminate the program

7) "make clean" on host window  which would remove all the executable files created


==================================================================
Annexure
==================================================================

 
a) gedit RGBLed.c -- instruction to access the file contents of RGBLed.c


==================================================================
Authors
==================================================================


NITHEESH MUTHURAJ 
ASU ID:1213383988
nitheesh@asu.edu
 
REVANTH RAJSHEKAR 
ASU ID:1213380816
rmrajash@asu.edu

