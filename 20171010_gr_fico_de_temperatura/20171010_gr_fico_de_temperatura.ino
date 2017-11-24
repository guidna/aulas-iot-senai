#include <UIPEthernet.h>
#include <utility/logging.h>

const int LM35 = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  float temperatura = (float(analogRead(LM35))*5/(1023))/0.01;
  Serial.println(temperatura);
  delay(100);
}
