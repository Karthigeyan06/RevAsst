#include <Servo.h>

const int trigPin = 2;
const int echoPin = 3;
const int greenLedPin = 6;
const int redLedPin = 7;
const int servoPin = 9;

const float criticalDistance = 6.0; 
const float minDistance = 10.0;

Servo myServo;
int servoInitialPosition = 90;
int servoActivatedPosition = 45; 

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(servoInitialPosition);

void loop() {
  float distance = getDistance(trigPin, echoPin);

  if (distance < criticalDistance) {
    Serial.println("Critical warning: Object very close!");
    myServo.write(servoActivatedPosition);
  } else {
    myServo.write(servoInitialPosition); 
  }

  if (distance < minDistance) {
    Serial.println("Warning: Object detected! Slow down.");
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
  } else {
    Serial.println("Distance clear.");
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
  }

  delay(500);
}

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration / 2) * 0.0343;

  return distance;
}
