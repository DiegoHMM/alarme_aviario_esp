#include <WiFi.h>
#include <UrlEncode.h>
#include <Callmebot_ESP32.h>
#include "config.h"

bool flag = 1;


void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  pinMode(2, OUTPUT);
  pinMode(23, INPUT_PULLDOWN);

  Serial.println("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado ao WiFi neste IP ");
  Serial.println(WiFi.localIP());

  Callmebot.whatsappMessage(PHONE_NUMBER, API_KEY, "Bot iniciado");
}



void loop() {
  if(digitalRead(23) == HIGH) {
    if(flag) {
      Callmebot.whatsappMessage(PHONE_NUMBER, API_KEY, "ALERTA ALERTA!");
      digitalWrite(2, HIGH);
      delay(400);
      digitalWrite(2, LOW);
      flag = 0;
    }
  } else {
    flag = 1; 
  }
}


