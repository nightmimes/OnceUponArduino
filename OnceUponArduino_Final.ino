#include <Servo.h> // servo library
Servo servoOne; // define var for servo one STEPMOM FACE
Servo servoTwo; // define var for servo two SNOW WHITE 1
Servo servoThree; // define var for servo three CASTLE DOOR
Servo servoF; // define var for combined servos 4-6, shortened 'f'
Servo servoEight;

//OnOff button
const int buttonOnPin = 13; // initialize button at digital pin 13 INTERACTION 1 & 3
int buttonOnState = 0; // initialize OnOff button as 0, off
int lastButtonOnState = 0; 
bool On = false; // initialize OnOff button condition as false

//Bush button
const int buttonBushPin = 7; // initialize copper button at digital pin 7 INTERACTION 2
int buttonBushState = 1;
int lastButtonBushState = 1;
// bool Bush = true;

//Apple button
const int buttonApplePin = 4; // initialize apple button at digital pin 4 INTERACTION 4
int buttonAppleState = 0;
int lastButtonAppleState = 0;
bool Apple = false;
// bool buttonApplePressed = false;
// bool applePressed = false;

//Heart button
const int buttonHeartPin = 2; // initialize heart button at digital pin 2 INTERACTION 5
int buttonHeartState = 0;
int lastButtonHeartState = 0;
bool Heart = false;

/* defines vars for ULTRASONIC */
const int trigPin = 10; // initialize trig at digital pin 9 ULTRASONIC
const int echoPin = 11; // initialize echo at digital pin 10 ULTRASONIC
/* defines vars for ULTRASONIC & servos */
long duration;
int distanceCM; // var for distance in centimeters
float distanceIN; // var for distance in inches

bool waveAtSensor = false;
bool sceneNumOne = false;
bool farestOfAll = false;
bool servoTwoRaised = false;
bool faceAngry = false; // to stop spinning for servo 1
bool doorOpen = false;
// bool doorIsOpen = false; // to stop spinning for servo 3

bool sceneNumTwo = false;
bool bushInteraction = false; // to start bush button circuit
bool bushOff = false; // deactivates bush circuit and starts scene 2 characters
bool doorClose = false;
bool charactersUp = false;
bool charactersDown = false;
bool oldLady = false;
bool sceneNumThree = false;
bool sceneNumFour = false;
bool sceneNumFive = false;
bool snowWhiteUp = false;
bool spinToPrince = false;

bool sceneStarted = true;

unsigned long startTime = 0;
bool servoEightPositioned = false;

void setup() {
  startTime = millis();

  servoOne.attach(9); // servo one evil stepmom face at digital pin 9
  servoOne.write(180); // set evil stepmom face to neutral side I

  servoTwo.attach(8); // servo two SNOW WHITE 1 at digital pin 8
  servoTwo.write(180); // set snow white 1 to default lowered position 

  servoThree.attach(12); // servo three CASTLE DOOR at digital pin 12
  servoThree.write(80);

  servoF.attach(6); // servo 4-6 SNOW WHITE 2, DWARF 1, DWARF 2 at digital pin 6
  servoF.write(180);

  /* servoEight.attach(5); // servo eight spinning characters at digital pin 5
  servoEight.write(0); */

  servoEight.write(0);
  servoEight.attach(5); // servo eight spinning characters at digital pin 5

  if(!servoEightPositioned && millis() - startTime >= 1){
    servoEightPositioned = true;
  } 

  if(servoEightPositioned == true){
    servoEight.detach();
  }  else {
    servoEight.attach(5); // servo eight spinning characters at digital pin 5
  } 

  pinMode(buttonOnPin, INPUT); // initialize buttons on pin measurement as input
  pinMode(buttonBushPin, INPUT);
  pinMode(buttonApplePin, INPUT);
  pinMode(buttonHeartPin, INPUT);

  pinMode(trigPin, OUTPUT); // initialize trig pin as output
  pinMode(echoPin, INPUT); // initialize echo pin measurement as input

  Serial.begin(9600); // begins serial communication
}

/* function declarations */
void onOffSwitch();
// void mirrorScene();
void ultrasonicSensor();
void calibrateUltrasonic();
void printUltrasonic();
// void sceneOne();
// void sceneTwo();

void loop() {
  onOffSwitch();
 // serialMonitor();
  mirrorScene();

   /* if(!oldLady || !spinToPrince){ // if servo 8 not spinning to old lady side B or prince side C
servoEight.detach();
} else if(oldLady == true || spinToPrince == true){
servoEight.attach(5);
} */

  sceneOne();
  sceneTwo();
  sceneThree();
  sceneFour();
  sceneFive();
}

/* void serialMonitor(){
  bool onPrinted = false;
  bool offPrinted = false;
  // bool waveText = false;

  buttonOnState = digitalRead(buttonOnPin);

  if(buttonOnState != lastButtonOnState || !sceneStarted){ // if the button state changed or has not started
    if(buttonOnState == HIGH){ // if button is turned on
    if(!onPrinted){ // if on hasn't been printed
      //Serial.print("ON");
      onPrinted = true;
    }
    if(!offPrinted){ // if off hasn't been printed
      // Serial.print("OFF");
      offPrinted = true;
    }
    } 
  }
  lastButtonOnState = buttonOnState; // recalibrating

  if(buttonOnState != lastButtonOnState){ // if the button state changed
    if(onPrinted == true){ // and if on condition is true
      onPrinted = false; // reset condition if button state is changed
    }
    if(offPrinted == true){ // and if off condition is true
      offPrinted = false; // reset condition if button state is changed
    }
  }
  lastButtonOnState = buttonOnState; // recalibrating

  /* ultrasonic text */
 /* if(waveAtSensor){ // if condition to start ultrasonic is on
    if(!waveText){ // if "waiting for hand wave" text not displayed on serial monitor

    }
  } 
} */

void sceneOne(){
  if(On == true && sceneNumOne == true){ // if on is pressed, starting scene one
 // Serial.print("SCENE I "); // writes scene 1 in serial monitor

  waveAtSensor = true;
  ultrasonicSensor();
  }
}

void sceneThree(){
if(sceneNumThree == true && On == true){
  if(sceneNumTwo == false){
    sceneNumOne = false;
    // Serial.print("SCENE III "); // writes scene 3 in serial monitor

    waveAtSensor = true;
    ultrasonicSensor();
  }
}
}

void mirrorScene(){
  if(On == true){
     if(sceneNumOne == true || sceneNumThree == true){ // if it's scene 1 or 3
    if(farestOfAll == true && servoTwoRaised == true){ // after wave is detected by ultrasonic
  delay(500);
  for(int angle = 180; angle >= 0; angle--){ // turns neutral face to angry
    servoOne.write(angle);
    delay(1);
  }
  faceAngry = true; // stop servo 1 motion
  }

  if(sceneNumOne == true){ // if it's scene 1
      doorOpen = true; // starts door opening to transition to scene 2
  } 
  if(sceneNumThree == true){
    oldLady = true; // starts turning servo 8 to old lady side B
  }
  
  if(doorOpen == true){ // for scene 2
    delay(250); 
    for(int angle = 90; angle <= 180; angle++){ // snow white 1 lowered
      servoTwo.write(angle);
      delay(5);
    }
     for(int angle = 80; angle >= 0; angle--){ // door open
      servoThree.write(angle);
      delay(30);
     }
     delay(1000); // delay for door opening
    // doorIsOpen = true;
   // faceAngry = false;
    sceneNumTwo = true;
    sceneNumOne = false;
    doorOpen = false; //stops looping servo 3 motion
  } 

  if(oldLady == true){ // for scene 4
    if(farestOfAll == true){
servoEight.attach(5);
  delay(1000);
  for(int angle = 0; angle <= 90; angle++){ // turns servo 8 to old lady side B
    servoEight.write(angle);
    delay(25);
  }
  delay(1000);
  faceAngry = false;
  sceneNumFour = true;
  oldLady = false; // stops looping servo 8 motion
  farestOfAll = false;
    }
  }
     }
    
  if(sceneNumTwo == true || sceneNumFour == true){ // if it's scene 2 or 4
    farestOfAll = false;
    servoTwoRaised = false;
  }
    
  }
}


void sceneTwo(){
  if(sceneNumTwo == true && On == true){
    servoOne.write(180); // set evil stepmom face back to neutral side I
    bool Bush = true; 
    bool startSceneThree = false;
    // Serial.print("SCENE II "); // writes scene 2 in serial monitor
    delay(1000); // delay for door opening

    bushInteraction = true; // interaction #2

  if(bushInteraction == true){ // if interaction 2 started
    buttonBushState = digitalRead(buttonBushPin);
    Serial.print("Remove the odd one out");
    Serial.println(buttonBushState);

    if(buttonBushState != lastButtonBushState || buttonBushState == LOW){ // only act if the button state changed
        Bush = false;
        Serial.println("You got it!"); // writes in serial monitor if bush is removed from circuit
        bushOff = true;
    
  }
  lastButtonBushState = buttonBushState; // recalibrating
    }

    if(bushOff == true && Bush == false){ // condition to start outdoor character motion
    delay(50); // delay between removing bush and characters raising
    charactersUp = true; // condition to raise characters
    
    if(charactersUp == true){
      for(int angle = 180; angle >= 90; angle--){ // raise outside characters
      servoF.write(angle);
      delay(25);
    }
    delay(2000); // delay for outside scene
    bushOff = false; // ends servo f raising motion
    bushInteraction = false; // resets bush interaction condition
    charactersUp = false; // resets characters and prevents further servo f raising motion
    charactersDown = true; // condition to lower characters
    }
    }

    if(bushOff == false && bushInteraction == false){
      if(charactersDown == true){ // if condition true
              for(int angle = 90; angle <= 180; angle++){ // lower outside characters
                servoF.write(angle);
                delay(25); 
                }
            charactersDown = false; // stops servo F characters lowering motion
            doorClose = true; // starts door closing motion
      }
      if(doorClose == true){
        delay(25); // delay after characters lowering
    for(int angle = 0; angle <= 80; angle++){ // close door
      servoThree.write(angle);
      delay(30);
    }
    // delay(2000); // delay to door closing
    doorClose = false; // stops servo 3 closing motion
    startSceneThree = true; // starts scene three
      }
      
      if(startSceneThree == true){
      sceneNumThree = true;
      sceneNumTwo = false; 
      }
    }

  }
}

void sceneFour(){
  if(sceneNumFour == true && On == true){
       buttonAppleState = digitalRead(buttonApplePin);

      if(buttonAppleState != lastButtonAppleState){
        if(buttonAppleState == HIGH){
          Apple = true;
        }
      }
      lastButtonAppleState = buttonAppleState; // recalibrating

      if(Apple == true){ // if apple button pressed
      applePressed = true;
      }

      if(applePressed == true){
      for(int angle = 90; angle <= 180; angle++){ // snow white 1 falls down
      servoTwo.write(angle);
      delay(7);
      }
      applePressed = false;
      prince = true; 
      }

      if(prince == true){
        servoEight.attach(5);
        for(int angle = 90; angle <= 180; angle++){
          servoEight.write(angle);
          delay(25);
        }
        prince = false;
              Apple = false; // disables apple button and servo 2 motion
      sceneNumFive = true;
      sceneNumFour == false;
      }
      if(!prince){
        servoEight.detach();
      }
  }
}

void sceneFive(){
  if(sceneNumFive == true && On == true){
buttonHeartState = digitalRead(buttonHeartPin);
    Serial.println(buttonHeartState);
    if(buttonHeartState != lastButtonHeartState){
        if(buttonHeartState == HIGH){ // if heart is inserted into hand slot
        Heart = true;
        }
      }
      lastButtonHeartState = buttonHeartState; // recalibrating

       
        if(Heart == true && !snowWhiteUp){ // if snow white not raised
        for(int angle = 180; angle >= 90; angle--){ // snow white 1 raises
          servoTwo.write(angle);
          delay(25);
        }
        Serial.print("<3");
        snowWhiteUp = true; // stops raising motion 
        }
  }
} 

void onOffSwitch(){
  buttonOnState = digitalRead(buttonOnPin);

  if(buttonOnState != lastButtonOnState){ // only act if the button state changed
    if(buttonOnState == HIGH){
      On = true;
      // Serial.println("ON");
      if(sceneStarted == true){
        sceneNumOne = true;
      }
    sceneStarted = false;
      // onPressed = true;
    }
  }
  lastButtonOnState = buttonOnState; // recalibrating
}

void ultrasonicSensor() {
  if(sceneNumThree == true){
    servoTwoRaised = false; // reset boolean for scene 3 interaction
    farestOfAll = false;
  }

  if (waveAtSensor == true && servoTwoRaised == false) {
    calibrateUltrasonic();

    duration = pulseIn(echoPin, HIGH);
    distanceCM = duration * 0.0344 / 2;
    distanceIN = distanceCM / 2.54;

    printUltrasonic();
  }

  if (distanceIN <= 1 && !servoTwoRaised) { // only move if not already moved
    waveAtSensor = false;

    delay(100); // delay for snow white is the fairest of all
    for (int angle = 180; angle >= 90; angle--) { // snow white 1 raises
      Serial.print("Wave Detected!");
      servoTwo.write(angle);
      delay(25);
    }
    farestOfAll = true;
    servoTwoRaised = true; // prevent repeating the motion
    
  } else {
    Serial.print("Waiting for Hand Wave...");
    delay(25); // waits for next measurement if none is detected
  }
}

void calibrateUltrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void printUltrasonic() {
  // Serial.print("distance cm: ");
  // Serial.println(distanceCM);
  Serial.print("distance in: ");
  Serial.println(distanceIN);
} 