# ExBUS2MSP

A little conversion to allow you to run use the jeti EXBUS stream to 'arm / disarm' a dji flight controller via the MSP protocol.

The general aim is as follows:


- listen to the exbus stream for a specific channel
- when the channel toggles, change the 'arm' flag on the MSP protocol.

This will essentially allow you to pout the dji air unit into low power mode as if its connected to a flight controller

Code is a bit messy and taken from loads of different projects!

Wiring is easy:

With the TEENSY 3.2

PIN 9  => CONNECT TO SERVO SIGNAL PIN ON RX
PIN 8 => RX ON AIR UNIT
PIN 7 => TX ON AIR UNIT

By default the system listen to CHANNEL 5 for a toggle of the channel to indicate arm/disarm.

To change this edit  <exbus.h>

Set the value of ARM_CHANNEL to the channel to listen to for the arm/disarm sequence.

Enjoy...