char tabla [] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
short mutari = 0;

void setup() {
   Serial.begin(9600); 
}

void loop () {

//afisare mesaj bun venit  
   Serial.println ("Salut!");
   Serial.println ("Tu vei muta primul - esti cu X.");
   Serial.println ("Tabla de jo are pozitii numerotate de la 1 la 9.");
   Serial.println ("1 2 3");
   Serial.println ("4 5 6");
   Serial.println ("7 8 9");
   Serial.println ("Alege o pozitie de la 1 la 9.");
   
//preluare caracter utilizator 
  do {
    mutareX();
    if(victorie()) break;
    mutare0();
    afisare();
  } while(!victorie());

  delay (5000);
  for (int i = 0; i < 100; i++) Serial.println ();
  for (int i = 0; i < 9; i++) tabla[i] = '-';
  mutari = 0;
}

boolean victorie () {
  char winner = '-';
  //linia 1
  if(tabla[0] == tabla[1] && tabla[1] == tabla[2]) winner = tabla[0]; 
  //col 1 
  if(tabla[0] == tabla[3] && tabla[3] == tabla[6]) winner = tabla[0];
  //linia 2
  if(tabla[3] == tabla[4] && tabla[4] == tabla[5]) winner = tabla[3];
  //col 2
  if(tabla[1] == tabla[4] && tabla[4] == tabla[7]) winner = tabla[1];
  //linia 3
  if(tabla[6] == tabla[7] && tabla[7] == tabla[8]) winner = tabla[0];
  //col 3
  if(tabla[2] == tabla[5] && tabla[5] == tabla[8]) winner = tabla[2];
  //diag 1
  if(tabla[0] == tabla[4] && tabla[4] == tabla[8]) winner = tabla[0];
  //diag 2
  if(tabla[2] == tabla[4] && tabla[4] == tabla[6]) winner = tabla[2];
  
  if (winner == 'X') {
    Serial.println ("Felicitari, ati castigat!");
    return true;
  }
  else if (winner == '0') {
    afisare();
    Serial.println ("Din pacate ati pierdut.");
    return true;  
  }  
  else if (mutari == 9) {
    Serial.println ("Remiza!");
    return true;
  }
  else
    return false;
}

void afisare () {
  for (int i = 0; i < 9; i++){
    Serial.print(tabla[i]);
    if ( (i+1) % 3 == 0)
      Serial.print ('\n');
    else
      Serial.print (' ');
  } 
}

void mutareX() {
  boolean valid = false;
  int x = 0;
  while (!valid) {
    Serial.println ("Alegeti o pozitie de la 1 la 9.");
    while ( x < '1' || x > '9') {
      x = Serial.read ();
      delay (1000);
    }
    x = x - 48;
    Serial.print ( "Ati ales pozitia : " );
    Serial.print ( x, DEC );
    Serial.println ();
    if (tabla[x-1] != '-' )
      Serial.println ( "Pozitie eronata." );
    else {
      tabla[x-1] = 'X';
      valid = true;
    }
  }
}

void mutare0() {
  int i = -1;
  while (i == -1) {
    i = random (0, 9);
    if (tabla[i] == '-') {
      tabla[i] = '0';
      Serial.print ( "Arduino a ales pozitia: " );
      Serial.print ( i+1, DEC );
      Serial.println ();
      break;
    }  
    else i = -1;
  }
}

