#include <LiquidCrystal.h>
#include <util/delay.h>

const int rs = 12;
const int en = 11;
const int d4 = 9;
const int d5 = 8;
const int d6 = 7;
const int d7 = 6;
const int backlight = 13;

volatile int sec = 0;
volatile int minut = 0;
volatile int ora = 0;
volatile int zi = 1;
volatile int luna = 1;
volatile int an = 2015;

volatile int zile_luna [] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
volatile boolean backlight_on;
volatile byte set_mode;

LiquidCrystal lcd(rs, LOW, en, d4, d5, d6, d7);

void setup() {
  //activare timer
  TIMSK1 = (1 << TOIE1); //overflow
  TCCR1A = 0;
  TCNT1 = 0x0BDC; //setare valoare initiala 65536 - 62500
  TCCR1B = (1 << CS12);  //1 MHZ / 256
  
  //activare intreruperi
  EIMSK |= (1 << INT0);
  EIMSK |= (1 << INT1);
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT20);
  
  pinMode(backlight, OUTPUT);
  digitalWrite(backlight, LOW);
  backlight_on = false;
  
  //mod de funct. normal
  set_mode = 0;
  
  //configurare LCD
  lcd.begin(16, 2);
  lcd.noCursor();
}

void loop() {
  
  lcd.setCursor(0, 0);
  if (zi<10) lcd.print("0");
  lcd.print(zi);
  lcd.setCursor(2,0);
  lcd.print("/");
  if (luna<10) lcd.print("0");
  lcd.print(luna);
  lcd.setCursor(5,0);
  lcd.print("/");
  lcd.print(an);
  lcd.setCursor(0, 1);
  if (ora<10) lcd.print("0");
  lcd.print(ora);
  lcd.setCursor(2,1);
  lcd.print(":");
  if (minut<10) lcd.print("0");
  lcd.print(minut);
  lcd.setCursor(5,1);
  lcd.print(":");
  if (sec<10) lcd.print("0");
  lcd.print(sec);
  lcd.print(" ");
  
  if (set_mode!=0)
  {
    lcd.setCursor(11, 1);
    lcd.print("SET ");
    switch (set_mode) {
      case 1:
      lcd.print("Z");
      break;
      case 2:
      lcd.print("L");
      break;
      case 3:
      lcd.print("A");
      break;
      case 4:
      lcd.print("O");
      break;
      case 5:
      lcd.print("M");
      break;
      case 6:
      lcd.print("S");
      break;
    }
  }
  delay(500);
  lcd.clear();
}

//procedura de overflow
ISR (TIMER1_OVF_vect) {
  TCNT1 = 0x0BDC; //setare valoare initiala 65536 - 62500
  
  if (sec == 59) {
    if (minut == 59) {
      if (ora == 23) {
        if (zi == zile_luna[luna-1]) {
          if (luna == 12) {
            an++;
            luna = 1;
          }
          else luna++;
          zi = 1;
        }
        else zi++;
        ora = 0;
      }
      else ora++;
      minut = 0;
    }
    else minut++;
    sec = 0;
  }
  else sec++;
}

ISR (INT0_vect) {
  
  set_mode = (set_mode + 1) % 7;
  _delay_ms(200);  
}

ISR (INT1_vect) {
  switch (set_mode) {
    case 1: 
      if (zi == zile_luna[luna-1]) {
        if (luna == 12) {
            an++;
            luna = 1;
          }
          else luna++;
          zi = 1;
        }
      else zi++;
      break;
    case 2:
       if (luna == 12) {
            an++;
            luna = 1;
          }
        else luna++;
        break;
    case 3: 
      an++;
      break;
    case 4:
      if (ora == 23) {
        if (zi == zile_luna[luna]) {
          if (luna == 12) {
            an++;
            luna = 1;
          }
          else luna++;
          zi = 1;
        }
        else zi++;
        ora = 0;
      }
      else ora++;
      break;
    case 5:
      if (minut == 59) {
        if (ora == 23) {
          if (zi == zile_luna[luna]) {
            if (luna == 12) {
              an++;
              luna = 1;
            }
            else luna++;
            zi = 1;
          }
          else zi++;
          ora = 0;
        }
        else ora++;
        minut = 0;
      }
      else minut++;
      break;
    case 6:
      if (sec == 59) {
        if (minut == 59) {
          if (ora == 23) {
            if (zi == zile_luna[luna]) {
              if (luna == 12) {
                an++;
                luna = 1;
              }
              else luna++;
              zi = 1;
            }
            else zi++;
            ora = 0;
          }
          else ora++;
          minut = 0;
        }
        else minut++;
        sec = 0;
      }
      else sec++;
      break;
  }
  _delay_ms(200);
}

ISR (PCINT2_vect) {
  _delay_ms(20); // nu prindem de doua ori apasarea butonului
  if (!(PIND & 0x10)) {
    if (!backlight_on) {
      digitalWrite(backlight, HIGH);
      backlight_on = true;
    }
    else {
      digitalWrite(backlight, LOW);
      backlight_on = false;
    }
  }
}
