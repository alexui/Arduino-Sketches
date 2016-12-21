#include <LiquidCrystal.h>
#include <Util/delay.h>

const int rs = 12;
const int en = 11;
const int d4 = 9;
const int d5 = 8;
const int d6 = 7;
const int d7 = 6;

LiquidCrystal lcd(rs, LOW, en, d4, d5, d6, d7);

const int speakerPin = 4;
volatile int mod = 0; // 0 - stop, 1 - play, 2 - pauza

const int length = 64; // 18+18+12+16
const char notes[] = "agbCgCbgDCCgbgCafgDbafCaagDaCaCgbDbDaaDagfaafDaDaDgaagfaggbabgCbC";
const int beats[] = {1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1, \
  1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1, \
  1,1,1,1,1,1,1,1,1,1,1,1, \
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
  const int tempo = 300;
  const char * versuri[] = {"Un zam-bet de co", \
  "pil si o floa-re", \
  "Un ghi-o-cel ", \
  "ie-sit din nea ", \
  "Si o pri-ma ra ", \
  "za de la soa-re ", \
  "Au a-lun-gat ", \
  "re-gi-na rea ", \
  "Ea a ple-cat ", \
  "Spu-nand ca se ", \
  "va raz-bu-na ", \
  "Ca se va in ", \
  "toar-ce sa dea ", \
  "Iar fulgi de nea", \
  "si vre-me rea "};

const int karaoke[64][2] = { {0,0}, {0,4}, {0,8}, {0,11}, {0,14}, \
  {1,1}, {1,4}, {1,7}, {1,10}, {1,14}, \
  {2,0}, {2,4}, {2,7}, {2,10}, \
  {3,0}, {3,4}, {3,8}, {3,12}, \
  {4,0}, {4,3}, {4,6}, {4,9}, {4,12}, \
  {5,0}, {5,3}, {5,6}, {5,10}, {5,13}, \
  {6,0}, {6,3}, {6,6}, {6,10}, \
  {7,0}, {7,3}, {7,6}, {7,10}, \
  {8,0}, {8,3}, {8,6}, {8,10}, \
  {9,1}, {9,5}, {9,9}, {9,12}, \
  {10,0}, {10,4}, {10,7}, {10,10}, \
  {11,0}, {11,3}, {11,6}, {11,9}, \
  {12,1}, {12,5}, {12,8}, {12,12}, \
  {13,1}, {13,6}, {13,10}, {13,14}, \
  {14,0}, {14,4}, {14,7}, {14,11}};
  
void playTone(int tone, int duration){
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    //fiecare nota trimite HIGH la pin cu o anumita frecventa (duration/(ton*2))
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  const char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' }; // note
  const int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758 };
  // frecvente
  for (int i = 0; i < 12; i++) {
    if (names[i] == note) playTone(tones[i], duration);
  } 
}

void setup() { 
  pinMode(speakerPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.noCursor();
  EIMSK |= (1 << INT0);
  EIMSK |= (1 << INT1);
}

void loop() {
  if (mod==0) {
    lcd.setCursor(0,0);
    lcd.print("Stop ");
    lcd.setCursor(0,1);
    lcd.print(" ");
  }
  else {
    for (int n = 0; n < length; n++) {
      lcd.clear();
      if (mod == 0) break;
      while (mod == 2) {
        lcd.setCursor(0,0);
        lcd.print("Pauza ");
      }
      lcd.setCursor(0,1);
      lcd.print(versuri[karaoke[n][0]]);
      lcd.setCursor(0,0);
      lcd.print("     ");
      lcd.setCursor(karaoke[n][1],0);
      lcd.print("o");
      if (notes[n] == ' ') delay(beats[n] * tempo);
      else playNote(notes[n], beats[n] * tempo);
     // delay(tempo / 2);
    }
    delay(1000);
  }
}

ISR(INT0_vect)
{
  if (mod == 1) mod = 2;
  else if (mod == 2) mod = 1;
  _delay_ms(400);
}

ISR(INT1_vect) {
  if (mod == 0) mod = 1;
  else mod = 0;
  _delay_ms(400);
}
