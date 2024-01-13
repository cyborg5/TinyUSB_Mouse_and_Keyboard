/*
 * This module simulates the standard Arduino "Mouse.h" and
 * "Keyboard.h" API for use with the TinyUSB HID API. Instead of doing
 *  #include <HID.h>
 *  #include <Mouse.h>
 *  #include <Keyboard.h>
 *  
 *  Simply do
 *  
 *  #include <TinyUSB_Mouse_Keyboard.h>
 *  
 *  and this module will automatically select whether or not to use the
 *  standard Arduino mouse and keyboard API or the TinyUSB API. We had to
 *  combine them into a single library because of the way TinyUSB handles
 *  descriptors.
 *  
 *  For details on Arduino Mouse.h see
 *   https://www.arduino.cc/reference/en/language/functions/usb/mouse/
 *  For details on Arduino Keyboard.h see
 *   https://www.arduino.cc/reference/en/language/functions/usb/keyboard/
 *
 *  NOTE: This code is derived from the standard Arduino Mouse.h, Mouse.cpp,
 *    Keyboard.h, and Keyboard.cpp code. The copyright on that original code
 *    is as follows.
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
#ifndef USE_TINYUSB
  //if not using TinyUSB then default to the standard Arduino routines.
  #include <HID.h>
  #include <Mouse.h>
  #include <Keyboard.h>
#else


/*****************************
 *   COMMON SECTION
 *****************************/ 

  #include <Adafruit_TinyUSB.h>
  #include <TinyUSB_Mouse_and_Keyboard.h>
  
  #define RID_KEYBOARD 1
  #define RID_MOUSE 2
  

  // HID report descriptor using TinyUSB's template
  // Single Report (no ID) descriptor
  uint8_t const desc_hid_report[] =
  {
    TUD_HID_REPORT_DESC_KEYBOARD( HID_REPORT_ID(RID_KEYBOARD) ),
    TUD_HID_REPORT_DESC_MOUSE( HID_REPORT_ID(RID_MOUSE) )
  };

  Adafruit_USBD_HID usb_hid;
  
/*****************************
 *   MOUSE SECTION
 *****************************/ 

  TinyMouse_::TinyMouse_(void) {
  }
  
  void TinyMouse_::begin(void) {
    _buttons = 0;
    usb_hid.setPollInterval(2);
    usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
    usb_hid.begin();
    while( !TinyUSBDevice.mounted() ) delay(1);
  }

  void TinyMouse_::move (int8_t x, int8_t y, int8_t wheel) {
    if ( TinyUSBDevice.suspended() )  {
      TinyUSBDevice.remoteWakeup();
    }
    while(!usb_hid.ready()) delay(1);
    usb_hid.mouseReport(RID_MOUSE,_buttons,x,y,wheel,0);
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
  
 /*****************************
 *   KEYBOARD SECTION
 *****************************/ 

  TinyKeyboard_::TinyKeyboard_(void) {
  }
  
  void TinyKeyboard_::begin(void)
  {
    usb_hid.setPollInterval(2);
    usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
    usb_hid.begin();
    while( !TinyUSBDevice.mounted() ) delay(1);
  }
  
  void TinyKeyboard_::end(void)
  {
  }
  
  void TinyKeyboard_::sendReport(KeyReport* keys)
  {
    if ( TinyUSBDevice.suspended() )  {
      TinyUSBDevice.remoteWakeup();
    }
    while(!usb_hid.ready()) delay(1);
    usb_hid.keyboardReport(RID_KEYBOARD,keys->modifiers,keys->keys);
    delay(2);
  }
  
  #define SHIFT 0x80
  const uint8_t _asciimap[128] =
  {
    0x00,             // NUL
    0x00,             // SOH
    0x00,             // STX
    0x00,             // ETX
    0x00,             // EOT
    0x00,             // ENQ
    0x00,             // ACK  
    0x00,             // BEL
    0x2a,     // BS Backspace
    0x2b,     // TAB  Tab
    0x28,     // LF Enter
    0x00,             // VT 
    0x00,             // FF 
    0x00,             // CR 
    0x00,             // SO 
    0x00,             // SI 
    0x00,             // DEL
    0x00,             // DC1
    0x00,             // DC2
    0x00,             // DC3
    0x00,             // DC4
    0x00,             // NAK
    0x00,             // SYN
    0x00,             // ETB
    0x00,             // CAN
    0x00,             // EM 
    0x00,             // SUB
    0x00,             // ESC
    0x00,             // FS 
    0x00,             // GS 
    0x00,             // RS 
    0x00,             // US 
  
    0x2c,      //  ' '
    0x1e|SHIFT,    // !
    0x34|SHIFT,    // "
    0x20|SHIFT,    // #
    0x21|SHIFT,    // $
    0x22|SHIFT,    // %
    0x24|SHIFT,    // &
    0x34,          // '
    0x26|SHIFT,    // (
    0x27|SHIFT,    // )
    0x25|SHIFT,    // *
    0x2e|SHIFT,    // +
    0x36,          // ,
    0x2d,          // -
    0x37,          // .
    0x38,          // /
    0x27,          // 0
    0x1e,          // 1
    0x1f,          // 2
    0x20,          // 3
    0x21,          // 4
    0x22,          // 5
    0x23,          // 6
    0x24,          // 7
    0x25,          // 8
    0x26,          // 9
    0x33|SHIFT,      // :
    0x33,          // ;
    0x36|SHIFT,      // <
    0x2e,          // =
    0x37|SHIFT,      // >
    0x38|SHIFT,      // ?
    0x1f|SHIFT,      // @
    0x04|SHIFT,      // A
    0x05|SHIFT,      // B
    0x06|SHIFT,      // C
    0x07|SHIFT,      // D
    0x08|SHIFT,      // E
    0x09|SHIFT,      // F
    0x0a|SHIFT,      // G
    0x0b|SHIFT,      // H
    0x0c|SHIFT,      // I
    0x0d|SHIFT,      // J
    0x0e|SHIFT,      // K
    0x0f|SHIFT,      // L
    0x10|SHIFT,      // M
    0x11|SHIFT,      // N
    0x12|SHIFT,      // O
    0x13|SHIFT,      // P
    0x14|SHIFT,      // Q
    0x15|SHIFT,      // R
    0x16|SHIFT,      // S
    0x17|SHIFT,      // T
    0x18|SHIFT,      // U
    0x19|SHIFT,      // V
    0x1a|SHIFT,      // W
    0x1b|SHIFT,      // X
    0x1c|SHIFT,      // Y
    0x1d|SHIFT,      // Z
    0x2f,          // [
    0x31,          // bslash
    0x30,          // ]
    0x23|SHIFT,    // ^
    0x2d|SHIFT,    // _
    0x35,          // `
    0x04,          // a
    0x05,          // b
    0x06,          // c
    0x07,          // d
    0x08,          // e
    0x09,          // f
    0x0a,          // g
    0x0b,          // h
    0x0c,          // i
    0x0d,          // j
    0x0e,          // k
    0x0f,          // l
    0x10,          // m
    0x11,          // n
    0x12,          // o
    0x13,          // p
    0x14,          // q
    0x15,          // r
    0x16,          // s
    0x17,          // t
    0x18,          // u
    0x19,          // v
    0x1a,          // w
    0x1b,          // x
    0x1c,          // y
    0x1d,          // z
    0x2f|SHIFT,    // {
    0x31|SHIFT,    // |
    0x30|SHIFT,    // }
    0x35|SHIFT,    // ~
    0       // DEL
  };
  
  // press() adds the specified key (printing, non-printing, or modifier)
  // to the persistent key report and sends the report.  Because of the way 
  // USB HID works, the host acts like the key remains pressed until we 
  // call release(), releaseAll(), or otherwise clear the report and resend.
  size_t TinyKeyboard_::press(uint8_t k) 
  {
    uint8_t i;
    if (k >= 136) {     // it's a non-printing key (not a modifier)
      k = k - 136;
    } else if (k >= 128) {  // it's a modifier key
      _keyReport.modifiers |= (1<<(k-128));
      k = 0;
    } else {        // it's a printing key
      k = pgm_read_byte(_asciimap + k);
      if (!k) {
        setWriteError();
        return 0;
      }
      if (k & 0x80) {           // it's a capital letter or other character reached with shift
        _keyReport.modifiers |= 0x02; // the left shift modifier
        k &= 0x7F;
      }
    }
    
    // Add k to the key report only if it's not already present
    // and if there is an empty slot.
    if (_keyReport.keys[0] != k && _keyReport.keys[1] != k && 
      _keyReport.keys[2] != k && _keyReport.keys[3] != k &&
      _keyReport.keys[4] != k && _keyReport.keys[5] != k) {
      
      for (i=0; i<6; i++) {
        if (_keyReport.keys[i] == 0x00) {
          _keyReport.keys[i] = k;
          break;
        }
      }
      if (i == 6) {
        setWriteError();
        return 0;
      } 
    }
    sendReport(&_keyReport);
    return 1;
  }
  
  // release() takes the specified key out of the persistent key report and
  // sends the report.  This tells the OS the key is no longer pressed and that
  // it shouldn't be repeated any more.
  size_t TinyKeyboard_::release(uint8_t k) 
  {
    uint8_t i;
    if (k >= 136) {     // it's a non-printing key (not a modifier)
      k = k - 136;
    } else if (k >= 128) {  // it's a modifier key
      _keyReport.modifiers &= ~(1<<(k-128));
      k = 0;
    } else {        // it's a printing key
      k = pgm_read_byte(_asciimap + k);
      if (!k) {
        return 0;
      }
      if (k & 0x80) {             // it's a capital letter or other character reached with shift
        _keyReport.modifiers &= ~(0x02);  // the left shift modifier
        k &= 0x7F;
      }
    }
    
    // Test the key report to see if k is present.  Clear it if it exists.
    // Check all positions in case the key is present more than once (which it shouldn't be)
    for (i=0; i<6; i++) {
      if (0 != k && _keyReport.keys[i] == k) {
        _keyReport.keys[i] = 0x00;
      }
    }
    sendReport(&_keyReport);
    return 1;
  }
  
  void TinyKeyboard_::releaseAll(void)
  {
    _keyReport.keys[0] = 0;
    _keyReport.keys[1] = 0; 
    _keyReport.keys[2] = 0;
    _keyReport.keys[3] = 0; 
    _keyReport.keys[4] = 0;
    _keyReport.keys[5] = 0; 
    _keyReport.modifiers = 0;
    sendReport(&_keyReport);
  }
  
  size_t TinyKeyboard_::write(uint8_t c)
  {
    uint8_t p = press(c);  // Keydown
    release(c);            // Keyup
    return p;              // just return the result of press() since release() almost always returns 1
  }
  
  size_t TinyKeyboard_::write(const uint8_t *buffer, size_t size) {
    size_t n = 0;
    while (size--) {
      if (*buffer != '\r') {
        if (write(*buffer)) {
          n++;
        } else {
          break;
        }
      }
      buffer++;
    }
    return n;
  }
  TinyKeyboard_ Keyboard;//create an instance of the Keyboard object
#endif
