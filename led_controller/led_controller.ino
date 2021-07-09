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
int temporisation = 0;

//valeur de detection des capteurs
int detection = 0, non_detection = 1;

//sequence de led lors d'un evenement sur rx
const int size_seq_rx = 20;
int seq_rx_1[2] = {led_J1,led_J2};
int seq_rx_2[1] = {no_led};
int seq_rx_3[2] = {led_V1,led_V2};
int seq_rx_4[1] = {no_led};
int seq_rx_5[2] = {led_R1,led_R2};
int seq_rx_6[1] = {no_led};
int seq_rx_7[2] = {led_V1,led_V2};
int seq_rx_8[1] = {no_led};
Seq_item seq_rx[size_seq_rx] = {
  Seq_item(seq_rx_1,500,2),
  Seq_item(seq_rx_2,500,1),
  Seq_item(seq_rx_1,500,2),
  Seq_item(seq_rx_2,500,1),
  Seq_item(seq_rx_1,500,2),
  Seq_item(seq_rx_2,500,1),
  Seq_item(seq_rx_1,500,2),
  Seq_item(seq_rx_2,500,1),
  Seq_item(seq_rx_1,500,2),
  Seq_item(seq_rx_2,500,1),
  Seq_item(seq_rx_3,500,2),
  Seq_item(seq_rx_4,500,1),
  Seq_item(seq_rx_3,500,2),
  Seq_item(seq_rx_4,500,1),
  Seq_item(seq_rx_5,500,2),
  Seq_item(seq_rx_6,500,1),
  Seq_item(seq_rx_5,500,2),
  Seq_item(seq_rx_6,500,1),
  Seq_item(seq_rx_7,500,2),
  Seq_item(seq_rx_8,500,1),
};

//sequence de led lors d'un evenement sonore
const int size_seq_son = 2;
int seq_son_1[2] = {led_R1,led_R2};
int seq_son_2[2] = {led_V1,led_V2};
Seq_item seq_son[size_seq_son] = {
  Seq_item(seq_son_1,250,2),
  Seq_item(seq_son_2,250,2)
};

//sequence des led en attente d'un evenement
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

//variable de stockage de l'etat du systeme + initalisation
Seq_item* current_seq = seq_wait;
Seq_item* previous_seq = seq_wait;
Seq_item current_seq_step = seq_wait[0];
Seq_item previous_seq_step = seq_wait[6];
int current_size = size_seq_wait,current_step = 0;
int leds_done = 0;

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
  //envoie de la detection du son au RPi
  digitalWrite(TX,HIGH*(1-val_RX));
  
  //changement de sequence selon les evenements
  // remise a zero si changement
  if(val_RX == detection && current_seq != seq_rx) {
    previous_seq_step = current_seq_step;
    current_seq = seq_rx;
    current_size = size_seq_rx;
    temporisation = current_step = 0;
    current_seq_step = current_seq[current_step];
  } else if(val_Capt_Son == detection && current_seq != seq_son) {
    previous_seq_step = current_seq_step;
    current_seq = seq_son;
    current_size = size_seq_son;
    temporisation = current_step = 0;
    current_seq_step = current_seq[current_step];
  } else if(current_seq != seq_wait && val_Capt_Son == val_RX == non_detection) {
    previous_seq_step = current_seq_step;
    current_seq = seq_wait;
    current_size = size_seq_wait;
    temporisation = current_step = 0;
    current_seq_step = current_seq[current_step];
  }
  
  
  //changement d'etape selon le temps passé
  if(temporisation >= current_seq_step.getDuree()) {
    previous_seq_step = current_seq_step;
    current_step = (current_step + 1) % current_size;
    current_seq_step = current_seq[current_step];
    temporisation = leds_done = 0;
  }

  //mise à jour des leds si besoin
  if(leds_done == 0) {
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
    leds_done = 1;
  }
  
  temporisation += delai;
  delay(delai);
  
} 
