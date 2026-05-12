// Pins
// Program fondation : declared variables, pins name, included library/ Objects, state variables...

const int trigPin = 4;


const int echoPin = 5;


const int ledVerte = 8; 


const int ledRouge = 2; 


const int buzzer = 6;

 

// Chronomètres


unsigned long tempsPhase = 0; // "unsigned long" mean a range of numbers from 0 to 4,294,967,295, negatives int aren't there for this fuction...

// so "tempsPhase" is equal to 0 for the 23 and 27 lines...

unsigned long prochainCoup = 0; // "unsigned long" mean a range of numbers from 0 to 4,294,967,295, negatives int aren't there for this fuction...

 

// Game States...


enum Etat { REPOS, ATTAQUE, TOUCHE }; // we associate each state of "Etat" to a script section all developped bealow,, each script section is separated by "break"... 
// IMPORTANT TO KNOW THE FACT THAT THE "ENUM ETAT" l-34 runs from the left to the right his contents that are "REPOS, ATTAQUE, TOUCHE) so one by one...

Etat etatActuel = REPOS; // we associate "Etat" with "actual state" that is associated with one of the three state present in the l-34...

 // we start by the first state because of the linear reading of the compiler...

void setup() {//*


  pinMode(ledVerte, OUTPUT);


  pinMode(ledRouge, OUTPUT);


  pinMode(buzzer, OUTPUT);


  pinMode(trigPin, OUTPUT); // associated with a wave emmision from the US sensor...


  pinMode(echoPin, INPUT); // the arduino R4 or UNO board receive signals from the US echo waves...

 
  randomSeed(analogRead(0)); // allow to read random values in the A0 port by the electrical noises of this port...


  prochainCoup = millis() + random(1000, 4000); // we start a chronometer with millis and start the random 
}//*

 

void loop() {  // a first main blue |{}| that comes after the second |{}| green section closure*...


  unsigned long maintenant = millis(); // each time millis is mentionned on the script, we start a chrono from 0..

// so millis can take any values from 0 to 4,294,967,295 that is in factt huge ammont if time that can be evaluated by the millis chrono...

  int distance = lireDistance(); // tells us about the association of a function l-206 with a name "distance" associated...


  switch (etatActuel) { //  a second green |{}| that comes after the first |{}| yellow section closure**...
// means that we want to invocate the presence of the differents states from "Etat"...
   

    case REPOS: // switch on line 81 is in link with case from this line, so for this case of state...
// we associate the sleep state to a scrpt secton...

      if (maintenant >= prochainCoup) { // a tercery yellow |{}| that comes after de second |{}| blue section closure***...
// each time we dont use any delay because of his ability to freeze the micro processor AT-Mega 32 of the arduino...
// now is associated with millis and because of the chronometer that has been started just at the R4 boot moment l-62, and the random values took by the "prochain coup" in millis with a max value "4000ms", we can exactly know when we got the "choosed value" if we got the millis chrono superior to this choosed value... 
        digitalWrite(ledVerte, HIGH);


        tone(buzzer, 1200); // SON AIGU : Alerte impact imminent !


        tempsPhase = maintenant; //we associate the 0 value of "temps phase" with now to restart the now chrono...

        etatActuel = ATTAQUE; // in logic, just after the green led got emmited from the "REPOS" section/part, we are now in the "ATTAQUE" part of the game, like a linear logic evolution of the game events... 


      }//*** 


      break;  // To separate the "State" section we use the break separator that is linked with "case" and "switch"...

 

    case ATTAQUE: // yhe next logic state of the game...

// double conditionnal for this case, the attack case...

      // Fenêtre d'esquive de 350ms


    if (maintenant - tempsPhase >= 350) { // *** it is like if we used the "delay" function without "freezing" the AT Mega processor...
// temps phase = 0 so after we got 350ms after the mllis restart line-93...

        digitalWrite(ledVerte, LOW); // the aftermath of a conditional evocation line 118...


        noTone(buzzer); // same also consequences of a conditional line 118...


         //1st cond...


        // VERIFICATION : Si tu es encore là après 350ms


        if (distance <= 100) { // we also add a precision in the IA, so we need to allow the US sensor recognisinng the inferior distance from 100cm...


          digitalWrite(ledRouge, HIGH); // the punition RED indicator...


          tone(buzzer, 150); // SON GRAVE : Type "Buzzer Incroyable Talent"


          tempsPhase = maintenant; // we always actualise the passed l-133 to l-139 script part so we can progress in the game logic...


          etatActuel = TOUCHE; // logic linear state that comes after "ATTAQUE"...
         //2nd cond...


        } else {


          // Succès : Tu as esquivé à temps


          preparerProchainCoup(); // " we just runs the "REPOS" code section like if we restart the programm to his first stage ("repos")...


        }


      }//***


      break; // we devide the script in sections so we have separated parts that runs in harmony...

 

    case TOUCHE: // when the player got "hitted" by the game...


      // the "punition" last 600ms...


      if (maintenant - tempsPhase >= 600) { // like a 600ms "delay" without having to freeze the AT mega processor... ***


        digitalWrite(ledRouge, LOW); // the desapearition of the LED Red indicator...


        noTone(buzzer); // same but for the noise emmision...


        preparerProchainCoup(); // just after the "punition" we run the "kick" function...
// afer a punition, we keep running the game as before like nothing happend...

      } // each programm parts have their own {} structure so we can get a clean result without reading trouble... ***


      break; // we separate the code in sections again...


  } //** 


}// *

 

// --- FONCTIONS ---

 

int lireDistance() { // int because of the int values that takes this function... *
// you can find this script in a random well explained youtube tutorial... 

  
 digitalWrite(trigPin, LOW); // US configuration beginning...


  delayMicroseconds(2); // to correcty activte the US sensor without any missed emmision...


  digitalWrite(trigPin, HIGH);


 delayMicroseconds(10); // the time the sound hit any obstacle...


  digitalWrite(trigPin, LOW); // US configuration ended...

// calculus part (distance simple formulas)...

  long duree = pulseIn(echoPin, HIGH, 25000); // the "int" values, 25000 means the max time we should wait before this operation restart from the begining of the code...
// line-218 wait the moment until we got a US reception, this waiting moment last 25000ms...

  if (duree == 0) return 999; // "If no echo was received(duree == 0), exit the function and return a special value (999) indicating an invalid measurement."
 // same "int" values again...
 
  return duree * 0.034 / 2; // idem...
// the earth of this section, we calcul the distance at this moment of he function...

}//*

 

void preparerProchainCoup() { // second function for the main game activity...


  prochainCoup = millis() + random(1500, 4000); 
 // WE USE THE NATURAL ELECTONIC PHENOMEN WHERE ELECTRIC NOISES APPEARS RANDOMLY ON THE A0 PORT so we associate thoses noises to a random intervalled value...
// next punch vault 0 each time the light is randomly emmited by the LED emmiter from the breadboard link to the digital pin 8 of the arduino...
// this make in sort that now associated to "millis" is superior to 0 after that "millis" got invocated on any line of the code especially the 91 lines...
 
  etatActuel = REPOS;  // we associate this function to the game main sleep mode... 
// we complete the loop of "ETAT" so we reset to return to the begenning of the programm/ game logic...

}//*  heheheha Thanks (instagram account: @andy_lltd | Ytb channel: @ThinkerLab)...
