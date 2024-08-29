#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3); // RX, TX
int M1_F = 9;
int M1_R = 10;
int M2_F = 11;
int M2_R = 12;
int incommingByte;

void setup()
{
  pinMode(M1_F, OUTPUT);
  pinMode(M1_R, OUTPUT);
  pinMode(M2_F, OUTPUT);
  pinMode(M2_R, OUTPUT);
  BT.begin(9600);
}

void loop()
{
  if (BT.available() > 0)
    incommingByte = BT.read();
  else
    incommingByte = 0;
  

  switch (incommingByte)
  {
    case 'F': forward();
      break;
    case 'B': backward();
      break;
    case 'S': Stop();
      break;
    case 'R': Right();
      break;
    case 'L': left();
      break;
  }
}
void Stop()
{
  BT.println("STOP");
  digitalWrite(M1_F, LOW);
  digitalWrite(M1_R, LOW);
  digitalWrite(M2_F, LOW);
  digitalWrite(M2_R, LOW);
delay(100);
}
void forward()
{
  BT.println("FORWARD");
  digitalWrite(M1_F, HIGH);
  digitalWrite(M1_R, LOW);
  digitalWrite(M2_F, HIGH);
  digitalWrite(M2_R, LOW);
delay(100);
}
void backward()
{
  BT.println("BACK WARD");
  digitalWrite(M1_F, LOW);
  digitalWrite(M1_R, HIGH);
  digitalWrite(M2_F, LOW);
  digitalWrite(M2_R, HIGH);
delay(100);
}
void Right()
{
  BT.println("RIGHT");
  digitalWrite(M1_F, LOW);
  digitalWrite(M1_R, HIGH);
  digitalWrite(M2_F, HIGH);
  digitalWrite(M2_R, LOW);
delay(100);
}
void left()
{
  BT.println("LEFT");
  digitalWrite(M1_F, HIGH);
  digitalWrite(M1_R, LOW);
  digitalWrite(M2_F, LOW);
  digitalWrite(M2_R, HIGH);
delay(100);
}
