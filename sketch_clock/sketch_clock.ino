#include <util/delay.h>

volatile int nr_sec = 0; // ia variabila din RAM si nu din registru pt ca e mai sigur
const int leds [] = {2, 3, 4, 5, 6, 7, 8};
const int caracter = 9;
const int numbers [] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};

const int button1 = 10;
const int button2 = 11;
const int button3 = 12;

//Arduino are 16 MHz
void setup() {
  //timer oprit
  TCCR1A = 0;
  TCCR1B = 0;
  
  //alte initializari
  for (int i = 0; i < 7; i++)
    pinMode(leds[i], OUTPUT);
  pinMode(caracter, OUTPUT);
  digitalWrite(caracter, HIGH);
  
  TIMSK1 = (1 << TOIE1); //activare timer overflow
    
  //modul 2
  //TIMSK1 = 0x02;// activare in modul CTC
  //OCR1A = 0xF423; //init reg. de comparare
  //TCCR1B = 0x0C; // set clock 100 / set wgm12 ctc mode
}

//procedura de overflow
ISR (TIMER1_OVF_vect) {
  TCNT1 = 0x0BDC; //setare valoare initiala 65536 - 62500
  nr_sec++;
  if (nr_sec == 10) nr_sec = 0;
}

void print_character(int val) {
  for (int i = 0; i < 7; i++) {
      digitalWrite(leds[i], !(val%2)); //activ pe 0
      val = val/2;
  }
}

void loop() {
  
  if (digitalRead(button1) == LOW) {
    //pornire timer
    TCNT1 = 0x0BDC; //setare valoare initiala 65536 - 62500
    TCCR1B = (1 << CS12);  //1 MHZ / 256
    _delay_ms(200);
  }
  if (digitalRead(button2) == LOW) {
    TCCR1B = 0;
    _delay_ms(200);
  }
  if (digitalRead(button3) == LOW) {
    nr_sec = 0;
    _delay_ms(200);
  }
  
  print_character(numbers[nr_sec%10]);
}
