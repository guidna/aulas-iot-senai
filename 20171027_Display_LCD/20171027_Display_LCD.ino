// include the library code:
#include <LiquidCrystal.h>

int botao = A5;
int luz = 13;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int previousNumber = analogRead(botao);

void setup() {

  Serial.begin(9600);

  while (!Serial) {
  }
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Aguardando texto");

  pinMode(luz, HIGH);
}

void loop() {
  if(Serial.available()){
    writeText();
  }
  if (previousNumber + 5 > writeNumber()
      && ){
    writeNumber();
  }
  delay(100);
}

int writeNumber() {
  
  //receive the value from potentiometer
  int number = analogRead(botao);

  cleanDisplay(0 ,1);
  lcd.setCursor(0, 1);
  // print the value received
  lcd.print(number);
  
  Serial.println(number);
  
  previousNumber = number;
  
  return number;
  
}

void cleanDisplay(int y, int x) {
  // set the cursor to column y, line x
  // (note: line 2 is the second row, since counting begins with 0):
  lcd.setCursor(y, x);
  
  lcd.print("                ");
  
  
}
void writeText () {
  
  String text = Serial.readString();

  cleanDisplay(0, 0);
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print(text);

  Serial.println(text);
}
