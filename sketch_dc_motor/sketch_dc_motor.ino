#include <LiquidCrystal.h>
#include <Util/delay.h>

//Se foloseste tranzistor pentru amplificarea curentului pt. DC Motor
//Arduino stats: https://www.arduino.cc/en/Main/arduinoBoardUno

const int rs = 12;
const int en = 11;
const int d4 = 9;
const int d5 = 8;
const int d6 = 7;
const int d7 = 6;

LiquidCrystal lcd(rs, LOW, en, d4, d5, d6, d7);

byte intreg[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};//segment de bara plin (2 unitati)
byte gol[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
};//segment de bara gol
byte inceput[8] = {
  B11111,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B11111,
};//segmentul de inceput de bara gol
byte jumate[8] = {
  B11111,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11111,
};//segmentul de inceput de bara numai jumatate
byte sfarsit[8] = {
  B11111,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B11111,
};//segmentul de sfarsit de bara gol
byte sfarsitjumatate[8] = {
  B11111,
  B11001,
  B11001,
  B11001,
  B11001,
  B11001,
  B11111,
};//segmentul de sfarsit de bara jumatate

volatile int valoare = 0;
float tensiune = 0;
const int motorPin = 5;

void setup()
{ //activare int0 si int1
  EIMSK |= (1 << INT0);
  EIMSK |= (1 << INT1);
  //activare PCI2 (buton 3 - PCINT20 - PCI2)
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1<<PCINT20);
  lcd.begin(16, 2);
  lcd.noCursor();
  lcd.createChar(0, inceput);
  lcd.createChar(1, sfarsit);
  lcd.createChar(2, jumate);
  lcd.createChar(3, intreg);
  lcd.createChar(4, gol);
  lcd.createChar(5, sfarsitjumatate);
}

void loop() { 
  lcd.setCursor(0, 0);
  lcd.print("Comanda: ");
  if (valoare<10) lcd.print(" ");
  if (valoare<100) lcd.print(" ");
  lcd.print(valoare);
  lcd.print(" ");
  tensiune = (valoare * 5.0) / 256.0;
  lcd.setCursor(0, 1);
  lcd.print(tensiune);
  lcd.print("V");
  lcd.print (" ");
  if (tensiune >= 0.55) lcd.write((byte)3);
  else {
    if (tensiune >= 0.30) lcd.write((byte)2);
    else lcd.write((byte)0);
  }
  for (int i=0;i<7;i++) {
    if (tensiune>=1.1 + i*0.55) lcd.write((byte)3);
    else {
      if (tensiune >= 30 + i*0.55) lcd.write((byte)2);
      else lcd.write((byte)4);
    }
  }
  if (tensiune >= 4.95) lcd.write((byte)3);
  else {
    if (tensiune >= 4.7) lcd.write((byte)5);
    else lcd.write((byte)1);
  }
  delay(1000);
}

ISR(INT0_vect){ 
  if (valoare > 0) valoare = valoare - 5;
  _delay_ms(200); 
}

ISR(INT1_vect){ 
  if (valoare < 255) valoare = valoare + 5;
  _delay_ms(200); 
}

ISR(PCINT2_vect){ 
  if (!(PIND & 0x10)) analogWrite(motorPin, valoare);
  _delay_ms(200); 
}
