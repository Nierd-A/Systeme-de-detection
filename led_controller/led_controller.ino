int led_R1 = 12;
int led_R2 = 11;
int led_J1 = 10;
int led_J2 = 9;
int led_V1 = 8;
int led_V2 = 7;
int capt_Son = 5;
int RX = 0;
int TX = 1;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.


  pinMode(led_R1, OUTPUT); //rouge
  pinMode(led_R2, OUTPUT);
  pinMode(led_J1, OUTPUT); //jaune
  pinMode(led_J2, OUTPUT);
  pinMode(led_V1, OUTPUT); //vert
  pinMode(led_V2, OUTPUT);
  pinMode(TX, OUTPUT);//TX
  
  pinMode(capt_Son, INPUT);  //capteur de son
  pinMode(RX, INPUT); //RX : Capteur de presence
 

}

// the loop function runs over and over again forever
void loop() {
  int val_Capt_Son = digitalRead(capt_Son);
  int val_RX = digitalRead(RX);

  if (val_RX == 0)
  {
      // Extinction de toutes les DEL au départ du programme
      for (byte i = 7 ; i <= 12 ; i++) {
        digitalWrite (i, LOW) ; // éteint la DEL reliée à la broche i
      }
      
      // 5 seconde de clignotement leds jaunes
      for (int cmp = 0 ; cmp < 10 ; cmp++){
          
          digitalWrite(led_J1, HIGH);
          digitalWrite(led_J2, HIGH);
          delay (250);
          digitalWrite(led_J1, LOW);
          digitalWrite(led_J2, LOW);
          delay (250);
      }
      // 5 seconde de clignotement leds verte et rouge avec 2 seconde d'intervalle
      for (int cmp = 0 ; cmp < 4 ; cmp++){
          
          digitalWrite(led_V1, HIGH);
          digitalWrite(led_V2, HIGH);
          delay (250);
          digitalWrite(led_V1, LOW);
          digitalWrite(led_V2, LOW);
          delay (250);
      }
      for (int cmp = 0 ; cmp < 4 ; cmp++){
          
          digitalWrite(led_R1, HIGH);
          digitalWrite(led_R2, HIGH);
          delay (250);
          digitalWrite(led_R1, LOW);
          digitalWrite(led_R2, LOW);
          delay (250);
      }
      for (int cmp = 0 ; cmp < 2 ; cmp++){
          
          digitalWrite(led_V1, HIGH);
          digitalWrite(led_V2, HIGH);
          delay (250);
          digitalWrite(led_V1, LOW);
          digitalWrite(led_V2, LOW);
          delay (250);
      }
      
  }
  

  else if (val_Capt_Son == 0)
  {
    // Extinction de toutes les DEL au départ du programme
    for (byte i = 7 ; i <= 12 ; i++) {
        digitalWrite (i, LOW) ; // éteint la DEL reliée à la broche i
    }
    // On informe au RPi que un son se produit
    digitalWrite(TX, HIGH);
    for(int cmp=0; cmp < 5;cmp++) {
    // Leds rouges et vertes clignotes
    digitalWrite(led_V1, LOW);
    digitalWrite(led_V2, LOW);
    digitalWrite(led_R1, HIGH);
    digitalWrite(led_R2, HIGH);
    delay (300);
    digitalWrite(led_R1, LOW);
    digitalWrite(led_R2, LOW);
    digitalWrite(led_V1, HIGH);
    digitalWrite(led_V2, HIGH);
    delay (300);
    }
  }
    

  else {
      //On informe au RPi qu'il n'y a plus de son
      digitalWrite(TX, LOW);
      // Extinction de toutes les DEL au départ du programme
      for (byte i = 7 ; i <= 12 ; i++) {
        digitalWrite (i, LOW) ; // éteint la DEL reliée à la broche i
      }
     
      // Boucle pour faire flasher les DEL
      for (byte i = 7 ; i <= 12 ; i++) {
        digitalWrite (i, HIGH) ; // allume la DEL sur broche i
        delay (50) ; // durée du flash 50 millisecondes
        digitalWrite (i, LOW) ; // éteint la DEL
      }
     
      // délai de 500 millisecondes
      delay (500) ;
     
      // Recommence la séquence
    
  }
}
