#include <Arduino.h>
#include <Servo.h>

const int trigPin = 2;
const int echoPin = 3;
const int buzzer = 8;
const int led = 11;

const int Range = 25;

Servo radarServo;
Servo pointerServo;

bool objectAlreadyDetected = false;

int getDistance() {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);

    if (duration == 0)
        return 0;

    return duration * 0.0343 / 2.0;
}

void handleDetection() {

    digitalWrite(led, HIGH);
    tone(buzzer, 1000);

    if (!objectAlreadyDetected) {

        pointerServo.write(90);
        delay(2000);
        pointerServo.write(150);

        objectAlreadyDetected = true;
    }

    while (true) {

        int dist = getDistance();

        Serial.print("Distance: ");
        Serial.println(dist);

        if (dist == 0 || dist > Range) {

            objectAlreadyDetected = false;

            digitalWrite(led, LOW);
            noTone(buzzer);

            break;
        }

        delay(100);
    }
}

void setup() {

    Serial.begin(9600);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    pinMode(buzzer, OUTPUT);
    pinMode(led, OUTPUT);

    radarServo.attach(9);
    pointerServo.attach(10);

    radarServo.write(10);
    pointerServo.write(150);
}

void loop() {

    for (int angle = 10; angle <= 170; angle++) {

        radarServo.write(angle);
        delay(20);

        int dist = getDistance();

        Serial.print("Distance: ");
        Serial.println(dist);

        if (dist > 0 && dist <= Range) {

            // Radar stops at current angle
            radarServo.write(angle);

            handleDetection();
        }
    }

    for (int angle = 170; angle >= 10; angle--) {

        radarServo.write(angle);
        delay(20);

        int dist = getDistance();

        Serial.print("Distance: ");
        Serial.println(dist);

        if (dist > 0 && dist <= Range) {

            // Radar stops at current angle
            radarServo.write(angle);

            handleDetection();
        }
    }
}