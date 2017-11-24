#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>

/*#include <Ethernet.h> ALAN*/
#include <PubSubClient.h>

//=======================================================================
void callback(const char topic, byte* payload, unsigned int length);
//=======================================================================

char topicPub[] = "alarme";
char topicSub[] = "alarme";

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xAE, 0x03 };
IPAddress ip (192, 162, 1, 100);
char server[] = "m14.cloudmqtt.com";
int port = 15195;

char clientMQTTID[] = "MQTT-Senai";
char userMQTT[] = "casa01";
char passMQTT[] = "senha01";

EthernetClient ethClient;
PubSubClient client(server, port, callback, ethClient);

void setup() {

  serialSetup();
  ethernetSetup();

}

void loop() {

  inputRequest();
  client.loop();
  showInformation();

}
void serialSetup() {

  Serial.begin(9600);
  while (!Serial) {
  }
  Serial.println("Inicio");

}

void showInformation() {

  String message;
  char msgMQTT;



  Serial.println(message);

}
void inputRequest() {
  if (!client.connected()) {
    reconnectMQTT();
  }

}

void ethernetSetup() {

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Falha em configurar Ethernet usando DHCP");
    Ethernet.begin(mac, ip);
  }
  delay(1000);
  Serial.println("Ethernet Ok...");

}

void reconnectMQTT() {

  char messageMQTT[] = "Online";

  if (!client.connected()) {
    Serial.print("Conectando MQTT ...");

    if (client.connect(clientMQTTID, userMQTT, passMQTT)) {
      Serial.println("conectado");
      client.publish(topicPub, messageMQTT);
      if (!client.subscribe("Garage_Project")) {
        Serial.println("Erro na subscrição");
      } else {
        Serial.println("Subscrição realizada com sucesso - Porta");
      }

      if (!client.subscribe("Garage_Light")) {
        Serial.println("Erro na subscrição");
      } else {
        Serial.println("Subscrição realizada com sucesso - Luz");
      }

    } else {
      Serial.print("falha, rc=");
      Serial.print(client.state());
      Serial.println(" nova tentativa em 5 segundos");
    }
  }

}
void callback(const char topic, byte* payload, unsigned int length) {

  // handle message arrived
  Serial.print("Callback: ");
  Serial.println(String(topic));

  char* payloadAsChar = payload;

  // Workaround para pequeno bug na biblioteca
  payloadAsChar[length] = 0;

  // Converter em tipo String para conveniência
  String topicStr = String(topic);
  String msg = String(payloadAsChar);
  Serial.print("Topic received: "); Serial.println(String(topic));
  Serial.print("Message: "); Serial.println(msg);


  // Dentro do callback da biblioteca MQTT,
  // devemos usar Serial.flush() para garantir que as mensagens serão enviadas
  Serial.flush();

  // https://www.arduino.cc/en/Reference/StringToInt
  int msgComoNumero = msg.toInt();

  Serial.print("Numero recebido: "); Serial.println(msgComoNumero);
  Serial.flush();
  delay(1000);

}

