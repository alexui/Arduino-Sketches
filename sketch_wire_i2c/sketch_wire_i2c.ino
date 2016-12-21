#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 12;
const int en = 11;
const int d4 = 9;
const int d5 = 8;
const int d6 = 7;
const int d7 = 6;

LiquidCrystal lcd(rs, LOW, en, d4, d5, d6, d7);

const int tmpAdd = 0x48;
float temperatura;

void setup() {
  
  lcd.begin(16, 2);
  lcd.noCursor();
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  temperatura = getTemperature();
  lcd.setCursor(0, 1);
  if (temperatura < 0) {
    lcd.print("-");
    temperatura = - temperatura;
  }
  else
    if (temperatura < 10)
      lcd.print(" ");
  lcd.print(temperatura);
  Serial.println(temperatura);
  delay(5000);
}

float getTemperature() {
  byte MSB = 0x00;
  byte LSB= 0x00;
  int temp = 0;
  float tempCelsius = 0.0;
  
  Wire.beginTransmission(tmpAdd); //uC este master , pregateste o comunicatie cu disp de la adresa specificata
  //scrie in Pointer register - seteaza Temperature Register
  Wire.write(0x00); //pune in buffer 
  Wire.endTransmission(); //actiunea de transmitee a datelor
  Wire.requestFrom(tmpAdd, 2); //asteapta 2 octeti
  Wire.endTransmission();
  
  MSB = Wire.read(); //citeste octet dim TWDT
  LSB = Wire.read();
  
  //temperatura trebuie shiftata la dreapta cu 4 biti
  temp = ( MSB << 8 | LSB ) >> 4;
  
  Serial.print("Am citit : ");
  Serial.print(temp, DEC);
  Serial.print(" tradus: ");
  tempCelsius = temp * 0.0625;
  Serial.print(tempCelsius, 4);
  Serial.println();
  return tempCelsius; 
}
