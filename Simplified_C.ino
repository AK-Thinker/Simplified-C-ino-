// Pins


const int trigPin = 4;


const int echoPin = 5;


const int ledVerte = 8; 


const int ledRouge = 2; 


const int buzzer = 6;

 

// Chronomètres


unsigned long tempsPhase = 0;


unsigned long prochainCoup = 0;

 

// États du jeu


enum Etat { REPOS, ATTAQUE, TOUCHE };


Etat etatActuel = REPOS;

 

void setup() {//*


  pinMode(ledVerte, OUTPUT);


  pinMode(ledRouge, OUTPUT);


  pinMode(buzzer, OUTPUT);


  pinMode(trigPin, OUTPUT);


  pinMode(echoPin, INPUT);


  


  randomSeed(analogRead(0));


  prochainCoup = millis() + random(1000, 4000); // Temps de repos avant premier coup


}//*

 

void loop() {  // a first main blue |{}| that comes after the second |{}| green section closure*...


  unsigned long maintenant = millis();


  int distance = lireDistance();

 

  switch (etatActuel) { //  a second green |{}| that comes after the first |{}| yellow section closure**...


    


    case REPOS:


      if (maintenant >= prochainCoup) { // a tercery yellow |{}| that comes after de second |{}| blue section closure***...


        digitalWrite(ledVerte, HIGH);


        tone(buzzer, 1200); // SON AIGU : Alerte impact imminent !


        tempsPhase = maintenant;


        etatActuel = ATTAQUE;


      }//*** 


      break;

 

    case ATTAQUE:

// double conditionnal for this case, the attack case...

      // Fenêtre d'esquive de 350ms


    if (maintenant - tempsPhase >= 350) { // ***


        digitalWrite(ledVerte, LOW);


        noTone(buzzer);


         //1st cond...


        // VERIFICATION : Si tu es encore là après 350ms


        if (distance <= 100) {


          digitalWrite(ledRouge, HIGH);


          tone(buzzer, 150); // SON GRAVE : Type "Buzzer Incroyable Talent"


          tempsPhase = maintenant;


          etatActuel = TOUCHE;
         //2nd cond...


        } else {


          // Succès : Tu as esquivé à temps


          preparerProchainCoup(); // "just runs the kick" fonction()...


        }


      }//***


      break; // we devide the script in sections so we have separated parts that runs in harmony...

 

    case TOUCHE: // when the player got "hitted" by the game...


      // the "punition" last 600ms...


      if (maintenant - tempsPhase >= 600) { // like a 600ms "delay" without having to freeze the AT mega processor... ***


        digitalWrite(ledRouge, LOW);


        noTone(buzzer);


        preparerProchainCoup(); // just after the "punition" we run the "kick" function...


      } // each programm parts have their own {} structure so we can get a clean result without reading trouble... ***


      break; // we separate the code in sections again...


  } //** 


}// *

 

// --- FONCTIONS ---

 

int lireDistance() { // int because of the int values that takes this function... *


  digitalWrite(trigPin, LOW); // US configuration beginning...


  delayMicroseconds(2);


  digitalWrite(trigPin, HIGH);


  delayMicroseconds(10);


  digitalWrite(trigPin, LOW); // US configuration ended...

// calculus part (distance simple formulas)...

  long duree = pulseIn(echoPin, HIGH, 25000); // the "int" values...


  if (duree == 0) return 999; // same "int" values again...


  return duree * 0.034 / 2; // idem...


}//*

 

void preparerProchainCoup() { // second function for the main game activity...


  // On laisse un peu de temps au boxeur pour se remettre en garde...


  prochainCoup = millis() + random(1500, 4000); // WE USE THE NATURAL ELECTONIC PHENOMEN WHERE ELECTRIC NOISES APPEARS RANDOMLY ON THE A0 PORT so we associate thoses noises to a random intervalled value...


  etatActuel = REPOS;  // we associate this function to the game main sleep mode... 


}//*  heheheha Thanks (instagram account: @andy_lltd | Ytb channel: @ThinkerLab)...