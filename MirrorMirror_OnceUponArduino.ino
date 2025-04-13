#include <Servo.h> // servo library

Servo servoOne; // define var for servo one STEPMOM FACE
Servo servoTwo; // define var for servo two SNOW WHITE 1
Servo servoThree; // define var for servo three CASTLE DOOR

/* setup buttons */
const int buttonOnPin = 13; // initialize button at digital pin 13 INTERACTION 1
int buttonOnState = 0; // initialize OnOff button as 0, off
int lastButtonOnState = 0; 
bool On = false; // initialize OnOff button condition as false

bool sceneOne = false; // initialize sceneOne condition as false
bool ultrasonic = false; // initialize ultrasonic as false
bool dialogueSceneOne = false; 
bool dialogueOneDone = false;
bool doorOpening = false;
// bool endSceneOne = false;

bool sceneTwo = false; // initialize scene two condition as false

const int trigPin = 10; // initialize trig at digital pin 9 ULTRASONIC
const int echoPin = 11; // initialize echo at digital pin 10 ULTRASONIC
/* defines vars for ULTRASONIC & servos */
long duration;
int distanceCM; // var for distance in centimeters
float distanceIN; // var for distance in inches


void setup() {
  servoOne.attach(9);  // servo one STEPMOM FACE at digital pin 9
  servoTwo.attach(8); // servo two SNOW WHITE 1 at digital pin 8
  servoThree.attach(12) // servo three CASTLE DOOR at digital pin 13

/* define inputs for buttons */
  pinMode(buttonOnPin, INPUT); // defines button on pin measurement as input

  pinMode(trigPin, OUTPUT); // defines trig pin as output
  pinMode(echoPin, INPUT); // defines echo pin measurement as input
  Serial.begin(9600); // begins serial communication
}

void loop() {

buttonOnState = digitalRead(buttonOnPin); // defines var for button state measurement from input

// reads On/Off button
if(buttonOnState != lastButtonOnState){ // if a different state is measured, if OnOff is switched ON
if(buttonOnState == HIGH){
  On = true;
  sceneOne = true;
  Serial.println("Start SCENE 1"); // writes start scene 1 in serial monitor
}
}

/* SCENE 1*/
if(buttonOnState == HIGH && On == true){ // if button is On and On boolean is set to true
if(sceneOne == true){
Serial.println("SCENE I"); // writes scene 1 in serial monitor

delay (500); // delay to accommodate introduction audio narration
/* LED lights gesturing towards ULTRASONIC */
ultrasonic = true; // after narration delay and LED gestures, activate ultrasonic sensor

if(dialogueSceneOne == true){ // if dialogue conditional is true, triggered by ultrasonic measurement
delay (1000); // delay for audio narration 'mirror, mirror, who is farest of all' from evil stepmom
delay (50); // short delay before mirror narration response
delay (1000); // delay for audio narration 'snow white is farest of all' response from mirror
delay (50); // short delay before evil stepmom reaction
dialogueOneDone = true; // after scene one narrations finish, set ending conditional to true
}

if(dialogueOneDone == true){
  if(dialogueSceneOne == false){ // to make sure narrations play through entirely
  servoOne.write(180); // turns servo 1, evil stepmom face from Neutral to Angry
  delay(250); // delay before snow white kicked out
  /* more red LEDs turn on, add extra delay to accommodate lights turning on ?? */

  doorOpening = true; // sets condition to open castle door to true
  dialogueOneDone = false; // sets condition to false to end looping if statement
  }
}

if(doorOpening == true && dialogueOneDone == false){
servoThree.write(90);
delay(500); // delay according to door opening duration

/* endSceneOne = true; // sets condition to transition into interaction for scene 2 */
if(sceneOne == true){
doorOpening = false; // sets condition to false to end looping if statement
sceneTwo == true; // sets condition to start scene 2
sceneOne == false; // sets condition to stop scene 1
}
}
}

if(sceneTwo == true && sceneOne == false){
  
}

}


/* Serial.print("Button State: ");
Serial.println(buttonState);
  
  if (buttonState == HIGH) {
    myservo.write(90);
  } else {
    myservo.write(0);
  } */
}

 /* SERVO Functions */

 /* ULTRASONIC Functions */
void ultrasonic(){
  calibrateUltrasonic(); // calls ultrasonic calibration function

/* ultrasonic sensor measurements */
  duration = pulseIn(echoPin, HIGH); // reads echo pin measurement, returns sound wave travel time in microsecs
  distanceCM = duration * 0.0344 / 2;  // calculating distance from measurement unit
  distanceIN = distanceCM / 2.54 // convert cm unit to inches

  printUltrasonic(); // print ultrasonic measurements cm and inches
  
  if(distanceIN <= 2){ // if user waves hand 2 inches or closer to ultrasonic
  if(sceneOne == true){
    ultrasonic = false;
    dialogueSceneOne = true;
  }
  } else {
    delay(500); // wait for next measurement
  }
}

void calibrateUltrasonic(){
  digitalWrite(trigPin, LOW); // clears trig pin
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH); // sets trig pin on high for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void printUltrasonic(){
  Serial.print("distance cm: "); // prints 'distance cm:'
  Serial.print(distanceCM); // prints distance measured in cm
  Serial.print("distance in: ") // prints 'distance in: '
  Serial.print(distanceIN); // prints distance measured in inches
}
