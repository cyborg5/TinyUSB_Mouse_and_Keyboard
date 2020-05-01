/*
 * Sample program demonstrating TinyUSB_Mouse_and_Keyboard.h module which
 * auto selects between standard Arduino Mouse.h API and TinyUSB mouse API.
 * This program tests the mouse and keyboard portions together.
 */

//Include this module whether using Arduino stack or TinyUSB stack
#include <TinyUSB_Mouse_and_Keyboard.h>

void setup() {
  //Don't really need much Serial output but we wanted to make sure it doesn't interfere
  Keyboard.begin(); //Unlike Arduino Keyboard.h and Mouse.h, 
  Mouse.begin();    //    you must use "begin" method for both mouse and keyboard.
  Serial.begin(115200); 
  while (! Serial)delay (1);
  Serial.println("USB mouse and keyboard test");
  Keyboard.println("The first line of text");   //write some text
  Keyboard.println("The second line of text");
  Serial.println("Wrote some text.");
  delay(2000);
  Mouse.click();
  Keyboard.press(KEY_LEFT_SHIFT);   //hold the shift key
  Mouse.move(100,0);                //move the mouse
  Mouse.click();                    //click again
  Keyboard.releaseAll();            //release the shift
  Serial.println("Highlighted the first line.");
  delay(2000);
  Keyboard.press(KEY_LEFT_CTRL);    //do a control-x
  Keyboard.write('x');              //press and release 'x' key
  Keyboard.releaseAll();            //release the control
  Serial.println("Cut the text");
  delay(2000);
  Mouse.move(0, 20);                //move the mouse down a bit
  Mouse.click();
  delay(2000);
  Keyboard.press(KEY_LEFT_CTRL);    //do a control-v
  Keyboard.write('v');              //press and release 'v' key
  Keyboard.releaseAll();            //release the control
  Serial.println("Pasted the text");
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
 *  
 *  
 */
