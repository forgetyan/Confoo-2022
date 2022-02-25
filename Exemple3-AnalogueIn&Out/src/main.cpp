#include <Arduino.h>
 
 
const int PIN_LED = 5;
const int PIN_SENSOR = 32;
const int CHANNEL_PWM = 1;
const int PWM_FREQENCY = 1000;
 
void setup() {
  pinMode(PIN_SENSOR, INPUT);
 
  ledcAttachPin(PIN_LED, CHANNEL_PWM);
  ledcSetup(CHANNEL_PWM, PWM_FREQENCY, 8);
}
 
void loop() {
  // Lire la valeur analogique
  int sensorValue = analogRead(PIN_SENSOR); // Valeur de 0 à 4095
  // Envoyer le signal à la lumière
  ledcWrite(CHANNEL_PWM, sensorValue * 255 / 4095); // Valeur de 0 à 255
}
