#include <Mouse.h>

const int joyY_pin = A8;
const int joyX_pin = A7;

const int joystick_btpin = 14;

const int mouse_left_btpin = 15;
const int scrolldown_btpin = 16;
const int scrollup_btpin = 17;
const int close_btpin = 19;

const int custom_btpin = 18;


int rawx, rawy, x, y;
int threshold = 10;  // dead zone

int joybt, mouse_left, scrolldown, scrollup, custom;

int close;
int close_prev = HIGH;

void setup() {
  Serial.begin(11520);

  pinMode(joystick_btpin, INPUT_PULLUP);
  pinMode(mouse_left_btpin, INPUT_PULLUP);
  pinMode(custom_btpin, INPUT_PULLUP);
  pinMode(close_btpin, INPUT_PULLUP);
  pinMode(scrolldown_btpin, INPUT_PULLUP);
  pinMode(scrollup_btpin, INPUT_PULLUP);

  Mouse.begin();
}

void loop() {

  rawx = analogRead(joyX_pin);
  rawy = analogRead(joyY_pin);

  joybt = digitalRead(joystick_btpin);
  mouse_left = digitalRead(mouse_left_btpin);

  close = digitalRead(close_btpin);
  scrolldown = digitalRead(scrolldown_btpin);
  scrollup = digitalRead(scrollup_btpin);

  custom = digitalRead(custom_btpin);

  x = -(rawx - 512);
  y = rawy - 512;

  // dead zone
  if (abs(x) < threshold) x = 0;
  if (abs(y) < threshold) y = 0;

  // 
  x = x / 250;
  y = y / 250;

  Mouse.move(x, y);  // (x, y)


  /*if (custom == HIGH) {
  }
  else {
    y = rawy - 512;

    if (y > threshold) {
      // Joystick para baixo → Ctrl -
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEYPAD_MINUS);  
      delay(10);
      Keyboard.releaseAll();
      Serial.println("CTRL -");
      delay(300); 

    } else if (y < -threshold) {
      // Joystick para cima → Ctrl +
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEYPAD_PLUS);  
      delay(10);
      Keyboard.releaseAll();
      Serial.println("CTRL +");
      delay(300);  
    }
  }*/

  //Serial.printf("rx: %d | ry: %d || x: %d | y: %d", rawx, rawy, x, y);
  //Serial.printf(" joybt: %d | ml: %d || cl: %d | scrolldown: %d | scrollup: %d\n", joybt, mouse_left, close, scrolldown, scrollup);

  /**/


  // bts
  if (digitalRead(mouse_left_btpin) == LOW) Mouse.press(MOUSE_LEFT);
  else Mouse.release(MOUSE_LEFT);

  //Serial.printf("close: %d || close_prev: %d\n", close, close_prev);

  if (close == LOW && close_prev == HIGH) {
    // Ctrl + W
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('w');
    delay(10);
    Keyboard.releaseAll();
    //Serial.println("close");
  }

  // update close state
  close_prev = close;


  // scroll
  if (digitalRead(scrolldown_btpin) == LOW) {
    // Scroll down
    Mouse.scroll(-1);
    delay(100);
  }

  if (digitalRead(scrollup_btpin) == LOW) {
    // Scroll up
    Mouse.scroll(1);
    delay(100);
  }
  /**/

  delay(10);
}
