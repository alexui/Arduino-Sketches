const int latchPin = 4;
const int clockPin = 3;
const int dataPin = 2; 

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  digitalWrite(latchPin, HIGH);  
}

void loop() {
/*  int alege = 0;
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
  */
//  switch (alege) {
//    case 1:
//      joc1();
//    case 2:
//      joc2();
//  }
 // joc1();
 f();
}

void f() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 240);
  delay(1000);
  digitalWrite(latchPin, HIGH);  
  delay(1000);
}

void joc1() {
  while (1) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 170); //10101010
    digitalWrite(latchPin, HIGH);
    delay(1000);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 85); //01010101
    digitalWrite(latchPin, HIGH);
    delay(1000);
  }
}

void joc2() {
  int afisare = 0;
  while(1) {
    for ( int i = 0; i < 9; i++) {
      afisare += 1<<i; //1<<afisare + 1
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, afisare); //01010101
      digitalWrite(latchPin, HIGH);
      delay(500);      
    }
    for ( int i = 0; i < 9; i++) {
      afisare -= 1<<i; //1<<afisare + 1
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, afisare); //01010101
      digitalWrite(latchPin, HIGH);
      delay(500);      
    }
  }  
}
