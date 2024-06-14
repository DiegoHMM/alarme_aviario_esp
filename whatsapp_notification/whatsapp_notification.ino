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

  analogReadResolution(12); // Configura a resolução do ADC para 12 bits

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
  int valorADC = analogRead(34);
  float tensao = (valorADC / 4095.0) * 3.3; // Converte o valor do ADC para tensão
  Serial.println(tensao);
  delay(1000); 

  if(tensao >= 2.5) { // Condição modificada para acionar quando a tensão for considerada alta
    if(flag) {
      Callmebot.whatsappMessage(PHONE_NUMBER, API_KEY, "Alarme disparado no aviário!");
      digitalWrite(2, HIGH);
      delay(10000);
      digitalWrite(2, LOW);
      flag = 0;
    }
  } else {
    flag = 1; 
  }
}
