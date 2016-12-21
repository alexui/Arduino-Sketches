#include <LiquidCrystal.h>

const int rs = 12;
const int en = 11;
const int d4 = 9;
const int d5 = 8;
const int d6 = 7;
const int d7 = 6;
const int backlight = 13;

LiquidCrystal lcd(rs, LOW, en, d4, d5, d6, d7);

const int voltmetrupin = 0;
const float cap_inmagazinata = 1200.0;
const float temp_referinta = 25.0;
const float fact_temp = 0.04;
const float tensiune_max = 1.5;
const float tensiune_min = 0.2;
const float peukert_number = 1.2;
const float R1 = 220.0; // valori rezistente divizor tensiune
const float R2 = 220.0;

int val=0; // valoare achizitionata
float vout = 0.0; // tensiunea citita
float vin = 0.0; // tensiune baterie
float maxvin = 0.0; // valoarea maxima a tensiunii bateriei
float i = 0.0; //intesitate curent in mA
float cap_ramasa;
float temperatura = 0;
float durata_viata;

void setup() {
  lcd.begin(16, 2);
  lcd.noCursor();
}

void loop(){
  val = analogRead(voltmetrupin);
  vout = (val * 5.0) / 1024.0;
  vin = vout / (R2/(R1+R2));
  if (maxvin<vin) maxvin = vin;
  if (maxvin==0) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Conectati");
      lcd.setCursor(0,1);
      lcd.print("bateria...");
  }
  else {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(vin);
      lcd.setCursor(4,0);
      lcd.print("V @ ");
      lcd.setCursor(8,0);
      temperatura = GetTemp();
      lcd.print(temperatura);
      lcd.setCursor(12,0);
      lcd.print(char(223));
      lcd.print("C");
      lcd.setCursor(0,1);
      cap_ramasa = max(0, ((vin - tensiune_min) / (tensiune_max - tensiune_min)) * cap_inmagazinata);
      cap_ramasa = cap_ramasa + (cap_ramasa * (temperatura - temp_referinta) * fact_temp);
      lcd.print(cap_ramasa);
      lcd.setCursor(5,1);
      lcd.print("AH");
      lcd.setCursor(8,1);
      lcd.print("/");
      lcd.setCursor(10,1);
      i = (vin * 1000) / (R1+R2);
      durata_viata = ((cap_ramasa * 1000.0) / pow(i,peukert_number))/ 24;
    lcd.print(durata_viata); //zile
    }
 delay(5000);
}

float GetTemp(void) {
  unsigned int wADC;
  float rezultat;
  ADMUX = (1<<REFS1 ) | (1<<REFS0) | (1<<MUX3);
  ADCSRA |= (1<<ADEN);
  delay(20);
  ADCSRA |= (1<<ADSC);
  while (bit_is_set(ADCSRA,ADSC));
    wADC = ADCW;
  rezultat = (wADC - 324.31)/1.22;
  return (rezultat);
}
