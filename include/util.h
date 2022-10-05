#include <PubSubClient.h>

class state;
state parse(char *message);
void controller(PubSubClient, char *, state, float);
