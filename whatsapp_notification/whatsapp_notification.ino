#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>
#include <config.h>

bool flag = 1;

void sendMessage(String message) {

  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + PHONE_NUMBER + "&apikey=" + API_KEY + "&text=" + urlEncode(message);
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200) {
    Serial.print("Mensagem enviada com sucesso");
  } else {
    Serial.println("Erro no envio da mensagem");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}


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
}



void loop() {
  if(digitalRead(23) == HIGH) {
    if(flag) {
      sendMessage("ALERTA ALERTA!");
      digitalWrite(2, HIGH);
      delay(400);
      digitalWrite(2, LOW);
      flag = 0;
    }
  } else {
    flag = 1; 
  }
}


