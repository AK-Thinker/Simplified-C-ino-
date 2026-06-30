// concrete stuff...

const int redLight = 1; 
const int greenLight = 2; 

const int buzzer = 3; 

const int trigPin = 4; 
const int echoPin = 5; 

// states...

unsigned long tempsPhase = 0; 
unsigned long prochainCoup = 0; 

enum Etat {REPOS, ATTACK, TOUCHE}; 

Etat etatActuel = REPOS; 

void setup() {
  // put your setup code here, to run once:
pinMode(redLight, OUTPUT); 
pinMode(greenLight, OUTPUT); 

pinMode(buzzer, OUTPUT); 

pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);

randomSeed(analogRead(A0));

prochainCoup = millis() + random(1000,4000);

}

void loop() {
  // put your main code here, to run repeatedly:
unsigned long maintenant = millis(); 
int distance = lireDistance(); 

switch (etatActuel) {

case REPOS: 

if(maintenant >= prochainCoup){

  digitalWrite(greenLight, HIGH);
  tone(buzzer, 1200);

  tempsPhase = maintenant; 
  etatActuel = ATTACK;

}

break; 

case ATTACK: 

if (maintenant - tempsPhase >= 350){

digitalWrite(greenLight, LOW); 
noTone(buzzer); 


if (distance <= 200){

  digitalWrite(redLight, HIGH);
  tone(buzzer, 150);

  etatActuel = TOUCHE; 

 }else{  

  preparerProchainCoup(); 

}
}

break; 

case TOUCHE: 

if (maintenant - tempsPhase >= 600){

  digitalWrite(redLight, LOW);
  noTone(buzzer); 

  preparerProchainCoup(); 

}

break;

}
}
//functions...

int lireDistance(){ //1st function...

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); 

  unsigned long duree = pulseIn(echoPin, HIGH, 25000);

  if (duree == 0) return 999; 

 return duree * 0.034 / 2;

}


void preparerProchainCoup(){

prochainCoup = millis() + random(1000,4000); 

etatActuel = REPOS; 

}



//here is the link of the entire project you can acces into the WOKWI website : https://wokwi.com/projects/468268032513247233
