#include <util/delay.h>

const int leds [] = {2, 3, 4, 5, 6, 7, 8};
const int caracter = 9;
const int numbers [] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
volatile int v = 0;
/*
const int button1 = 10;
const int button2 = 11;
const int button3 = 12;
*/
void setup() {
  for (int i = 0; i < 7; i++)
    pinMode(leds[i], OUTPUT);
  pinMode(caracter, OUTPUT); 
  digitalWrite(caracter, HIGH);
/*  
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
*/
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT2) | (1 << PCINT3) | (1 << PCINT4);
}

void print_character(int val) {
  for (int i = 0; i < 7; i++) {
      digitalWrite(leds[i], !(val%2)); //activ pe 0
      val = val/2;
  }
}

ISR (PCINT0_vect) {
  v = v + 1;
  v = v%10;
 // _delay_ms(400);
}

ISR (PCINT3_vect) {
  if (v != 0)
    v--;
  _delay_ms(100);
}

ISR (PCINT4_vect) {
  v = 0;
  //_delay_ms(100);
}

void loop() {
/*  if (digitalRead(button1) == LOW) {
    v++;
    v = v%10;
    delay(200);
  }
  if (digitalRead(button2) == LOW) {
    if (v != 0)
      v--;
    delay(200);
  }
  if (digitalRead(button3) == LOW) {
    v = 0;
    delay(200);
  }
  */
//  digitalWrite(caracter, HIGH); asa se afiseaza intermitent
  print_character(numbers[v]);
  delay(200);
//  digitalWrite(caracter, LOW);
}
