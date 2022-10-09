#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "util.h"

const int PIN_lighting = 10;
const int PIN_sprinkler = 11;
const int PIN_alarm = 12;

// WiFi
const char *ssid = "JAYAS";        // WiFi name
const char *password = "8806123K"; // password

// MQTT Broker
const char *mqtt_broker = "52.184.165.84";
const char *topic_alarm = "326project/smartbuilding/pv/<floorno>/<roomno>/current";
const char *topic_sprinkler = "326project/smartbuilding/pv/<floorno>/<roomno>/current";
const char *topic_lighting = "326project/smartbuilding/pv/<floorno>/<roomno>/current";
const char *mqtt_username = "co326a";
const char *mqtt_password = "safety";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length)
{
  char *message = new char[length];

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");

  for (int i = 0; i < length; i++)
  {
    message[i] = (char)payload[i];
  }

  Serial.println(message);
  Serial.println();
  Serial.println("-----------------------");

  controller(message, parse(message), topic);
}

void setup()
{
  pinMode(PIN_lighting, OUTPUT);
  pinMode(PIN_sprinkler, OUTPUT);
  pinMode(PIN_alarm, OUTPUT);

  // Set software serial baud to 115200;
  Serial.begin(115200);
  // connecting to a WiFi network
  WiFi.mode(WIFI_STA); // Optional
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  // connecting to an mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  while (!client.connected())
  {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the mqtt broker\n", client_id.c_str());

    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password))
    {
      Serial.println("mqtt broker connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  // publish and subscribe
  client.publish(topic_alarm, "status: ON");
  client.publish(topic_sprinkler, "status: ON");
  client.publish(topic_lighting, "status: ON");
  client.subscribe(topic_alarm);
  client.subscribe(topic_sprinkler);
  client.subscribe(topic_lighting);
}

void loop()
{
  client.loop();
}
