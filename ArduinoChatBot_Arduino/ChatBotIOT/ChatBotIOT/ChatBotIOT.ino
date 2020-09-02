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

int Led = 3;
int Foco = 2;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("Conectando con Wifi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.print("\nConectando con MQTT...");
  while (!client.connect("fox_house", "housefox", "123andres")) {
    delay(1000);
    Serial.print("*");
  }

  Serial.println("\nConectado :D !");

  client.subscribe("/fH/habitacion/casa");
  client.subscribe("/fs/sala/casa");
}

void RecibirMensaje(String &topic, String &payload) 
{
  Serial.println("Mensaje: " + topic + " - " + payload);
  if (payload == "1") {
    digitalWrite(Foco, 1);
    //digitalWrite(Led,1);
    Serial.println("iluminacion Activada");
  }
  else {
    digitalWrite(Foco, 0);
    //digitalWrite(Led, 0);
    Serial.println("iluminacion Desactivada");
  }}

  void RecibirMensaje2(String &topic, String &payload) 
 {
 Serial.println("Mensaje: " + topic + " - " + payload);
 if (payload == "1") {
    digitalWrite(Led, 1);
    Serial.println("iluminacion Activada2");
  }
  else {
    digitalWrite(Led, 0);
   Serial.println("iluminacion Desactivada2");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(Led, OUTPUT);
  pinMode(Foco, OUTPUT);
  digitalWrite(Led, 0);
  digitalWrite(Foco, 0);

  Serial.println("Iniciando Wifi");
  WiFi.mode(WIFI_STA);//Cambiar modo del Wi-Fi
  delay(100);
  wifiMulti.addAP(ssid1, pass1);
  //wifiMulti.addAP(ssid2, pass2);
 // wifiMulti.addAP(ssid3, pass3);

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
