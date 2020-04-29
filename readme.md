# TinyUSB Mouse and Keyboard library

This library provides an Arduino Mouse.h and Keyboard.h compatible API for TinyUSB stack mouse and keyboard control.

Copy all files to your "Arduino/libraries". See the "examples" folder for sample sketches.

This module simulates the standard Arduino "Mouse.h" API and Arduino "Keyboard.h" API for use with the TinyUSB HID API. Instead of doing

    #include <HID.h>
    #include <Mouse.h>
    #include <Keyboard.h>

Simply do

    #include <TinyUSB_Mouse_and_Keyboard.h>
	 
and this module will automatically select whether or not to use the standard Arduino mouse API or the TinyUSB API.

Also be sure to check out the companion library "[BLE52_Mouse_and_Keyboard](https://github.com/cyborg5/BLE52_Mouse_and_Keyboard)" which provides a similar interface for using BLE connections on an nRF52840.


## Redesigned from initial release to be a single library

## Known issues:

 - Intermittent problems using Serial.print() or Serial.println() but it is not always reproducible. We're working on it.
 

