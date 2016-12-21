const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
int a1 = 0;
int a2 = 0;
int a3 = 0;

void setup() {
  pinMode(button1, INPUT); //se intapla si implicit
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(button1) == LOW) {
    a1++;
    Serial.print("Butonul 1 s-a apasat de ");
    Serial.print(a1, DEC);
    Serial.print(" ori.");
    Serial.println();
    //debouncing software
    delay(200);
  }
  if (digitalRead(button2) == LOW) {
    a2++;
    Serial.print("Butonul 2 s-a apasat de ");
    Serial.print(a2, DEC);
    Serial.print(" ori.");
    Serial.println();
    //debouncing software
    delay(200);
  }
  if (digitalRead(button3) == LOW) {
    a3++;
    Serial.print("Butonul 3 s-a apasat de ");
    Serial.print(a3, DEC);
    Serial.print(" ori.");
    Serial.println();
    //debouncing software
    delay(200);
  }
}
