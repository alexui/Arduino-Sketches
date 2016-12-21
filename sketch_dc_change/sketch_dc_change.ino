const int comandaPin = 11;
const int in1Pin = 10;
const int in2Pin = 9;
const int potPin = 0;
const int butPin = 2;

void setup() { 
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(comandaPin, OUTPUT);
  pinMode(butPin, INPUT);
  Serial.begin(9600);
}

void loop() { 
  int speed = analogRead(potPin) / 4;
 // Serial.println(speed);
  boolean reverse = digitalRead(butPin);
  setMotor(speed, reverse); 
}

void setMotor(int speed, boolean reverse) { 
  analogWrite(comandaPin, speed);
  digitalWrite(in1Pin, !reverse);
  digitalWrite(in2Pin, reverse); 
}

//https://www.youtube.com/watch?v=5nDaHJqruq0 very useful
