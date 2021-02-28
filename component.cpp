#include "component.h"

#define HIGH 0x1
#define LOW  0x0
#define INPUT 0x0
#define OUTPUT 0x1
extern "C"
{
  void digitalWrite(int pin,int value);
  void analogWrite(int pin,int value);
  int digitalRead(int pin);
  int analogRead(int pin);
  void pinMode(int pin, int mode);
  void delay(int time);
}

_motor Lmotor(1),Rmotor(0);
_beep Beep;
_key Key;
_sensor Sensor;

static const int Left_motor=8;//左电机(IN3) 输出0  前进   输出1 后退
static const int Left_motor_pwm=9;//左电机PWM调速
static const int Right_motor_pwm=10;// 右电机PWM调速
static const int Right_motor=11;// 右电机(IN1)  输出0  前进   输出1 后退
static int min(int a, int b){return a<b?a:b;}
static const int keypin = 16;
static const int beeppin = 17;
static const int sensorpin = 6;

_beep::_beep(){pinMode(beeppin,OUTPUT);}
void _beep::on(){digitalWrite(beeppin,HIGH);}
void _beep::off(){digitalWrite(beeppin,LOW);}
_key::_key(){pinMode(keypin,INPUT);}
int _key::clicked(){return digitalRead(keypin);}
_sensor::_sensor(){pinMode(sensorpin, INPUT);}
int _sensor::blocked(){return !digitalRead(sensorpin);}

_motor::_motor(int isLeft)
{
	this->isLeft = isLeft;
	speed = 0;
	rev = 0;
	if(isLeft)
	{
		pinMode(Left_motor,OUTPUT);
 		pinMode(Left_motor_pwm,OUTPUT);
	}
	else
	{
		pinMode(Right_motor_pwm,OUTPUT);
  		pinMode(Right_motor,OUTPUT);
	}
}

void _motor::run(int speed)
{
        this->speed = speed;
	if(isLeft == 0)
	{
		digitalWrite(Right_motor,DRIVE);
  		digitalWrite(Right_motor_pwm,HIGH); 
  		analogWrite(Right_motor_pwm,speed);
	}
	else
	{
		digitalWrite(Left_motor,DRIVE);
  		digitalWrite(Left_motor_pwm,HIGH);   
 		//analogWrite(Left_motor_pwm,(int)(1.3*speed));
                analogWrite(Left_motor_pwm,min((int)(1.3*speed),255));//左后轮固定损坏补正
	}
}

void _motor::stop()
{
	if(isLeft == 0)
  		analogWrite(Right_motor_pwm,0);     
	else
  		analogWrite(Left_motor_pwm, 0);     
}

void _motor::reverse()
{
  rev = !rev;
  if(isLeft)digitalWrite(Left_motor,rev);
  else digitalWrite(Right_motor,rev);
}

int _motor::speedchange(int value)
{
	int s = speed + value, err = 0;
	if(s > 255)
		s = 255,err = 1;
	else if (s < 0)
		s = 0, err = 1;
	this->run(speed);
	if(err)
		return -1;
	return speed;
}


void forward(int speed)
{
  if(Lmotor.rev)Lmotor.reverse();
  if(Rmotor.rev)Rmotor.reverse();
  Lmotor.run(speed);
  Rmotor.run(speed);
}

void back(int speed)
{
  if(!Lmotor.rev)Lmotor.reverse();
  if(!Rmotor.rev)Rmotor.reverse();
  Lmotor.run(speed);
  Rmotor.run(speed);
}

void brake()
{
  Lmotor.stop();
  Rmotor.stop();
}
