#include <IRremote.h>
#include <IRremoteInt.h>

#include <LiquidCrystal.h>

const int rs = 12;
const int en = 11;
const int d4 = 9;
const int d5 = 8;
const int d6 = 7;
const int d7 = 6;

LiquidCrystal lcd(rs, LOW, en, d4, d5, d6, d7);

const int receiver = 4;
const int speakerPin = 3;
const int remote_command = 5;
IRrecv irrecv(receiver);
decode_results results;

volatile int stat = 0;

void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(remote_command, OUTPUT);
  lcd.begin(16, 2);
  lcd.noCursor();
  irrecv.enableIRIn();
}

void loop() {
  
  if (stat) {
      digitalWrite(remote_command, HIGH);
      delay(1000);
      digitalWrite(remote_command, LOW);
      delay(1000);
  }
  if (irrecv.decode(&results)) {
    lcd.setCursor(0,0);
    lcd.print(" ");
    lcd.setCursor(0,0);
    if (results.decode_type == UNKNOWN) {
      lcd.print("Unknown");
    }
    else if (results.decode_type == NEC) {
      lcd.print("NEC");
    }
    else if (results.decode_type == SONY) {
      lcd.print("SONY");
    }
    else if (results.decode_type == RC5) {
      lcd.print("RC5");
    }
    else if (results.decode_type == RC6) {
      lcd.print("RC6");
    }
    else if (results.decode_type == PANASONIC) {
      lcd.print("PANASONIC");
    }
    else if (results.decode_type == JVC) {
      lcd.print("JVC");
    }
    lcd.setCursor(0,1);
    lcd.print("               ");
    lcd.setCursor(0,1);
    lcd.print(results.value, HEX);
    lcd.print(" ");
    
    if (results.value == 0x8c03f) stat = !stat;
    else playTone(280,500);
    
    irrecv.resume();
  }
  delay(100);
}

void playTone(int tone, int duration){
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    //fiecare nota trimite HIGH la pin cu o anumita frecventa (duration/(ton*2))
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
