#include <Servo.h>
Servo myservo;
int pos = 0;
int trig = 7;
int echo = 8;
long time, distance, mesure;
//-----------------------------------------//
#define TRIG_PIN 10
#define ECHO_PIN 11
int led_red = 5;
int led_green = 6;
int led_yellow = 4;
int buzzer = 12;

int pahState = 0; // 0 - close   1 - open

void setup() {
  myservo.attach(9);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  Serial.begin(9600);
  //--------------------------------------//
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(buzzer, OUTPUT);




  checkDistance(  TRIG_PIN,  ECHO_PIN);
  mesure = distance;
  Serial.print(mesure);
  Serial.println("cm - top sensor distance");
  delay(100);


  if ( mesure < 30) {
    digitalWrite(led_green, HIGH);
    digitalWrite(led_yellow, LOW);
    digitalWrite(led_red, LOW);
    noTone(buzzer);
  }


  if (mesure <= 15 && mesure > 5) {
    digitalWrite(led_yellow, HIGH);
    digitalWrite(led_green, HIGH);
    digitalWrite(led_red, LOW);
    noTone(buzzer);
  }

  if (mesure <= 5 ) {
    digitalWrite(led_red, HIGH);
    digitalWrite(led_green, HIGH);
    digitalWrite(led_yellow, HIGH);
    tone(buzzer, 2000);
  }

}

void loop() {
 

  checkDistance(  trig,  echo);
  Serial.print (" bottom sensor distance = ");
  Serial.println(distance);

  if (distance < 10)
  {

    myservo.write(0);  // פתח פח
    pahState = 1;
    delay(3000);



  }
  else  {


    myservo.write(180); // סגור פח
    pahState = 0;
    delay(1000);

    delay(100);
  }
  //-----------------------------------------------//
  if ( pahState == 0) {
   
    checkDistance(  TRIG_PIN,  ECHO_PIN);
    mesure = distance;
    Serial.print(mesure);
    Serial.println("cm - top sensor distance");
    delay(100);


    if ( mesure < 30) {
      digitalWrite(led_green, HIGH);
      digitalWrite(led_yellow, LOW);
      digitalWrite(led_red, LOW);
      noTone(buzzer);
    }


    if (mesure <= 15 && mesure > 5) {
      digitalWrite(led_yellow, HIGH);
      digitalWrite(led_green, HIGH);
      digitalWrite(led_red, LOW);
      noTone(buzzer);
    }

    if (mesure <= 5 ) {
      digitalWrite(led_red, HIGH);
      digitalWrite(led_green, HIGH);
      digitalWrite(led_yellow, HIGH);
      tone(buzzer, 2000);
    }

  }
  else if ( pahState == 1) {

    checkDistance(  TRIG_PIN,  ECHO_PIN);
    while (distance < 18) {
      checkDistance(  TRIG_PIN,  ECHO_PIN);

    }
  }
}


void checkDistance( int trigPin, int echoPin) {

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  time = pulseIn(echoPin, HIGH);
  distance = time / 58;
   Serial.print (" top sensor * distance = ");
  Serial.println(distance);

}

