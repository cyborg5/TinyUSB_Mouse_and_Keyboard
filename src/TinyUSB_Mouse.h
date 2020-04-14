/*
 * This module simulates the standard Arduino "Mouse.h" API for use with the
 *  TinyUSB HID API. Instead of doing
 *  #include <HID.h>
 *  #include <Mouse.h>
 *  
 *  Simply do
 *  
 *  #include "TinyUSB_Mouse.h"
 *  
 *  and this module will automatically select whether or not to use the
 *  standard Arduino mouse API or the TinyUSB API. 
 *  
 *  For details on Arduino Mouse.h see
 *   https://www.arduino.cc/reference/en/language/functions/usb/mouse/
 *
 *  NOTE: This code is derived from the standard Arduino Mouse.h and Mouse.cpp
 *    code. The copyright on that original code is as follows.
 *   
 *  Copyright (c) 2015, Arduino LLC
 *  Original code (pre-library): Copyright (c) 2011, Peter Barrett
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifdef USE_TINYUSB
  #define MOUSE_LEFT 1
  #define MOUSE_RIGHT 2
  #define MOUSE_MIDDLE 4
  #define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)

  /*
   * This class contains the exact same methods as the Arduino Mouse.h class.
   */
  class TinyMouse_
  {
    private:
      uint8_t _buttons;
      void buttons(uint8_t b);
    public:
      TinyMouse_(void);
      void begin(void);
      void end(void);
      void click(uint8_t b = MOUSE_LEFT);
      void move(signed char x, signed char y, signed char wheel = 0); 
      void press(uint8_t b = MOUSE_LEFT);   // press LEFT by default
      void release(uint8_t b = MOUSE_LEFT); // release LEFT by default
      bool isPressed(uint8_t b = MOUSE_LEFT); // check LEFT by default
  };
  
  extern TinyMouse_ Mouse;
#else   //if not using TinyUSB then default to the standard Arduino routines.
  #include <HID.h>
  #include <Mouse.h>
#endif  
