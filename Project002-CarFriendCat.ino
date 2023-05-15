#include <Servo.h>
Servo myservo; //ประกาศตัวแปรแทน Servo
const int trig = 11; //ประกาศขา trig
const int echo = 12; //ประกาศขา echo
//Define variables
long duration, distance; //ประกาศตัวแปรเก็บค่าระยะ

// Motor A
int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 6; //   เพื่อให้ PWM สามารถควบคุมความเร็วมอเตอร์ 

// Motor B
int dir1PinB = 5;
int dir2PinB = 6;
int speedPinB = 7; // เพื่อให้ PWM สามารถควบคุมความเร็วมอเตอร์

void setup()
{
  
  myservo.attach(8); // กำหนดขา 8 ควบคุม Servo
  //Begin Serial communication
  Serial.begin(9600); // Starts the serial communication at a baudrate of 9600
  //กำหนด ขา เพื่อใช้ในการควบคุมการทำงานของ  Motor ผ่านทาง L298N
  pinMode(dir1PinA,OUTPUT);
  pinMode(dir2PinA,OUTPUT);
  pinMode(speedPinA,OUTPUT);
  pinMode(dir1PinB,OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  pinMode(speedPinB,OUTPUT);
  //Define inputs and outputs
  pinMode(echo, INPUT); //สั่งให้ขา echo ใช้งานเป็น input
  pinMode(trig, OUTPUT); //สั่งให้ขา trig ใช้งานเป็น output
}

void loop()
{
  myservo.write(70); // สั่งให้ Servo หมุนไปองศาที่ 60
  delay(250); // หน่วงเวลา 1000ms
  myservo.write(110); // สั่งให้ Servo หมุนไปองศาที่ 120
  delay(250); // หน่วงเวลา 1000ms
  digitalWrite(trig, LOW); 
  delayMicroseconds(5); 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(5); 
  digitalWrite(trig, LOW); //ใช้งานขา trig
 
  duration = pulseIn(echo, HIGH); //อ่านค่าของ echo
  distance = (duration/2) / 29.1; //คำนวณเป็น centimeters
  Serial.print(distance); 
  Serial.print(" cm\n");
   if(distance <= 10)
  {
    // Motor A
  analogWrite(speedPinA,100); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinA,LOW);
  digitalWrite(dir2PinA,HIGH);
// Motor B
  analogWrite(speedPinB,100); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinB,LOW);
  digitalWrite(dir2PinB,HIGH);
  }
  else
  {
// Motor A
  analogWrite(speedPinA, 100); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);

// Motor B
  analogWrite(speedPinB, 100); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  }
}
