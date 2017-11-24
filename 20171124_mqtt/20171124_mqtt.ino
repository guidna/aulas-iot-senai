#include <UIPEthernet.h>
#include <utility/logging.h>

/*
 Reconnecting MQTT example - non-blocking

 This sketch demonstrates how to keep the client connected
 using a non-blocking reconnect function. If the client loses
 its connection, it attempts to reconnect every 5 seconds
 without blocking the main loop.

*/

#include <SPI.h>
#include <PubSubClient.h>

// Update these with values suitable for your hardware/network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x02 };

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

EthernetClient ethClient;
PubSubClient client("m14.cloudmqtt.com", 19138, callback, ethClient);

long lastReconnectAttempt = 0;

boolean reconnect() {
  Serial.println("conectando...");
  if (client.connect("arduinoClient", "casa01", "senha01")) {
    Serial.println("conectado");
    // Once connected, publish an announcement...
    client.publish("alarme","hello world");
    // ... and resubscribe
    client.subscribe("alarme");
  }else{
    Serial.println("Erro ao conectar");  
  }
  return client.connected();
}

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac);
  delay(1500);
  lastReconnectAttempt = 0;
}


void loop()
{
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected

    client.loop();
  }

}
