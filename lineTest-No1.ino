#include <Servo.h>
#define SERVO_PIN 9
Servo servo_test;        //initialize a servo object for the connected servo  
//                
int angle = 0; 
int angle1 = 90; 
#define ena 11 //mottor right
#define in1 7
#define in2 6
#define in3 5
#define in4 4
#define enb 3 //mottor left
bool isAuto = false;
//line
#define SLeft 12 // cam bien re trai
#define S1 A5
#define S2 A4
#define S3 A3
#define S4 A2
#define S5 A1
#define SRight A0 // cam bien re phai


int s1Value = 0;
int s2Value = 0;
int s3Value = 0;
int s4Value = 0;
int s5Value = 0;
int sRValue = 0;
int sLValue = 0;
int countTurnRight = 0;
int countTurnLeft = 0;
void setup() {
  // put your setup code here, to run once:
//  servo_test.attach(9);
  Serial.begin(9600);
  servo_test.attach(SERVO_PIN); 
  servo_test.write(90);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  pinMode(SLeft, INPUT); 
  pinMode(SRight, INPUT);
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //right
  // trắng A0
  autoMove();
//  rotateRight90();
//  stopMove();
//  delay(1000);
}
void autoMove(){
    readIRSensor();
    if (sRValue == 1)
    {
      if (countTurnRight < 2)
      {
        stopMove();
            delay(20);
        rotateRight90();
        countTurnRight++;
        while (countTurnRight < 2)
        {
          readIRSensor();
          lineFollowing();
          if (sRValue == 1)
          {
            stopMove();
            delay(20);
            rotateRight90();
            countTurnRight++;
          }
        }
      }
    }
    if (sLValue == 1)
    {
      if (countTurnLeft < 2)
      {
        stopMove();
            delay(20);
        rotateLeft90();
        countTurnLeft++;
        while (countTurnLeft < 2)
        {
          readIRSensor();
          lineFollowing();
          if (sLValue == 1)
          {
            stopMove();
            delay(20);
            rotateLeft90();
            countTurnLeft++;
          }
        }
      }      
    }
    if ((s1Value == 1) && (s2Value == 1) && (s3Value == 1) && (s4Value == 1) && (s5Value == 1))
    {
      stopMove();
      riseFlag();
    }
    else
    {
      lineFollowing();
    }
  }
void lineFollowing() {

    if ((s1Value == 0) && (s2Value == 0) && (s3Value == 0) && (s4Value == 0) && (s5Value == 1))
    {
       analogWrite(ena, 0);
       analogWrite(enb, 130);
       moveForward();
    }
    else if ((s1Value == 0) && (s2Value == 0) && (s3Value == 1) && (s4Value == 1) && (s5Value == 1))
    {
       analogWrite(ena, 10);
       analogWrite(enb, 120);
       moveForward();
    }
     else if ((s1Value == 0) && (s2Value == 0) && (s3Value == 1) && (s4Value == 1) && (s5Value == 1))
    {
      if (countTurnRight < 2)
      {
        stopMove();
        delay(20);
        rotateRight90();
        countTurnRight++;
        while (countTurnRight < 2)
        {
          readIRSensor();
          lineFollowing();
          if (sRValue == 1 || ((s1Value == 0) && (s2Value == 0) && (s3Value == 1) && (s4Value == 1) && (s5Value == 1)))
          {
            stopMove();
            delay(20);
            rotateRight90();
            countTurnRight++;
          }
        }
      }
       
    }
    else if ((s1Value == 0) && (s2Value == 0) && (s3Value == 0) && (s4Value == 1) && (s5Value == 0))
    {
       analogWrite(ena, 10);
       analogWrite(enb, 120);
       moveForward();
    }
    else if ((s1Value == 0) && (s2Value == 0) && (s3Value == 1) && (s4Value == 1) && (s5Value == 0))
    {
       analogWrite(ena, 40);
       analogWrite(enb, 110);
       moveForward();
    }
    else if ((s1Value == 0) && (s2Value == 0) && (s3Value == 1) && (s4Value == 0) && (s5Value == 0))
    {
       analogWrite(ena, 110);
       analogWrite(enb, 110);
       moveForward();
    }
    else if ((s1Value == 0) && (s2Value == 1) && (s3Value == 1) && (s4Value == 0) && (s5Value == 0))
    {
       analogWrite(ena, 110);
       analogWrite(enb, 40);
       moveForward();
    }
     else if ((s1Value == 0) && (s2Value == 1) && (s3Value == 0) && (s4Value == 0) && (s5Value == 0))
    {
       analogWrite(ena, 120);
       analogWrite(enb, 10);
       moveForward();
    }
    else if ((s1Value == 1) && (s2Value == 1) && (s3Value == 1) && (s4Value == 0) && (s5Value == 0))
    {
       analogWrite(ena, 120);
       analogWrite(enb, 10);
       moveForward();
    }
    else if ((s1Value == 1) && (s2Value == 1) && (s3Value == 1) && (s4Value == 0) && (s5Value == 0))
    {
      if (countTurnLeft < 2)
      {
        stopMove();
        delay(20);
        rotateLeft90();
        countTurnLeft++;
        while (countTurnLeft < 2)
        {
          readIRSensor();
          lineFollowing();
          if (sLValue == 1 || ((s1Value == 1) && (s2Value == 1) && (s3Value == 1) && (s4Value == 0) && (s5Value == 0)))
          {
            stopMove();
            delay(20);
            rotateLeft90();
            countTurnLeft++;
          }
        }
      }
    }
    else if ((s1Value == 1) && (s2Value == 0) && (s3Value == 0) && (s4Value == 0) && (s5Value == 0))
    {
       analogWrite(ena, 130);
       analogWrite(enb, 0);
       moveForward();
    }

}

void readIRSensor()
{
  //Đọc data từ cảm biến hồng ngoại
  sLValue = digitalRead(SLeft);
  Serial.print(sLValue);
  Serial.print("  ||  ");
  s1Value = digitalRead(S1);
  Serial.print(s1Value);
  Serial.print(" ");
  s2Value = digitalRead(S2);
  Serial.print(s2Value);
  Serial.print(" ");
  s3Value = digitalRead(S3);
  Serial.print(s3Value);
  Serial.print(" ");
  s4Value = digitalRead(S4);
  Serial.print(s4Value);
  Serial.print(" ");
  s5Value = digitalRead(S5);
  Serial.print(s5Value);
  Serial.print(" ");
  sRValue = digitalRead(SRight);
  Serial.print(" || ");
  Serial.println(sRValue);
}
void moveForward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
}

void moveBackward()
{
  analogWrite(ena, 110);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enb, 110);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
}

void rotateRight90()
{
  long int startTime = millis();
  long int endTime = 0;
  do
  {
    Serial.println("Rotate left");
    analogWrite(ena, 110);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enb, 110);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    readIRSensor();
    endTime = millis();
  }
  while (s3Value != 1 || (endTime - startTime) < 300 - 100 * countTurnRight);
  
}

void riseFlag()
{

  
  //Code phất cờ\
  
servo_test.write(angle); 
  delay(100);
}

void rotateLeft90()
{
  
  long int startTime = millis();
  long int endTime = 0;
  Serial.println("Rotate right");
  do
  {
    analogWrite(ena, 110);
    digitalWrite(in1, HIGH);
    
    digitalWrite(in2, LOW);
    analogWrite(enb, 110);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    readIRSensor();
    endTime = millis();
  }
  while (s3Value != 1 || (endTime - startTime) < 300 - 100 * countTurnLeft);

//  moveForward();
//  delay(100);
}

void stopMove()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
//    gServo.write(0);
}
