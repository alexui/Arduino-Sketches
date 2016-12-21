#include <util/delay.h>

int leds [] = {3, 5, 6, 9, 10, 11};

void setup() {
  for (int i = 0; i < 6; i++)
    pinMode(leds[i], OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int alege = 0;
  Serial.println("Joc de lumini");
  Serial.println("Alegeti varianta de joc 1-2");
  while (alege < '1' || alege > '2' ) {
    alege = Serial.read();
    delay(1000); 
  }
  alege = alege - 48;
  Serial.print("Ati ales jocul: ");
  Serial.print(alege, DEC);
  Serial.println();
  Serial.println("Pentru restart apasati reset.");
  switch (alege) {
    case 1:
      joc1();
    case 2:
      joc2();
  }  
}

void joc1() {
 while (1) {
   for (int i = 0; i < 6; i+=2)
     for (int j = 0; j < 240; j+=20) {
       analogWrite(leds[i], j);
      _delay_ms(50);
     }
   _delay_ms(1000);
   for (int i = 0; i < 6; i+=2)
     for (int j = 240; j > -1; j-=20) {
       analogWrite(leds[i], j);
       _delay_ms(50);
     }
   _delay_ms(1000);     
   for (int i = 1; i < 6; i+=2)
     for (int j = 0; j < 240; j+=20) {
       analogWrite(leds[i], j);
       _delay_ms(50);
     }
   _delay_ms(1000);
   for (int i = 1; i < 6; i+=2)
     for (int j = 240; j > -1; j-=20) {
       analogWrite(leds[i], j);
       _delay_ms(50);
     }
   _delay_ms(1000);
 }   
}

void joc2() {
  while (1) {
    for (int i = 0; i < 6; i++ )
      for (int j = 0; j < 240; j += 20) {
        analogWrite(leds[i], j);
        _delay_ms(50); 
      }
    _delay_ms(500);
    for (int i = 5; i > -1 ; i-- )
      for (int j = 240; j > -1; j -= 20) {
        analogWrite(leds[i], j);
        _delay_ms(50); 
      } 
    _delay_ms(500); 
  } 
}
