#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <config.h>

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

bool flag = 1;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  pinMode(2, OUTPUT);
  pinMode(23, INPUT_PULLDOWN);

  

  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org");  // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  bot.sendMessage(CHAT_ID, "Bot iniciou", "");//envia mensagem dizendo que iniciou o BOT
}

void loop() {
  if(digitalRead(23) == HIGH) {
    if (flag) {
      bot.sendMessage(CHAT_ID, "Alerta", "");
      digitalWrite(2, HIGH);
      delay(400);
      digitalWrite(2, LOW);
      flag = 0;
    }
  } else {
    flag = 1;
  }
}