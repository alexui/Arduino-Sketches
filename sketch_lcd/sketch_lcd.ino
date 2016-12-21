#include <LiquidCrystal.h>
#include <util/delay.h>

const int rs = 12;
const int en = 11;
const int d4 = 9;
const int d5 = 8;
const int d6 = 7;
const int d7 = 6;


volatile int nr_sec = 0; //timer

LiquidCrystal lcd(rs, LOW, en, d4, d5, d6, d7);

void setup() {  
  //timer stop
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = (1 << TOIE1); //activare timer overflow
  
  //activare intreruperi
  EIMSK |= (1 << INT0);
  EIMSK |= (1 << INT1);
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT20);
  
  //configurare LCD
  lcd.begin(16, 2);
  lcd.noCursor();
}

void loop() {
  lcd.setCursor(0, 1);
  if (nr_sec < 10) lcd.print("0");
  lcd.print(nr_sec);
  lcd.print(" ");
}
/*
//procedura de overflow
ISR (TIMER1_OVF_vect) {
  TCNT1 = 0x0BDC; //setare valoare initiala 65536 - 62500
  nr_sec++;
  if (nr_sec == 60) nr_sec = 0;
}
*/

ISR (INT0_vect) {
 //pornire timer
/*  TCNT1 = 0x0BDC; //setare valoare initiala 65536 - 62500
  TCCR1B = (1 << CS12);  //1 MHZ / 256
  _delay_ms(200);
  */
  nr_sec++;
  _delay_ms(200);
}

ISR (INT1_vect) {
  /*
  TCCR1B = 0;
  _delay_ms(200);
  */
  nr_sec--;
  _delay_ms(200);
}

ISR (PCINT2_vect) {
  /*
  nr_sec = 0;
  _delay_ms(200);
  */
  nr_sec++;
  _delay_ms(200);
}
