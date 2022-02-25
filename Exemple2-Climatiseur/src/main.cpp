#include <Arduino.h>
 
const int PIN_LED = 5;
const int PIN_BUTTON = 15;
bool _buttonPressed = true;
 
void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  // Par défaut on ouvre le climatiseur
  digitalWrite(PIN_LED, HIGH);
  Serial.println("Programme démarré");
}
 
void loop() {
  int buttonState = digitalRead(PIN_BUTTON);
  if(buttonState == 1 && !_buttonPressed) {
    Serial.println("Fenêtre fermée, on ouvre le climatiseur");
    _buttonPressed = 1;
    // ouvrir le climatiseur en choisissant le voltage HIGH
    digitalWrite(PIN_LED, HIGH);
  }
  else if(buttonState == 0 && _buttonPressed) {
    Serial.println("Fenêtre ouverte, on ferme le climatiseur");
    _buttonPressed = 0;
    // fermer le climatiseur en choisissant le voltage LOW
    digitalWrite(PIN_LED, LOW);
  }
}
