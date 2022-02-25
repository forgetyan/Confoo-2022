#include <Arduino.h>
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "main.h"

const int PIN_TEMP_SENSOR = 32;

// Wifi
#define WLAN_SSID "Drake-guest"
#define WLAN_PASS "IoT@Confoo!"

// Adafruit
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "confoo"
#define AIO_KEY         "aio_ESGU41NHMXLa8x5j16sAeRbycZcE"


WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish temperaturePublisher = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN_TEMP_SENSOR, INPUT);
  connectWifi();
}

void loop() {
  // S'assurer d'être connecté à MQTT
  MQTT_connect();

  // Lire la valeur analogique, on va supposer qu'il s'agit de température
  int sensorValue = analogRead(PIN_TEMP_SENSOR); // Valeur de 0 à 4095
  float temperature = (round(((float)sensorValue) / 4095 * 4000) / 100) - 10; // On converti la valeur de -10 à 30 degrés avec 2 décimales
  Serial.println(temperature); // On affiche la température dans la console
  // On envoie la température sur Adafruit.io
  temperaturePublisher.publish(temperature);
  // Attendre 5 secondes
  delay(5000);
}

void connectWifi() {
  WiFi.mode(WIFI_STA); // Mode Station donc on es un client; pas un access point
  WiFi.begin(WLAN_SSID, WLAN_PASS); // On se connecte au Wifi avec les identifiants
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) { // On attend d'être connectés
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP()); // On affiche notre adresse IP
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}
