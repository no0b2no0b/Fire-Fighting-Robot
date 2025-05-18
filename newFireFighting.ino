#include<ESP32Servo.h>

Servo servo;

#define in1 12 //Motor1 L298 Pin in1
#define in2 14 //Motor1 L298 Pin in2
#define in3 27 //Motor2 L298 Pin in3
#define in4 26 //Motor2 L298 Pin in4
#define rightflame 19
#define frontflameana 15
#define frontflamedigi 16
#define leftflame 21
#define servopin 13
#define pump 25
#define gas 23

int sright, sleft, sfrontana, sfrontdigi;

void setup()
{ // put your setup code here, to run once
  Serial.begin(9600); // start serial communication at 9600bps
  pinMode(rightflame, INPUT);// declare fire sensor pin as input
  pinMode(frontflamedigi, INPUT);
  pinMode(frontflameana, INPUT);// declare fire sensor pin as input
  pinMode(leftflame, INPUT);// declare fire sensor pin as input
  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3
  pinMode(in4, OUTPUT); // declare as output for L298 Pin in4
  pinMode(pump, OUTPUT);
  pinMode(gas, INPUT);
  servo.attach(servopin);
  servo.write(90);
  delay(500);
  servo.write(150);
  delay(500);
  servo.write(30);
  delay(500);
  servo.write(90);
}
void loop()
{
  if(!digitalRead(gas))
  {
    Serial.println("gas");
  }
    
  sright = digitalRead(rightflame);
  sfrontana = analogRead(frontflameana);
  sfrontdigi = digitalRead(frontflamedigi);
  sleft = digitalRead(leftflame);

  Serial.print("analog : ");
  Serial.println(sfrontana);
  Serial.print("digitla : ");
  Serial.println(sfrontdigi);
  Serial.print("sleft : ");
  Serial.println(sleft);
  Serial.print("sright : ");
  Serial.println(sright);

  if(sfrontana<500)
  {
    Serial.println("fire in range");
    Stop();
    digitalWrite(pump, 1);
    servoPulse();

  }

  else if(sright==0 && sfrontdigi == 0)
  { 
    Serial.println("fire on right");
    turnRight();
    delay(500);
  }

  else if(sleft==0 && sfrontdigi==0)
  {
    Serial.println("fire on left");
    turnLeft();
    delay(500);
  }

  else if(sfrontana>=501 && sfrontana<=3000)
  {
    Serial.println("fire on ahead");
    digitalWrite(pump, 0);
    forward();
  }
  else  
  {
    digitalWrite(pump, LOW);
    Serial.println("nothing");
  }
}

void servoPulse ()
{
  Serial.println("using servo");
  for(int i = 90; i<=130; i+=5)
  {
    servo.write(i);
    delay(50);
  }
  for(int i = 130; i<=50; i-=5)
  {
    servo.write(i);
    delay(50);
  }
  for(int i = 50; i<=90; i+=5)
  {
    servo.write(i);
    delay(50);
  }
}
void forward()
{  
  Serial.println("moving forward");
  digitalWrite(in1, HIGH); //Right Motor forward Pin
  digitalWrite(in2, LOW); //Right Motor backward Pin
  digitalWrite(in3, HIGH); //Left Motor backward Pin
  digitalWrite(in4, LOW); //Left Motor forward Pin
}
void backward()
{
  Serial.println("moving backward");
  digitalWrite(in1, LOW); //Right Motor forward Pin
  digitalWrite(in2, HIGH); //Right Motor backward Pin
  digitalWrite(in3, LOW); //Left Motor backward Pin
  digitalWrite(in4, HIGH); //Left Motor forward Pin
}
void turnRight()
{ 
  Serial.println("turning right");
  digitalWrite(in1, HIGH); //Right Motor forward Pin
  digitalWrite(in2, LOW); //Right Motor backward Pin
  digitalWrite(in3, LOW); //Left Motor backward Pin
  digitalWrite(in4, HIGH); //Left Motor forward Pin
}
void turnLeft()
{
  Serial.println("turning left");
  digitalWrite(in1, LOW); //Right Motor forward Pin
  digitalWrite(in2, HIGH); //Right Motor backward Pin
  digitalWrite(in3, HIGH); //Left Motor backward Pin
  digitalWrite(in4, LOW); //Left Motor forward Pin
}
void Stop()
{ 
  Serial.println("stopping");
  digitalWrite(in1, LOW); //Right Motor forward Pin
  digitalWrite(in2, LOW); //Right Motor backward Pin
  digitalWrite(in3, LOW); //Left Motor backward Pin
  digitalWrite(in4, LOW); //Left Motor forward Pin
}