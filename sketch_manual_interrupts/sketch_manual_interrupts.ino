#include <util/delay.h>

volatile int a1 = 0;
volatile int a2 = 0;
volatile int a3 = 0;

void setup() {
  EIMSK |= (1 << INT0);
  EIMSK |= (1 << INT1);
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT20);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Butonul 1 s-a apasat de ");
  Serial.print(a1, DEC);
  Serial.print(" ori.");
  Serial.println();
  
  Serial.print("Butonul 2 s-a apasat de ");
  Serial.print(a2, DEC);
  Serial.print(" ori.");
  Serial.println();
  
  Serial.print("Butonul 3 s-a apasat de ");
  Serial.print(a3, DEC);
  Serial.print(" ori.");
  Serial.println();
}

ISR (INT0_vect) { //intreruperile sunt dezactivate pe durata ex programului 
  a1++;
  _delay_ms(400); // nu se foloseste delay pt ca deja s-a activat INT0 iar delay lucreaza cu t0
}

ISR (INT1_vect) {
  a2++;
  _delay_ms(400);
}

ISR (PCINT2_vect) {
  a3++;
  _delay_ms(400);
}
