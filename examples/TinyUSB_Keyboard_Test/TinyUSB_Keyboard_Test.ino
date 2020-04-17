/*
 * Sample program demonstrating TinyUSB_Mouse_and_Keyboard.h module which
 * auto selects between standard Arduino Mouse.h API and TinyUSB mouse API.
 * This program tests the keyboard portion alone.
 */

//Include this module whether using Arduino stack or TinyUSB stack
#include <TinyUSB_Mouse_and_Keyboard.h>

uint8_t Multiple[3]= {'1','2','3'};
void setup() {
  Keyboard.begin();   //Unlike Arduino Keyboard.h, you must use begin.
  Serial.begin(115200);
  while (! Serial)delay (1);
  Serial.println("USB keyboard test");
  Keyboard.write('a');            //press and release 'a' key
  Keyboard.write(Multiple,3);     //multiple keys sequentially from a buffer
  Keyboard.print("456");          //print a string
  Keyboard.println("789");        //print another string with a line
  Keyboard.press(KEY_LEFT_SHIFT); //hold down the shift
  Keyboard.println("a uppercase sentence"); //this will be all caps
  Keyboard.release(KEY_LEFT_SHIFT);//release the shift
  Keyboard.println ("back to lowercase");
  Keyboard.press(KEY_LEFT_SHIFT); //press shift
  Keyboard.println("1234");       //some text
  Keyboard.releaseAll();          //release all
  Keyboard.println("1234");       //not shifted
  Keyboard.print("A mistake");  //will attempt to erase this
  delay(1000);
  Keyboard.press(KEY_LEFT_CTRL);  //will attempt control-z
  Keyboard.write('z');
  Keyboard.releaseAll();         //release the control key
  Serial.println("USB keyboard test completed");
};
void loop() {
}

/*
 * Click below before uploading and it will type characters in this comment
 * 
 * 
 *  
 *  
 *  
 *  
 *  
 *  
 */
