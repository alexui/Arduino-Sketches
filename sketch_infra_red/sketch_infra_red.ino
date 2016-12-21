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
int receiver = 4;
IRrecv irrecv(receiver);
decode_results results;

void setup() {
  lcd.begin(16, 2);
  lcd.noCursor();
  irrecv.enableIRIn();
}

void loop() {
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
    // decodare comenzi pentru NEC AverMedia RM-KV
    if (results.value==0x20DF807F) lcd.print("Power");
    if (results.value==0x20DF609F) lcd.print("Mute");
    if (results.value==0x20DF906F) lcd.print("1");
    if (results.value==0x20DF50AF) lcd.print("2");
    if (results.value==0x20DFD02F) lcd.print("3");
    if (results.value==0x20DFD22D) lcd.print("OK");
    if (results.value==0x20DF20DF) lcd.print("Vol+");
    if (results.value==0x20DFA05F) lcd.print("Vol-");
    if (results.value==0x20DF40BF) lcd.print("CH+");
    if (results.value==0x20DFC03F) lcd.print("CH-");
    irrecv.resume();
  }
  delay(100);
}
