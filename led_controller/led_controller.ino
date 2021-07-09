class Seq_item {
  private:
    int* leds;
    int duree; 
    int size_l;

  public:
    Seq_item(int* l, int d, int s){
      leds = l;
      duree = d;
      size_l = s;
    }
    int* getLeds(){
      return leds;
    }
    int getDuree() {
      return duree;
    }
    int getSize() {
      return size_l;
    }
};


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

int no_led = -1;
int delai = 10; //en millisecondes

//variable de récupération des broches input
int val_Capt_Son, val_RX, old_Capt_Son, old_RX;

//variable lié au temps d'écoute des broches
int temporisation=0;

//valeur de detection des capteurs
int detection = 0, non_detection =1;

const int size_seq_son = 2;
int seq_son_1[2] = {led_R1,led_R2};
int seq_son_2[2] = {led_V1,led_V2};
Seq_item seq_son[size_seq_son] = {Seq_item(seq_son_1,250,2),Seq_item(seq_son_2,250,2)};

const int size_seq_wait = 7;
int seq_wait_1[1] = {led_V2};
int seq_wait_2[1] = {led_V1};
int seq_wait_3[1] = {led_J2};
int seq_wait_4[1] = {led_J1};
int seq_wait_5[1] = {led_R2};
int seq_wait_6[1] = {led_R1};
int seq_wait_7[1] = {no_led};

Seq_item seq_wait[size_seq_wait] = {
  Seq_item(seq_wait_1,50,1),
  Seq_item(seq_wait_2,50,1),
  Seq_item(seq_wait_3,50,1),
  Seq_item(seq_wait_4,50,1),
  Seq_item(seq_wait_5,50,1),
  Seq_item(seq_wait_6,50,1),
  Seq_item(seq_wait_7,500,1)
};

Seq_item* current_seq = seq_wait;
Seq_item* previous_seq = seq_wait;
Seq_item current_seq_step = seq_wait[0];
Seq_item previous_seq_step = seq_wait[6];
int current_size = size_seq_wait,current_step = 0;
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

  old_Capt_Son = digitalRead(capt_Son);
  old_RX = digitalRead(RX);
}

void loop() {
  //lecture capteur
  val_Capt_Son = digitalRead(capt_Son);
  val_RX = digitalRead(RX);

  //changement d'état
  
  //changement de sequence selon les evenements
  //changement d'etape selon le temps passé
  if(temporisation >= current_seq_step.getDuree()) {
    previous_seq_step = current_seq_step;
    current_step = (current_step + 1) % current_size;
    current_seq_step = current_seq[current_step];
    temporisation = 0;
  }

  //affichage de l'état
  if(previous_seq_step.getLeds()[0] != no_led ){
    //exctinction de la sequence precedente
    for(int i = 0; i < previous_seq_step.getSize(); i++) {
      digitalWrite(previous_seq_step.getLeds()[i],LOW);
    }
  }
  //allumage de la sequence courante
  if(current_seq_step.getLeds()[0] != no_led ){
    //exctinction de la sequence precedente
    for(int i = 0; i < current_seq_step.getSize(); i++) {
      digitalWrite(current_seq_step.getLeds()[i],HIGH);
    }
  }
  temporisation += delai;
  delay(delai);
}
// OLD_V1
/*
// Boucle d'écoute des événements
void loop() {
  
  //écoute des broches input pendant 500 millisecondes 
  //ET tant qu'un capteur ne change pas de valeur
  temporisation = 0;
  val_Capt_Son = digitalRead(capt_Son);
  val_RX = digitalRead(RX);
  while(temporisation < 500 && val_Capt_Son == non_detection && val_RX == non_detection) {
    //lecture des broches toutes les 10 millisecondes
    val_Capt_Son = digitalRead(capt_Son);
    val_RX = digitalRead(RX);
    delay(10);
    temporisation += 10;
  }
  
  //action selon les broches
  if (val_RX == detection)
  {
    sequence_presence();      
  }  

  else if (val_Capt_Son == detection)
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
}
*/
