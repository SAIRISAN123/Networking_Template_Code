#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h> 
#include <ESP32Servo.h>  

const char* ssid = " ";                   // Your WiFi SSID
const char* password = " ";         // Your WiFi Password
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "topic/esp32";

WiFiClient espClient;
PubSubClient client(espClient);
                             

void setup() {
  Serial.begin(115200);  // Start Serial communication with the computer

  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  reconnect();
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Print the received message for debugging
  Serial.print("Message received: ");
  Serial.println(message);

  // Parse the JSON message
  StaticJsonDocument<200> doc;  // Allocate a JSON document
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.f_str());
    return;
  }

}

void reconnect() {
  // Attempt to connect to MQTT broker
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32_DAC")) {
      Serial.println("connected");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 second");
      delay(1000);
    }
  }
}

void loop() {
  // Reconnect to MQTT if connection is lost
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
