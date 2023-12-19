#include <SoftwareSerial.h>
SoftwareSerial left(7,8);
int LRSSI;
int count, l, r, leftsq, rightsq, diff, diffsq;
// L298N Control Pins
int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 4;
int motor2pin2 = 5;
void setup() 
{
left.begin(9600);
Serial.begin(9600);
// Set L298N Control Pins as Output
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
}

void loop() 
{
  int count = 2;
  if(count==2)
  {
    LRSSI = left.read();
    l = LRSSI;
    Serial.print("LRSSI: ");
    Serial.println(l);
    leftsq = l*l;
    count = count-1;
  }
    if(count==1)
  {
    LRSSI = left.read();
    r = LRSSI;
    Serial.print("RRSSI: ");
    Serial.println(r);
    rightsq = r*r;
    count = count-1;
  }
  if(count == 0)
  {
    diff = l-r;
    diffsq = leftsq-rightsq;
    if( diff > 0 &&  diffsq < 1000 && l < 55 && r < 55 )   // diff>0 means obj is in right side and vice versa
    {
      moveStop(); 
      delay(400);
      moveStop();
    }
     if( diff > 0 &&  diffsq < 1000 && l > 55 && r > 55 )   // diff>0 means obj is in right side and vice versa
    {
      moveForward(); 
      delay(400);
      moveStop();
    }
    if( diff < 0 &&  diffsq > -1000 && l < 55 && r < 55 )
    {
      moveStop();
      delay(400);
      moveStop();
    }
    if( diff < 0 &&  diffsq > -1000 && l > 55 && r > 55 )
    {
      moveForward();
      delay(400);
      moveStop();
    }
    if( diff > 0 )
    {
      if( diffsq > 1000)
      {
        turnRight();
        delay(400);
        moveStop();
      }
    }
    if ( diff < 0)
    {
      if ( diffsq < -1000)
      {
        turnLeft();
        delay(400);
        moveStop();
      }
    }
    delay(600);
  }
}

void moveStop()       // Move Stop Function for Motor Driver.
{
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  Serial.println("STOP");
}

void moveForward()    // Move Forward Function for Motor Driver.
{
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  Serial.println("FORWARD");
}

void moveBackward()   // Move Backward Function for Motor Driver.
{
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  Serial.println("BACK");
}

void turnRight()      // Turn Right Function for Motor Driver.
{
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  Serial.println("RIGHT");
}

void turnLeft()       // Turn Left Function for Motor Driver.
{
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  Serial.println("LEFT");
}
