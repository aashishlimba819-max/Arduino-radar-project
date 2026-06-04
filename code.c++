#include<Arduino.h>
#include<Servo.h>

const int trigPin=2;
const int echoPin=3;
const int Buzzer=8;
const int led=11;

const int Range=25;

Servo radarServo;
Servo pointerServo;
long duration;
int distance;

int calDistance();
void setup(){
    radarServo.attach(9);
    pointerServo.attach(10);
    digital.Write(trigPin,OUTPUT);
    digital.Write(echoPin,INPUT);

    digital.Write(Buzzer,OUTPUT);
    digital.Write(led,OUTPUT);

    radarServo.Write(0);
    pointerServo.write(0);

}
void loop(){



}
int calDistance(){
digital.Write(trigPin,LOW);
delayMicrosecond(2);
digital.Write(trigPin,HIGH);
delayMicrosecond(10);
digital.Write(trigPin,LOW);
duration=pulseIn(echoPin,HIGH);

distance=duration*0.034/2;
return distance;
}