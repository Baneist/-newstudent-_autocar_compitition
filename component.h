//已经对象化 左轮Lmotor,右轮Rmotor
#ifndef COMPONENT_H
#define COMPONENT_H

#define DRIVE 0x0
#define REVERSE 0x1

class _sensor//前避障探头(比赛里用来开机启动车车所以把另外一个拆了)
{
public:
  _sensor();
  int blocked();
};

class _beep//蜂鸣器
{
public:
  _beep();
  void on();
  void off();
};

class _key
{
public:
  _key();
  int clicked();
};

class _motor
{
public:
	int isLeft;
	int speed;
	int rev;
        _motor(int isLeft);
public: //基础功能封装
	void run(int speed);
	void stop();
        void reverse();
        int speedchange(int value);
};
//整车行动封装
void forward(int speed);
void back(int speed);
void brake();
void left();

//所用到的元件封装
extern _motor Lmotor,Rmotor;
extern _beep Beep;
extern _key Key;
extern _sensor Sensor;
#endif
