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
void radarScan(int angle);
void setup(){
    radarServo.attach(9);
    pointerServo.attach(10);
    digital.Write(trigPin,OUTPUT);
    digital.Write(echoPin,INPUT);

    digital.Write(Buzzer,OUTPUT);
    digital.Write(led,OUTPUT);

    radarServo.Write(0);
    pointerServo.write(0);
    Serial.begin(9600);
}
void loop(){
for(int i=10;i<=170;i++){
    radarScan(i);
    
}
for(int i=170;i>=10;i--){
    radarScan(i);
    
}

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
void radarScan(int angle){
    radarServo.write(angle);
    int dist=calDistance();

    Serial.print("distance :");
    Serial.println(dist);

    while(dist>=0 && dist<=Range){
        radarServo.write(angle);
        digital.Write(led,HIGH);
        tone(Buzzer,1000);
        delay(10);
        tone(Buzzer,800);
        delay(10);
        tone(Buzzer,600);
        pointerServo.Write(angle);
    }
    delay(15);
}