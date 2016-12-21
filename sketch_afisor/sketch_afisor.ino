const int leds [] = {2, 3, 4, 5, 6, 7, 8};
const int caracter = 9;
const int numbers [] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};

void setup() {
  for (int i = 0; i < 7; i++)
    pinMode(leds[i], OUTPUT);
  pinMode(caracter, OUTPUT);
}

void print_character(int val) {
  for (int i = 0; i < 7; i++) {
      digitalWrite(leds[i], !(val%2)); //activ pe 0
      val = val/2;
  }
}

void loop() {
  for ( int nr = 0; nr <= 9; nr++) {
    digitalWrite(caracter, HIGH);
    print_character(numbers[nr]);
    delay(1000);
    digitalWrite(caracter, LOW);
  }
/*  
  for (int i = 0; i < 7; i++) {
    digitalWrite(caracter, HIGH);
    for (int j = 0; j < 7; j++)
      if (j == i)
        digitalWrite(leds[j], LOW);
      else
        digitalWrite(leds[j], HIGH);  
    delay(1000);
    digitalWrite(caracter, LOW);
  }
*/ //activ pe 0
}
