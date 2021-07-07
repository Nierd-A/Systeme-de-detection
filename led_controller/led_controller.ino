//déclaration des variables
//variables liées aux broches
int led_R1 = 12;
int led_R2 = 11;
int led_J1 = 10;
int led_J2 = 9;
int led_V1 = 8;
int led_V2 = 7;
int capt_Son = 5;
int RX = 0;  
int TX = 1; 

//variable de récupération des broches input
int val_Capt_Son, val_RX;

void setup() {
  // initialisation des leds et des broches de capteurs

  //output
  pinMode(led_R1, OUTPUT); //rouge
  pinMode(led_R2, OUTPUT);
  pinMode(led_J1, OUTPUT); //jaune
  pinMode(led_J2, OUTPUT);
  pinMode(led_V1, OUTPUT); //vert
  pinMode(led_V2, OUTPUT);
  pinMode(TX, OUTPUT);//TX

  //input
  pinMode(capt_Son, INPUT);  //capteur de son
  pinMode(RX, INPUT); //RX : Capteur de presence
 

}

// Boucle d'écoute des événements
void loop() {
  //écoute des broches input
  val_Capt_Son = digitalRead(capt_Son);
  val_RX = digitalRead(RX);

  //action selon les broches
  if (val_RX == 0)
  {
    sequence_presence();      
  }  

  else if (val_Capt_Son == 0)
  {
    sequence_son();    
  }    

  else {
    sequence_attente();    
  }
}

// Extinction de toutes les DEL
void extinction() {  
  for (byte i = 7 ; i <= 12 ; i++) {
    digitalWrite (i, LOW) ; // éteint la DEL reliée à la broche i
  }
}

// Fonction de sequence de led dédié au capteur de presence
// Les durées ont été imposées et sont calculées selon
// -> la somme des délais d'une boucle * le nombre de boucle
void sequence_presence() {
  extinction();
  
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
  //durée = 2 secondes
  for (int cmp = 0 ; cmp < 4 ; cmp++){
      
      digitalWrite(led_V1, HIGH);
      digitalWrite(led_V2, HIGH);
      delay (250);
      digitalWrite(led_V1, LOW);
      digitalWrite(led_V2, LOW);
      delay (250);
  }
  //durée = 2 secondes
  for (int cmp = 0 ; cmp < 4 ; cmp++){
      
      digitalWrite(led_R1, HIGH);
      digitalWrite(led_R2, HIGH);
      delay (250);
      digitalWrite(led_R1, LOW);
      digitalWrite(led_R2, LOW);
      delay (250);
  }
  //durée = 1 secondes
  for (int cmp = 0 ; cmp < 2 ; cmp++){
      
      digitalWrite(led_V1, HIGH);
      digitalWrite(led_V2, HIGH);
      delay (250);
      digitalWrite(led_V1, LOW);
      digitalWrite(led_V2, LOW);
      delay (250);
  }
}

//Fonction de sequence de led dédié au capteur de son
void sequence_son() {
  extinction();
  
  // On informe au RPi qu'un son se produit
  digitalWrite(TX, HIGH);
  
  //Clignotement de 2 secondes
  for(int cmp=0; cmp < 4;cmp++) {
  // Leds rouges et vertes clignotes
  digitalWrite(led_V1, LOW);
  digitalWrite(led_V2, LOW);
  digitalWrite(led_R1, HIGH);
  digitalWrite(led_R2, HIGH);
  delay (250);
  digitalWrite(led_R1, LOW);
  digitalWrite(led_R2, LOW);
  digitalWrite(led_V1, HIGH);
  digitalWrite(led_V2, HIGH);
  delay (250);
  
  }
  //On informe au RPi qu'il n'y a plus de son
  digitalWrite(TX, LOW);
}

//Fonction de sequence de led dédié à l'attente d'événements
void sequence_attente(){  
  extinction();
 
  // Boucle pour faire flasher les DEL
  for (byte i = 7 ; i <= 12 ; i++) {
    digitalWrite (i, HIGH) ; // allume la DEL sur broche i
    delay (50) ; // durée du flash 50 millisecondes
    digitalWrite (i, LOW) ; // éteint la DEL
  }
 
  // délai de 500 millisecondes
  delay (500) ;
}
