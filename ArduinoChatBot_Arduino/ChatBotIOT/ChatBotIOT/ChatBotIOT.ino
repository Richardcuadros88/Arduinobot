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
//const char ssid2[] = "TAMAYO";
//const char pass2[] = "andres1234567891234";
//const char ssid3[] = "ssid";
//const char pass3[] = "pass";

WiFiClient net;
MQTTClient client;

int foco2 = 3;
int Foco = 2;
unsigned long lastMillis = 0;

void connect() {
  Serial.print("Conectando con Wifi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.print("\nConectando con MQTT...");
  while (!client.connect("fox_house", "housefox", "123andres")) {
    Serial.print("*");
    delay(100);
  }
  Serial.println("\nConectado :D !");

  client.subscribe("/fH/foco/casa-casa2");
  client.subscribe("/fH/foco2/casa2");

}
void RecibirMensaje(String &topic, String &payload) {
  Serial.println("Mensaje: " + topic + " - " + payload);

  
  if (payload == "1") {
    digitalWrite(Foco, 1);
    Serial.println("Foco activado");
  }
  else {
    digitalWrite(Foco, 0);
    Serial.println("Foco Desactivado");
   }}
  
 void RecibirMensaje2(String &topic, String &payload) {
 Serial.println("Mensaje: " + topic + " - " + payload);
  if (payload == "1") {
    digitalWrite(foco2, 1);
    Serial.println("foco2 activado");
  }
  else {
    digitalWrite(foco2, 0);
    Serial.println("foco2 Desactivado");

  }
 }

void setup() {
  Serial.begin(115200);
  pinMode(foco2, OUTPUT);
  pinMode(Foco, OUTPUT);
  digitalWrite(foco2, 0);
  digitalWrite(Foco, 0);

  Serial.println("Iniciando Wifi");
  WiFi.mode(WIFI_STA);//Cambiar modo del Wi-Fi
  delay(100);
  wifiMulti.addAP(ssid1, pass1);
  //wifiMulti.addAP(ssid2, pass2);
  //wifiMulti.addAP(ssid3, pass3);

  client.begin("broker.shiftr.io", net);
  client.onMessage(RecibirMensaje);
  client.onMessage(RecibirMensaje2);
  connect();
}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    connect();
  }
}
