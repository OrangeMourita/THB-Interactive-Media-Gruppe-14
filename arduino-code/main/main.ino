#include <Servo.h>

// ---------------------- Pins ----------------------

const int soundPin = A0;

const int servoPin = 6;
const int buzzerPin = 3;

const int rgbRedPin = 9;
const int rgbGreenPin = 10;
const int rgbBluePin = 11;

// ---------------------- Einstellungen ----------------------

const int WINDOW_COUNT = 5;
const int SAMPLE_COUNT = 100;
const int SAMPLE_DELAY = 5;

// Schwellwerte (ggf. anpassen)
const int OPEN_THRESHOLD = 60;
const int CLOSE_THRESHOLD = 80;

// ---------------------- Globale Variablen ----------------------

Servo myservo;

bool flowerOpen = true;

// ---------------------- Setup ----------------------

void setup() {

  Serial.begin(9600);

  pinMode(rgbRedPin, OUTPUT);
  pinMode(rgbGreenPin, OUTPUT);
  pinMode(rgbBluePin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  myservo.attach(servoPin);

  openFlower();
}

// ---------------------- Servo ----------------------

void openFlower() {
  if (flowerOpen) {
    Serial.println("Blume bereits geöffnet!");
    return;
  };

  for(int i = 90; i >= -90; i -= 10) {
      myservo.write(90-i);
      delay(150);
    }

  flowerOpen = true;
}

void closeFlower() {
  if (!flowerOpen) {
    Serial.println("Blue bereits geschlossen!");
    return;
  };

  for(int i = -90; i <= 90; i += 10) {
      myservo.write(90-i);
      delay(150);
  }

  flowerOpen = false;
}

// ---------------------- RGB ----------------------

void changeRgbColor(byte red, byte green, byte blue) {

  analogWrite(rgbRedPin, red);
  analogWrite(rgbGreenPin, green);
  analogWrite(rgbBluePin, blue);
}

// ---------------------- Soundsensor ----------------------

int measureDifference() {

  int minimum = 1023;
  int maximum = 0;

  for (int i = 0; i < SAMPLE_COUNT; i++) {

    int value = analogRead(soundPin);

    if (value < minimum)
      minimum = value;

    if (value > maximum)
      maximum = value;

    delay(SAMPLE_DELAY);
  }

  return maximum - minimum;
}

int measureNoiseLevel() {

  long sum = 0;

  for (int i = 0; i < WINDOW_COUNT; i++) {

    int diff = measureDifference();

    Serial.print("Fenster ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(diff);

    sum += diff;
  }

  return sum / WINDOW_COUNT;
}

// ---------------------- Hauptprogramm ----------------------

void loop() {

  int noise = measureNoiseLevel();

  Serial.print("Durchschnitt: ");
  Serial.println(noise);

  // ---------- LED ----------

  if (noise < OPEN_THRESHOLD) {

    // Grün
    changeRgbColor(0, 255, 0);

  } else if (noise < CLOSE_THRESHOLD) {

    // Magenta
    changeRgbColor(255,   0, 255); delay(1000); // Magenta

  } else {

    // Rot
    changeRgbColor(255, 0, 0);

  }

  // ---------- Blume ----------

  if (flowerOpen && noise > CLOSE_THRESHOLD) {

    Serial.println("Zu laut -> Blume schließt");

    tone(buzzerPin, 800, 2200);

    closeFlower();

  }

  else if (!flowerOpen && noise < OPEN_THRESHOLD) {

    Serial.println("Wieder ruhig -> Blume öffnet");

    openFlower();

  }

  delay(1000);
}