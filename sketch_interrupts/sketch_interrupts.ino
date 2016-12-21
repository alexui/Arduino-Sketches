const int button3 = 4;
volatile int a1 = 0;
volatile int a2 = 0;
int a3 = 0;

void setup() {
  attachInterrupt(0, ISR_b1, FALLING); //cand pinul trece din 1 in 0
  attachInterrupt(1, ISR_b2, FALLING);
  Serial.begin(9600);
}

void loop() {
  if ((PIND & (1 << button3)) == 0) {
    a3++;
    Serial.print("Butonul 3 s-a apasat de ");
    Serial.print(a3, DEC);
    Serial.print(" ori.");
    Serial.println();
    //debouncing software
    delay(200);
  }
}

void ISR_b1() {
  a1++;
  Serial.print("Butonul 1 s-a apasat de ");
  Serial.print(a1, DEC);
  Serial.print(" ori.");
  Serial.println();
  //debouncing software
  delay(300);
}

void ISR_b2() {
  a2++;
  Serial.print("Butonul 2 s-a apasat de ");
  Serial.print(a2, DEC);
  Serial.print(" ori.");
  Serial.println();
  //debouncing software
  delay(300);
}
