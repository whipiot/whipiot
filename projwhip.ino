#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define WIFI_STA_NAME "whip"
#define WIFI_STA_PASS  "dddddddd"
#define MQTT_SERVER   "broker.hivemq.com"
#define MQTT_PORT     1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_NAME     "whipiot"
WiFiClient client;
PubSubClient mqtt(client);
int num=0;
void callback(char* topic, byte* payload, unsigned int length) {
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");
 for (int i = 0; i < length; i++) {
  Serial.print((char)payload[i]);
 }
}
void setup() {
 Serial.begin(115200);
 WiFi.mode(WIFI_STA); 
 while (!Serial) ; 
  delay(250);
  Serial.println(WIFI_STA_NAME); 
  Serial.println("WIFI Connecting");
  WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS); //เชื่อมต่อ wifi
 while (num<20) {
  delay(500);
  Serial.print(".");
  num++;
 }
 if (WiFi.status() == WL_CONNECTED) {
  Serial.print("\n WiFi Connected. \n");
 }else{
  Serial.print("\n WIFI Connect fail. ");
 }
 mqtt.setServer(MQTT_SERVER, MQTT_PORT);
 mqtt.setCallback(callback);
}
void loop() {
 if (mqtt.connect(MQTT_NAME, MQTT_USERNAME, MQTT_PASSWORD)) {
  Serial.print("\n Publish message: ");
  if (mqtt.publish("whipiot2","hi hello สวัสดี") == true) { 
   //ส่งข้อความ "Arduino Test MQTT" ใน Topic = "TEST/MQTT"
   Serial.println("Success sending");
  }else{
   Serial.println("Fail sending");
  }
 }
delay(5000); // ใส่ delay ให้เว้นระยะส่งข้อความทุกๆ 5 วินาที
}
