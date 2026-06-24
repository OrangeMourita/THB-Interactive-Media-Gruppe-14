const int analog = A0;
const int digital = 2;
const int R = 13;
const int G = 12;
const int B = 11;

int val = 0;
int messungen[10];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

int dif(int messungen[]) {
  int min = messungen[0];
  int max = messungen[0];

  for (int i = 1; i < 10; i++) {
    if (messungen[i] > max) {
      max = messungen[i];
    } else if (messungen[i] < min) {
      min = messungen[i];
    }
    return max-min;
  }
}

void checkDifs(int difs[]) {
  int threshold = 4;
  int counter = 0;
  for (int i = 0; i < 10; i++) {
    if (difs[i] >= threshold) {
      counter += 1;
    }
  }
  if (counter >= 3) {
    digitalWrite(R, HIGH);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  int difs[10];
  for(int i = 0; i < 10; i++) {
    for(int i = 0; i < 10; i++) {
      val = analogRead(analog);
      messungen[i] = val;
      delay(20);
    }
    int difference = dif(messungen);
    Serial.println(difference);
    difs[i] = difference;
    delay(100);
  }
}
