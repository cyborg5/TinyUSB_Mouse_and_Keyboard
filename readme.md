# Problems developed with this code. Do not download yet. It worked yesterday but not today.
# TinyUSB Mouse and Keyboard libraries 

These libraries provide an Arduino Mouse.h and Keyboard.h compatible API for TinyUSB stack mouse and keyboard control.

Copy all files to your "Arduino/libraries". See the "examples" folder for sample sketches.

This module simulates the standard Arduino "Mouse.h" API and Arduino "Keyboard.h" API for use with the TinyUSB HID API. Instead of doing

    #include <HID.h>
    #include <Mouse.h>
    #include <Keyboard.h>

Simply do

    #include <TinyUSB_Mouse.h>
	#include <TinyUSB_Keyboard.h>
 
and this module will automatically select whether or not to use the standard Arduino mouse API or the TinyUSB API.

