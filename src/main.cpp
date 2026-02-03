#include <Arduino.h>
#define trigPin 9
#define echoPin 10
void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    long distance = duration * 0.034/2;
    serial.print("Distance");
    serial.print(distance);
    serial.print(" cm");
    delay(1000);
}