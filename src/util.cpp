
#include <PubSubClient.h>

class state
{
public:
    bool fire_detect;
    float smoke_detect;
    bool pull;
};

state parse(char *message)
{
}

void controller(PubSubClient client, char *topic, state state, float threshold)
{
    if (state.fire_detect || state.pull)
    {
        client.publish(topic, "{ sprikler: True }");
    }
    if (state.smoke_detect > threshold || state.fire_detect || state.pull)
    {
        client.publish(topic, "{ HVAC: vent, Lighting: Evac }");
        client.publish(topic, "{ Alarm: true }");
    }
}
