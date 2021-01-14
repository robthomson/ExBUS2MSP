# ExBUS2MSP

A little conversion to allow you to run use the jeti EXBUS stream to 'arm / disarm' a dji flight controller via the MSP protocol.

The general aim is as follows:


- listen to the exbus stream for a specific channel
- when the channel toggles, change the 'arm' flag on the MSP protocol.

This will essentially allow you to pout the dji air unit into low power mode as if its connected to a flight controller