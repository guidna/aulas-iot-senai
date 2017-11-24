#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {A3, A2, A1, A0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, A5, A4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

bool tapyingPass = false;

String senhaDigitada;
String senha = "1557";

void setup(){
  Serial.begin(9600);

  pinMode(A0, INPUT);
}
  
void loop(){
  char key = keypad.getKey();
    
    if (key){
      
      if((key == '#') &&(senhaDigitada != "")) {
          tapyingPass = false;
          
          Serial.println("Terminou de digitar a senha.");
          Serial.println("Senha: ");
          Serial.println(senhaDigitada);
          
          if (senhaDigitada == senha){
            Serial.println("Alarme desativado");
          } else {
            Serial.println("Corre ladrão!");
          }
          
          senhaDigitada = "";
        } else {
            Serial.println("Digite uma senha");
     }
      
      if(tapyingPass){
        senhaDigitada += key; 
        Serial.print("Senha digitada :");
        Serial.println(senhaDigitada);
      }
      
      if(key == '*'){
        tapyingPass = true;
        Serial.println("Começou a digitar a senha...");
      }

    }
}
