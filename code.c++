#include<Arduino.h>
#include<Servo.h>

const int trigPin=2;
const int echoPin=3;
const int Buzzer=8;
const int led=11;

const int Range=30;

Servo radarServo;
Servo pointerServo;
long duration;
int distance;

int calDistance();
void radarScan(int angle);
void setup(){
    radarServo.attach(9);
    pointerServo.attach(10);
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);

    pinMode(Buzzer,OUTPUT);
    pinMode(led,OUTPUT);

    radarServo.write(0);
    pointerServo.write(0);

    Serial.begin(9600);
}
void loop(){


for(int i=10;i<=170;i++){
    radarScan(i);
    digitalWrite(led,LOW);
    noTone(Buzzer);
}
for(int i=170;i>=10;i--){
    radarScan(i);
    digitalWrite(led,LOW);
    noTone(Buzzer);
}

}
int calDistance(){
digitalWrite(trigPin,LOW);
delayMicroseconds(2);
digitalWrite(trigPin,HIGH);
delayMicroseconds(10);
digitalWrite(trigPin,LOW);
duration=pulseIn(echoPin,HIGH);

distance=duration*0.034/2;
return distance;
}
void radarScan(int angle){
    radarServo.write(angle);
    int dist=calDistance();
    
    Serial.print("distance :");
    Serial.println(dist);

    while(dist>=0 && dist<=Range){
        radarServo.write(angle);
        digitalWrite(led,HIGH);
        tone(Buzzer,1000);
        delay(20);
        tone(Buzzer,800);
        dist = calDistance();
        
        pointerServo.write(angle);
    }
    delay(15);
}