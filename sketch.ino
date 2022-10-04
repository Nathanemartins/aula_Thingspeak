#include "WiFi.h"
#include <DHTesp.h>
#include "HTTPClient.h"

#define LED 2 

const int relayPin_1 = 2;
const int relayPin_2 = 4;
const int DHT_PIN = 15;
const int pinoLED= 17;
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const String url = "https://api.thingspeak.com/update?api_key=JLC71UZ06WRWWSD6&";

HTTPClient http;
DHTesp dhtSensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Iniciando Setup");
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(WiFi.status());
    Serial.println("Finalizando setup");
  }
   //definindo saída e entrada do relay
  pinMode(LED, OUTPUT);
  pinMode(relayPin_1, OUTPUT);
  pinMode(relayPin_2, OUTPUT);
}
void loop() {
  // conectando ao servidor:
  float temperatura = 28.0;
  float humidade = 15.0;

  String path = url + "field1=" + String(temperatura) + "&field2=" + String(humidade);
  http.begin(path);
  int httpCode = http.GET();
  String payload = http.getString();

  Serial.println("HttpCode:" + String(httpCode));
  Serial.println("Payload:" + payload);

  //capturando temperatura e humidade
  delay(1000); 
   temperatura = dhtSensor.getTemperature();
   humidade = dhtSensor.getHumidity();
  //imprimindo dados
  
   Serial.println("Temperatura:" + String(temperatura, 2) + "C");
   Serial.println("Humidade:" + String(humidade, 1) + "%");
   
   digitalWrite (relayPin_2, HIGH);
   digitalWrite (relayPin_1, HIGH);
   delay(800);

   digitalWrite(pinoLED, (digitalRead(pinoLED)));
   digitalWrite(relayPin_1, LOW);
   digitalWrite(relayPin_2, LOW);
   delay(800);

}
