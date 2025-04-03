//Team Member: Kel Shang, Rin Nishiwaki
//Team Name: Box Twisters

/* #include <Servo.h>

Servo myservo;
const int buttonPin = 2;

int buttonState = 0;
int previousButtonState = 0;

void setup() {
  myservo.attach(9);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
buttonState = digitalRead(buttonPin);
Serial.print("Button State: ");
Serial.println(buttonState);
  
  if (buttonState != previousButtonState) {
    if(buttonState == HIGH){
    myservo.write(180);
    } else {
    myservo.write(0);
  }
  }
  previousButtonState = buttonState;
}*/

 #include <Servo.h>

Servo myservo;
const int buttonPin = 2;

int buttonState = 0;

void setup() {
  myservo.attach(9);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
buttonState = digitalRead(buttonPin);
Serial.print("Button State: ");
Serial.println(buttonState);
  
  if (buttonState == HIGH) {
    myservo.write(180);
  } else {
    myservo.write(0);
  }
} 
