/*
 * Sample program demonstrating TinyUSB_Keyboard.h and TinyUSB_Mouse.h modules 
 * together at the same time. These modules auto select between standard 
 * Arduino API and TinyUSB API for mouse and keyboard.
 */

//Include these modules whether using Arduino stack or TinyUSB stack
#include <TinyUSB_Mouse.h>
#include <TinyUSB_Keyboard.h>

void setup() {
  Keyboard.begin(); //Like Arduino Keyboard.h and Mouse.h, 
  Mouse.begin();    //    neither "begin" nor "end" methods do anything.
  //Don't really need much Serial output but we wanted to make sure it doesn't interfere
  Serial.begin(115200); 
  while (! Serial)delay (1);
  Serial.println("USB mouse and keyboard test");
  Keyboard.println("The first line of text");   //write some text
  Keyboard.println("The second line of text");
  delay(2000);
  Mouse.click();
  Keyboard.press(KEY_LEFT_SHIFT);   //hold the shift key
  Mouse.move(100,0);                //move the mouse
  Mouse.click();                    //click again
  Keyboard.releaseAll();            //release the shift
  delay(2000);
  Keyboard.press(KEY_LEFT_CTRL);    //do a control-x
  Keyboard.write('x');              //press and release 'x' key
  Keyboard.releaseAll();            //release the control
  delay(2000);
  Mouse.move(0, 20);                //move the mouse down a bit
  Mouse.click();
  delay(2000);
  Keyboard.press(KEY_LEFT_CTRL);    //do a control-v
  Keyboard.write('v');              //press and release 'v' key
  Keyboard.releaseAll();            //release the control
  Serial.println("Test completed.");
};
void loop() {
}

/*
 * Click just after the "*" on the on the next line before uploading
 * 
 * 
 * 
 * 
 *  
 *  
 *  
 *  
 *  
 *  
 */
