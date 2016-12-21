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

volatile int mod = 0;
volatile int track = 0;
volatile int n;

const int length[6] = {73,69,71,29,51,77}; // numarul de note din fiecare piesa

const char * notes[6] = \
  {"ggagsed deggsgg ggagsed deggsgg DCbCDbCbabCabagabgagsgasgsesgeseddeggsgg ", \
  "ddaagfedcdefga ddaagfedcdefga avgavCDagfdefgfgavaagfedfedgfgavCDagfed" , \
  "cfffgagavCavafggfcfffgagavCavafggffaCDCvagfgavCcfagfccfffgagavCavafggf " , \
  "faagfvvagaCCbCaDCvagfeagffef ", \
  "aavCagfgagdgavCaggfgagff vavCDDaaCagfecavCagfgagff ", \
  "cffefaagCCCvagacffefaagCffeedcCCCfvaagCCCfvaagDDDCvavgavCffgaDDDCvavgavCffgf "};

const int beats[6][77] = {
  {2,2,1,1,1,1,4,2,2,2,2,2,2,4,2,2,2,2,1,1,1,1,4,2,2,2,2,2,2,4,2,2,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,2,2,2,2,2,2,4,2,2 }, \
  {2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,4,2,2,2,2,2,2,4,1,1,2,4,2,2,2,2,2,2,2,2,2,2,8 } , \
  {2,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,2,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,1,1,3,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,4,4,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,2 } , \
  { 2,3,1,2,2,2,2,2,2,2,2,2,2,6,2,3,1,2,2,2,2,2,2,2,2,2,2,6,2 }, \
  { 2,3,1,2,2,4,4,3,1,2,2,8,3,1,2,2,3,1,4,2,2,3,1,6,2,3,1,2,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,4,4,2,2,3,1,8,8}, \
  {2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,1,1,3,1,2,2,4,3,1,2,2,2,2,4,2,1,1,3,1,2,2,4,8} };

const int tempo[6] = {200,300,300,300,300,300};

const char * piesa[6] = {"Ding Dong Merrily on High | ", \
  "God Rest Ye Merry Gentlemen | ", \
  "O Little Town of Bethlehem | ", \
  "While Shephards Watched | ", \
  "In The Bleak Midwinter | ", \
  "Hark the Herald | " };
  
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
    lcd.print("Stop");
    lcd.setCursor(5,0);
    lcd.print("Piesa ");
    lcd.print(track+1);
    lcd.setCursor(0,1);
    lcd.print(" ");
  }
  else {
    for (n = 0; n < length[track]; n++) {
      if (mod==0) break;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Play");
      lcd.setCursor(5,0);
      lcd.print("Piesa ");
      lcd.print(track+1);
      lcd.setCursor(0,1);
      for (int j=n; j<(n + strlen(piesa[track])); j++) lcd.print(piesa[track][j % strlen(piesa[track])]);
      if (notes[track][n] == ' ') 
        delay(beats[track][n] * tempo[track]); // pauză
      else 
        playNote(notes[track][n], beats[track][n] * tempo[track]);
    }
    //pauza intre note
    delay(tempo[track]/2);
  }
}

ISR(INT0_vect) {
  mod=!mod;
  _delay_ms(400);
}
ISR(INT1_vect) {
  track++;
  track = (track % 6);
  n = 0; // resetez la prima nota din melodie
  _delay_ms(400);
}
  
