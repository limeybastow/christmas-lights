// Crhistmas lights test program
 
int warmLights = 6;
int coolLights = 5;
 
void flash (int, int);
 
void oneFade (int, int);
 
void oppositeFade (int, int);
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("STARTING UP");
 
  pinMode(warmLights, OUTPUT);
  pinMode(coolLights, OUTPUT);
}
 
int next;
 
void loop() {
  // flash(warmLights, 1000);
  // oneFade(warmLights, 10);
  // bothOn(warmLights, 32, coolLights, 196);
  // crossFade(warmLights, coolLights);
  // altBlink(warmLights, coolLights);
  overlapBlink(warmLights, coolLights);
}
 
void flash (int pin, int delayTime) {
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
    delay(delayTime);
}
 
void oneFade (int pin, int delayTime) {
  for(int i = 0; i <= 255; i++) {
    analogWrite(pin, i);
    delay(delayTime);
  };
  for(int i = 255; i >= 0; i--) {
    analogWrite(pin, i);
    delay(delayTime);
  }
}
 
void bothOn (int pin1, int pin1Brightness, int pin2, int pin2Brightness) {
  analogWrite(pin1, pin1Brightness);
  delay(5);
  digitalWrite(pin1, LOW);
  analogWrite(pin2, pin2Brightness);
  delay(5);
  digitalWrite(pin2, LOW);
} 

void holdBothOn (int pin1, int pin1Brightness, int pin2, int pin2Brightness, long holdTime) {
  long startTime = micros();
  long holdTimeMicros = holdTime * 1000;
  while ((micros() - startTime) <= holdTimeMicros && micros() >= startTime) {
    bothOn(pin1, pin1Brightness, pin2, pin2Brightness);
  }
}

void crossFade (int pin1, int pin2) {
  for(int i = 0; i <= 255; i = i + 3) {
    // Serial.print("GOT HERE\n");
    holdBothOn(pin1, i, pin2, 255 - i, 2);
  }
  for(int i = 0; i <= 255; i = i + 3) {
    // Serial.print("GOT HERE\n");
    holdBothOn(pin1, 255 - i, pin2, i, 2);
  }
}

void altBlink (int pin1, int pin2) {
    holdBothOn(pin1, 0, pin2, 255, 500);
    holdBothOn(pin1, 255, pin2, 0, 500);
}

void overlapBlink (int pin1, int pin2) {
    holdBothOn(pin1, 0, pin2, 255, 500);
    holdBothOn(pin1, 255, pin2, 255, 500);
    holdBothOn(pin1, 255, pin2, 0, 500);
    holdBothOn(pin1, 255, pin2, 255, 500);
}
