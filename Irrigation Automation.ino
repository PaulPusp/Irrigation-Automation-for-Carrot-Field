const int moisturePins[3][2] = {
  {A0, A1}, // for 1st row
  {A2, A3}, //  2
  {A4, A5}  // 3
};

const int motorPins[3] = {2, 3, 4};

const int moistureThreshold = 273; //will change according to soil type, measure every time for our field we took 273

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(motorPins[i], OUTPUT);
    digitalWrite(motorPins[i], LOW);
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      pinMode(moisturePins[i][j], INPUT);
    }
  }
}

void loop() {
  for (int row = 0; row < 3; row++) {
    int moistureLevel1 = analogRead(moisturePins[row][0]);
    int moistureLevel2 = analogRead(moisturePins[row][1]);
    Serial.print("Row ");
    Serial.print(row + 1);
    Serial.print(": Sensor 1 = ");
    Serial.print(moistureLevel1);
    Serial.print(", Sensor 2 = ");
    Serial.println(moistureLevel2);
    if (moistureLevel1 < moistureThreshold || moistureLevel2 < moistureThreshold) {
      activateMotor(row);
    } else {
      deactivateMotor(row);
    }
  }

  delay(10000);
}

void activateMotor(int row) {
  digitalWrite(motorPins[row], HIGH);
  Serial.print("Activating motor for Row ");
  Serial.println(row + 1);
}

void deactivateMotor(int row) {
  digitalWrite(motorPins[row], LOW);
  Serial.print("Deactivating motor for Row ");
  Serial.println(row + 1);
}
