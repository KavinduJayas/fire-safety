
#include <PubSubClient.h>
#include <ArduinoJson.h>

extern const int PIN_lighting1;
extern const int PIN_lighting2;
extern const int PIN_sprinkler;
extern const int PIN_alarm;
extern const char *topic_alarm;
extern const char *topic_sprinkler;
extern const char *topic_lighting1;
extern const char *topic_lighting2;

int parse(char *message)
{
    Serial.println("parser started");
    StaticJsonDocument<200> doc;
    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, message);
    Serial.println("deserialized");

    // Test if parsing succeeds.
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return 0;
    }

    Serial.println("acessing state");
    const int state = doc["state"];
    Serial.println(state);
    Serial.println("state accessed");
    return state;
}

void controller(char *topic, char *message)
{
    Serial.println(F("inside controller"));
    Serial.println(F(topic_alarm));
    Serial.println(F(topic));

    if (strcmp(topic, topic_alarm) == 0)
    {
        Serial.println(F("topic alarm"));

        if (parse(message))
        {
            digitalWrite(PIN_alarm, HIGH);
            Serial.println(F("alarm: HIGH"));
        }
        else
        {
            digitalWrite(PIN_alarm, LOW);
            Serial.println(F("alarm: LOW"));
        }
    }
    if (strcmp(topic, topic_sprinkler) == 0)
    {
        Serial.println(F("topic sprinkler"));
        if (parse(message))
        {
            digitalWrite(PIN_sprinkler, HIGH);
            Serial.println(F("PIN_sprinkler: HIGH"));
        }
        else
        {
            digitalWrite(PIN_sprinkler, LOW);
            Serial.println(F("PIN_sprinkler: LOW"));
        }
    }
    if (strcmp(topic, topic_lighting1) == 0)
    {
        Serial.println(F("topic lighting1"));
        if (parse(message))
        {
            digitalWrite(PIN_lighting1, HIGH);
            Serial.println(F("PIN_lighting1: HIGH"));
        }
        else
        {
            digitalWrite(PIN_lighting1, LOW);
        }
    }
    if (strcmp(topic, topic_lighting2) == 0)
    {
        Serial.println(F("topic lighting2"));
        if (parse(message))
        {
            digitalWrite(PIN_lighting2, HIGH);
            Serial.println(F("PIN_lighting2: HIGH"));
        }
        else
        {
            digitalWrite(PIN_lighting2, LOW);
        }
    }
}