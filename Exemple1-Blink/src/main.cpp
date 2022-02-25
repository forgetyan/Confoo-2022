#include <Arduino.h>
 
const int PIN_LED = 5;
void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                   // wait for a second
  digitalWrite(PIN_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                   // wait for a second
}
