#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#else
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#endif

#include <MQTT.h>

const char ssid1[] = "foxx-house";
const char pass1[] = "nuevo1234567891234";

WiFiClient net;
MQTTClient client;

int Foco=2;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("Conectando con Wifi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  {
    Serial.print("\nConectando con MQTT...");
    while (!client.connect("dell_house", "housefox", "123andres")) {
      delay(1000);
      Serial.print("*");
    }
    Serial.println("\nConectado :D !");
    client.subscribe("/dll/Foco/casa");

  }
}

void RecibirMensaje(String &topic, String &payload) {
  Serial.println("incoming: " + topic + "-" + payload);

  if (payload == "1") {
    digitalWrite(Foco, 1);
    Serial.println(" Activada");

  }
  else {
    digitalWrite(Foco, 0);
    Serial.println(" Desactivada");
  }
}
void setup() {
  Serial.begin(115200);

  Serial.println("Iniciando Wifi");
  WiFi.mode(WIFI_STA);//Cambiar modo del Wi-Fi
  delay(100);
  wifiMulti.addAP(ssid1, pass1);
  //  wifiMulti.addAP(ssid2, pass2);
  //  wifiMulti.addAP(ssid3, pass3);

  client.begin("broker.shiftr.io", net);
  client.onMessage(RecibirMensaje);

  connect();
}

void loop() {

 
  client.loop();
  delay(10);

  if (!client.connected()) {
    connect();
  }
}
