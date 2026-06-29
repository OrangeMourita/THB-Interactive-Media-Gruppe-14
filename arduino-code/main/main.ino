#include <Servo.h>

const int analog = A0;
const int digital = 2;
const int R = 12;
const int G = 13;
const int servo = 9;
const int buzzer = 3;

Servo myservo;
bool open = false;

int val = 0;
int messungen[50];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(buzzer, OUTPUT);
  myservo.attach(servo);
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

int dif(int messungen[]) {
  int min = messungen[0];
  int max = messungen[0];

  for (int i = 1; i < 50; i++) {
    if (messungen[i] > max) {
      max = messungen[i];
    } else if (messungen[i] < min) {
      min = messungen[i];
    }
  }
    return max-min;
  
}

void checkDifs(int difs[]) {
  int threshold = 20;
  int counter = 0;
  for (int i = 0; i < 10; i++) {
    if (difs[i] >= threshold) {
      counter += 1;
    }
  }
  if (counter >= 4) {
    digitalWrite(G, LOW);
    digitalWrite(R, HIGH);
    closeFlower();
    delay(1000);
  } else {
    digitalWrite(G, HIGH);
    digitalWrite(R, LOW);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    openFlower();
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int difs[10];
  for(int i = 0; i < 10; i++) {
    for(int i = 0; i < 50; i++) {
      val = analogRead(analog);
      //Serial.println(val);
      messungen[i] = val;
      delay(10);
    }
    int difference = dif(messungen);
    Serial.println(difference);
    difs[i] = difference;
    checkDifs(difs);
  }
  /*
  digitalWrite(G, HIGH);
  openFlower();
  delay(1000);
  digitalWrite(G, LOW);
  closeFlower();
  delay(1000);
  */
}
