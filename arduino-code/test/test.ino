#include <Servo.h>


const int soundSensorPin = A0;
const int buzzerPin = 3;

const int rgbRedPin = 9;
const int rgbGreenPin = 10;
const int rgbBluePin = 11;





Servo myservo;
bool open = false;



void setup() {
  Serial.begin(9600);
  

  // put your setup code here, to run once:
  myservo.attach(6);

}

void loop() {
  testRgbLed();
  // testBuzzer();
  // testSoundSensor();
  // testServo();
}



void testRgbLed() {
  analogWrite(rgbRedPin, 0);
  analogWrite(rgbGreenPin, 255);
  analogWrite(rgbBluePin, 0);



  for (int i = 0; i <= 255; i++) {
    Serial.print("Rot: ");
    Serial.println(i);
    analogWrite(rgbRedPin, i);
    delay(150);
  }

}


void testBuzzer() {
  tone(3, 500, 500);
  delay(350);
}


void testSoundSensor() {
  int val = analogRead(soundSensorPin);
  Serial.println(val);
  delay(1000);
}



void testServo() {
  closeFlower();
  delay(2000);
  openFlower();
}

void openFlower() {
  if (!open) {
    for(int i = 90; i >= -90; i -= 10) {
      myservo.write(90-i);
      delay(200);
    }
    open = true;
  }
  
}

void closeFlower() {
  if (open) {
    for(int i = -90; i <= 90; i += 10) {
      myservo.write(90-i);
      delay(200);
    }
    open = false;
  }
}