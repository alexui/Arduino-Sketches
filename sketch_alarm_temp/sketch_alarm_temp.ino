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
const float TLOW = 30.2f;
const float THIGH = 31.5f;
byte alarma = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.noCursor();
  Wire.begin();
  setLimit(TLOW, THIGH);
  Serial.begin(9600);
}

void setLimit(float low, float high) {
  byte MSB, LSB;
  int temp;
    
  temp = low / 0.0625;
  temp = temp << 4;
  LSB = (byte) (temp & 0xff);
  MSB = (byte) ((temp >> 8) & 0xff);
  Wire.beginTransmission(tmpAdd);
  //scrie in Pointer Register - seteaza TLOW register
  Wire.write(0x02);
  Wire.write(MSB);
  Wire.write(LSB);
  Wire.endTransmission();
  
  temp = high / 0.0625;
  temp = temp << 4;
  LSB = (byte) (temp & 0xff);
  MSB = (byte) ((temp >> 8) & 0xff);
  Wire.beginTransmission(tmpAdd);
  //scrie in Pointer Register - seteaza THIGH register
  Wire.write(0x03);
  Wire.write(MSB);
  Wire.write(LSB);
  Wire.endTransmission();
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

void loop(){
  float temperatura = 0.0;
  temperatura = getTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.setCursor(5, 0);
  if (temperatura >= 0)
    lcd.print(" ");
  else {
    lcd.print("-");
    temperatura = - temperatura;
  }
  if (temperatura < 10) 
    lcd.print(" ");
  lcd.print(temperatura);
  if (temperatura > THIGH) {
    lcd.setCursor(0,1);
    lcd.print("ALARMA");
    alarma=1;
  }
  else {
    if (alarma == 0) {
      lcd.setCursor(0, 1);
      lcd.print("      ");
    }
    else {
      if (temperatura < TLOW) alarma = 0;
    }
  }
  delay(1000);
}

