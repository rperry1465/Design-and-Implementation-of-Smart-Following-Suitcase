# Design-and-Implementation-of-Smart-Following-Suitcase
Senior Project - Design and Implementation of Smart-Following Suitcase - EECE 480/481W EMU 2026

See below for a general layout of the code:

Libraries 
          
          - Adafruit Motor Shield Library is essential towards getting the suitcase motors to run
          
          - Libraries for the bluetooth module should also be provided as needed

Additional .ino files to run MAIN
          
          - Define motor directions (both in terms of a function which utilizes distance from user and the angle reading, and in terms of predefined movements for sonic sensors to follow)
          
          - Get readings from the array of sonic sensors (attaching interrupt may need to be done in MAIN, but the goal is to run it here)
          
          - Get Bluetooth distance readings (this could also be added to uS file for convience)
          
          - Define funtions to run I2C commands to the Raspberry Pi (this will help to siplify code in MAIN)

Items included in MAIN
         
          - Read Array Data
         
          - Read Bluetooth Data
         
          - Call functions in appropriate manner so that the prototype behaves as expected
         
          - Send signals to Pi when a set actions happen
