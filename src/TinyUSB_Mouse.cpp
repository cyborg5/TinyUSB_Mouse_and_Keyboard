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
  #include <Adafruit_TinyUSB.h>
  #define RID_MOUSE 2
  
  #include "TinyUSB_Mouse.h"

  // HID report descriptor using TinyUSB's template
  // Single Report (no ID) descriptor
  uint8_t const desc_hid_report[] =
  {
    TUD_HID_REPORT_DESC_MOUSE(HID_REPORT_ID(RID_MOUSE),)
  };

  Adafruit_USBD_HID usb_hid;
  
  TinyMouse_::TinyMouse_(void) {
    _buttons = 0;
    usb_hid.setPollInterval(2);
    usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
    usb_hid.begin();
    while( !USBDevice.mounted() ) delay(1);
  };
  
  void TinyMouse_::begin(void) {
  }
  void TinyMouse_::move (int8_t x, int8_t y, int8_t wheel) {
      //DEBUG("Attempting move");DEBUG (_buttons);DEBUG(x); DEBUG (y); DEBUG (wheel);
      if ( USBDevice.sUSBended() )  {
        USBDevice.remoteWakeup();
      }//else DEBUG("USB device not sUSBended");
      while(!usb_hid.ready()) delay(1);
      usb_hid.mouseReport(RID_MOUSE,_buttons,x,y,wheel,0);
      //} else DEBUG("Not Ready");  
  }
  
  void TinyMouse_::end(void) 
  {
  }
  
  void TinyMouse_::click(uint8_t b)
  {
    _buttons = b;
    move(0,0,0);
    _buttons = 0;
    move(0,0,0);
  }
  
  void TinyMouse_::buttons(uint8_t b)
  {
    if (b != _buttons)
    {
      _buttons = b;
      move(0,0,0);
    }
  }
  
  void TinyMouse_::press(uint8_t b) 
  {
    buttons(_buttons | b);
  }
  
  void TinyMouse_::release(uint8_t b)
  {
    buttons(_buttons & ~b);
  }
  
  bool TinyMouse_::isPressed(uint8_t b)
  {
    if ((b & _buttons) > 0) 
      return true;
    return false;
  }
  
  TinyMouse_ Mouse;//create an instance of the Mouse object
#endif