/*
 * Sample program demonstrating TinyUSB_Mouse_and_Keyboard.h module which
 * auto selects between standard Arduino Mouse.h API and TinyUSB mouse API.
 * This program tests the mouse portion alone.
 */

//Include this module whether using Arduino stack or TinyUSB stack
#include <TinyUSB_Mouse_and_Keyboard.h>

void Status (void) {  //prints out mouse button status
  Serial.print("Mouse Buttons: Left:"); Serial.print(Mouse.isPressed(MOUSE_LEFT),DEC);
  Serial.print(" Right:"); Serial.print(Mouse.isPressed(MOUSE_RIGHT),DEC);
  Serial.print(" Middle:"); Serial.println(Mouse.isPressed(MOUSE_MIDDLE),DEC);
}

void setup() {
  Mouse.begin();  //Unlike Arduino Mouse.h, you must use "begin" method.
  Serial.begin(115200);
  while (! Serial)delay (1);
  Serial.println("USB mouse test");
  Mouse.click(MOUSE_LEFT);delay(1000);  //do a click
  Mouse.move(50,0);delay(1000);         //movie in all four directions
  Mouse.move(0,50);delay(1000);
  Mouse.move(-50,0);delay(1000);
  Mouse.move(0,-50);delay(1000);
  Mouse.move(0,0,-5);delay(1000);       //scroll down and up
  Mouse.move(0,0,5);delay(1000);
  Mouse.press(MOUSE_LEFT);delay(1000);  //hold the left button
  Mouse.move(50,0,0); delay(1000);      //drag
  Mouse.release(MOUSE_LEFT);delay(1000);//release the button
  Mouse.click(MOUSE_RIGHT);delay(1000); //try a right click
  Mouse.move(-30,-30); delay(1000);     //move away from the right-click menu that popped up
  Mouse.click(MOUSE_LEFT);delay(1000);  //do a left click to clear the pop-up
  Status();                             //print the buttons status
  Mouse.press(MOUSE_LEFT); delay(1000); //press each button, print status, then release all
  Status();
  Mouse.press(MOUSE_RIGHT); delay(1000);
  Status();
  Mouse.press(MOUSE_MIDDLE); delay(1000);
  Status();
  Mouse.release(MOUSE_ALL); delay(1000);
  Status();
  Mouse.move(-30,-30); delay(1000);     //move slightly to clear the pop-up
  Mouse.click(MOUSE_LEFT);delay(1000);  //clear of the pop-up
  Serial.println("Test completed");
};
void loop() {
}
