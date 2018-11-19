/*
Cat Bell. Plays a tune when cat is on window sill.

Guide for distance sensor: https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/

Melody taken from https://www.arduino.cc/en/Tutorial/toneMelody
*/

#include "pitches.h"
#include "Arduino.h"

#define DISTANCETHRESHOLD 80

// pins
const int trigPin = 9;
const int echoPin = 10;
const int piezo = 3;
const int led = 11;

// defines variables
long duration;
int distance;

int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4};

void measureDistance() // Refer to linked distance sensor guide
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
}

void playMelody() // Refer to linked melody guide
{
  for (int thisNote = 0; thisNote < 8; thisNote++)
  {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(piezo, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(piezo);
  }
}

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  measureDistance();
  if (distance < DISTANCETHRESHOLD)
  {
    Serial.println("Triggered!");
    digitalWrite(led, HIGH);
    playMelody();
    delay(5000);
  }
  digitalWrite(led, LOW);
  delay(500);
}
