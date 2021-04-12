/*
  MIT License

  Copyright (c) 2021 110 101 118 101 114 032 117 115 101 032 116 104 105 115 032 105 110 032 112 114 111 102 105 108 101

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/*
  Short description:
  with this sketch you can measure the time of pressing button, you can look on elapsed_time variable to get 
  time in ms. Change the value below to adjust well for your needs 
*/

//variables to change
unsigned long press_time = 2000; // time to accept click as a press action
unsigned int min_time = 300; // minimum time for click

#define button_pin D6
int led_builtin = LED_BUILTIN;

int btnState = 0;
int lastbtnState = 0;

unsigned long count_time = 0;
unsigned long end_time = 0;
unsigned long elapsed_time = 0;
bool flashing_led = false;


void setup() {
  Serial.begin(115200);
  pinMode(led_builtin, OUTPUT);
  //For INPUT_PULLUP look on: https://www.arduino.cc/en/Tutorial/DigitalInputPullup
  pinMode(button_pin, INPUT_PULLUP);//INPUT_PULLUP internal resistor for getting correct values from btn
  digitalWrite(led_builtin, HIGH);
  delay(500);
  digitalWrite(led_builtin, LOW);
}
  unsigned long Btn_check(){
    if(btnState == LOW){
      count_time = millis();
      Serial.println("Btn pressed");
    }else if(btnState == HIGH){
      end_time = millis();
      Serial.println("Btn released");
      elapsed_time = end_time - count_time;
      Serial.println(elapsed_time);
      if (elapsed_time > 300 && elapsed_time < press_time) {
      Serial.println("Button_status:clicked");
      flashing_led = true;
      } else if (elapsed_time >= press_time) {
      Serial.println("Button_status:pressed");
      flashing_led = false;
      }
    }
    return elapsed_time;
    elapsed_time = 0;
  }
void loop() {
  btnState = digitalRead(button_pin);
  if(btnState != lastbtnState){
    Btn_check();
    delay(400);
  }
  lastbtnState = btnState;
  //Sometimes the boards have inverted leds like ESP8266
  if(flashing_led == true){
    digitalWrite(led_builtin, HIGH);
  }
  if(flashing_led == false){
    digitalWrite(led_builtin, LOW);
  }
}
