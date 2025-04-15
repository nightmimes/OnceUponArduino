#include <Servo.h> // servo library

Servo servoOne; // define var for servo one STEPMOM FACE
Servo servoTwo; // define var for servo two SNOW WHITE 1
Servo servoThree; // define var for servo three CASTLE DOOR
Servo servoF; // define var for combined servos 4-6, shortened 'f'
Servo servoSeven // define var for servo seven mirror
Servo servoEight // define var for servo eight spinning characters: evil step mom (side A), old lady (side B), prince (side C)
/* setup buttons */

//On button
const int buttonOnPin = 13; // initialize button at digital pin 13 INTERACTION 1
int buttonOnState = 0; // initialize OnOff button as 0, off
int lastButtonOnState = 0; 
bool On = false; // initialize OnOff button condition as false

//Bush button
const int buttonBushPin = 7; // initialize copper button at digital pin 7 INTERACTION 2
int buttonBushState = 1;
int lastButtonBushState = 1;
bool Bush = true;

const int buttonApplePin = 4; // initialize apple button at digital pin 4 INTERACTION 4
int buttonAppleState = 0;
int lastButtonAppleState = 0;
bool Apple = false;
bool buttonApplePressed = false;
bool applePressed = false;

const int buttonHeartPin = 2; // initialize heart button at digital pin 2 INTERACTION 5
int buttonHeartState = 0;
int lastButtonHeartState = 0;
bool Heart = false;

bool sceneMirror = false;
bool sceneOne = false; // initialize sceneOne condition as false
bool ultrasonic = false; // initialize ultrasonic as false
bool dialogueSceneOne = false; 
bool dialogueOneDone = false;
bool doorOpening = false;
// bool endSceneOne = false;

bool charactersUp = false; // boolean to raise outdoor characters: snow white, dwarf 1 & 2
bool sceneTwoDone = false;
bool doorClose = false;
bool sceneTwo = false; // initialize scene two condition as false

bool sceneThree = false;
bool endSceneThree = false;

bool sceneFour = false;
bool endSceneFour = false;

bool sceneFive = false;

const int trigPin = 10; // initialize trig at digital pin 9 ULTRASONIC
const int echoPin = 11; // initialize echo at digital pin 10 ULTRASONIC
/* defines vars for ULTRASONIC & servos */
long duration;
int distanceCM; // var for distance in centimeters
float distanceIN; // var for distance in inches


void setup() {
  servoOne.attach(9);  // servo one STEPMOM FACE at digital pin 9
  servoTwo.attach(8); // servo two SNOW WHITE 1 at digital pin 8
  servoThree.attach(12); // servo three CASTLE DOOR at digital pin 13
  servoF.attach(6); // servo 4-6 SNOW WHITE 2, DWARF 1, DWARF 2 at digital pin 6
  servoSeven.attach(3); // servo seven at digital pin 3
  servoEight.attach(5); // servo eight spinning characters at digital pin 5

/* define inputs for buttons */
  pinMode(buttonOnPin, INPUT); // defines button on pin measurement as input
  pinMode(buttonBushPin, INPUT); 

  pinMode(trigPin, OUTPUT); // defines trig pin as output
  pinMode(echoPin, INPUT); // defines echo pin measurement as input
  Serial.begin(9600); // begins serial communication
}

void loop() {
  onOffSwitch();

  
}

void onOffSwitch(){
  buttonOnState = digitalRead(buttonOnPin); // defines var for button state measurement from input
if(On != true){ // if switch is off
defaultPositions();

}
// reads On/Off button
if(buttonOnState != lastButtonOnState){ // if a different state is measured, if OnOff is switched ON
if(buttonOnState == HIGH){
  if(On == false){ // if switch off & scenes have not started
  On = true;
  sceneOne = true;
  sceneMirror = true;
  Serial.print("ON"); // writes start scene 1 in serial monitor
  }
  } else if(buttonOnState == LOW && On == true){ // switch turned off from being on
  On = false;
  defaultPositions();
}
}

  }

void defaultPositions(){ // sets default off positions for servos
  servoOne.write(0); 
  servoTwo.write(0); 
  servoThree.write(0); 
  servoF.write(0); 
  servoSeven.write(0); 
  servoEight.write(0); 
}

void sceneOne(){

/* SCENE MIRROR */
if(buttonOnState == HIGH && On == true){ // if button is On and On boolean is set to true
if(sceneOne == true){
  Serial.print("SCENE I"); // writes scene 1 in serial monitor
} else if(sceneThree == true){
  Serial.print("SCENE III"); // writes scene 3 in serial monitor
}

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

if(sceneOne == true){ // if it's scene one
  doorOpening = true; // sets condition to open castle door to true 
  /* delay door opening according to scene 1*/
} 
if(sceneThree == true){ // if it's scene three
  // play evil stepmom laughter & change LEDs ??
  endSceneThree = true; // ends mirror scene by initiating servo 8 spin to old lady side B
} 
  dialogueOneDone = false; // sets condition to false to end looping if statement
  }
}

if(doorOpening == true && dialogueOneDone == false){
  if(sceneOne == true){
servoThree.write(90); // set servo 3 to 90 degrees to open door
delay(500); // delay according to door opening duration
doorOpening = false;
sceneTwo = true;
  }

if(endSceneThree == true && dialogueOneDone == false){
  if(sceneThree == true){
    servoEight.write(90); // turns from evil stepmom side A to old lady side B
    /* delay according to character turning */
  endSceneThree = false;
  sceneFour = true;
  }
}

if(sceneTwo == true || sceneFour == true){ // if scene 2 or 4 is true
sceneMirror = false; // ends scenes one or three

if(sceneOne == true){ // if it's scene one
  sceneOne = false;
} else if(sceneThree == true){ // if it's scene three
  sceneThree = false;
}
}
}


}

}

void sceneTwo(){
buttonBushState = digitalRead(buttonBushPin); // defines var for button state measurement from input 

if(sceneTwo == true && sceneOne == false){
  servoThree.write(90); // door stays open with servo 3 at 90 degrees 

  // reads Bush button
if(buttonBushState != lastButtonBushState){ // if a different state is measured, if Bush button state is 0
if(buttonBushState == LOW){ // if bush is removed, turning state to low
  Bush = false; // sets boolean from true to false
  Serial.print("SCENE II"); // writes scene 2 in the serial monitor

  if(Bush == false){ // if bush is false
    charactersUp = true; // set cue to raise outdoor characters to true
  }

  if(charactersUp == true && Bush == false){
    /* while narration about dwarfs raising snow white is playing */
    servoF.write(90); // servo moves 90 degrees to raise characters
    /* delay for narration and scene */
    delay(1000);
    /* after scene plays through*/
    sceneTwoDone = true; // set boolean to true to end scene
    charactersUp = false; // lower outdoor characters down
  }

  if(sceneTwoDone == true){
    servoF.write(0); // default position
    /* delay for characters lowering*/
    delay(500);
    doorClose = true; // after characters lower, set condition to close door to true

    if(doorClose == true){ // turns evil stepmom face back to neutral, default
      servoOne.write(0); 
      /* delay ?? */
      servoThree.write(0); // close door back to default position
      /* delay for door closing */

      /* after door is closed*/
      sceneTwoDone = false;
      sceneTwo = false; // ends scene two
      sceneThree = true; // starts scene mirror (three)
    }
  }
  }
}
}
}

void sceneFour(){
  /* Apple LED Button, add color changes and initializations */
  if(sceneFour == true){
    buttonAppleState = digitalRead(buttonApplePin); // reads state of apple button
    
    if(buttonAppleState != lastButtonAppleState){
      if(buttonAppleState == HIGH){
        Apple = true; // sets apple boolean to true
        buttonApplePressed = true;
      }
      applePressed = true;
      Serial.print("SCENE IV");
    }

    if(buttonApplePressed == true || applePressed == true){ // if button is actively pressed or has been pressed
    /* delay according to quick fall */
    servoTwo.write(0); // lowers snow white 1 after getting poisoned
    /* delay for laughing sound effects */
    delay(500);
    endSceneFour = true; // after delays, set to transition by activating conditional to move servo 8 & lower mirror 
    }
  if(endSceneFour == true){
    servoEight.write(180); // turns servo 8 spinning character from side B to prince side C
    servoSeven.write(0); // lowers servo 7 mirror
    /* delay according to movements */
    delay(500);
    endSceneFour = false;
    sceneFour = false; // ends scene four
    sceneFive = true; // starts scene five 
  }
  }
}

void sceneFive(){
  if(sceneFive == true){
    buttonHeartState = digitalRead(buttonHeartPin); // reads state of heart button

    if(buttonHeartState != lastButtonHeartState){
      if(buttonHeartState == HIGH){
      Heart = true;
      Serial.print("SCENE V"); // writes scene 5 in serial monitor
      /* delay ?? */
      }
    }

    if(Heart == true){
      /* turn LED in a shape of a heart on */
      servoEight.write(165); // angel prince side C towards snow white 1
      servoOne.write(90); // raise snow white 1
      /* delay according to movements */
      delay(500);
      /* delay for end scene before restart OnOff button lights up */
      delay(1000);
    }
  }
}

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
