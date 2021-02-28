# -newstudent-_autocar_compitition
新生杯小车竞赛 勇往直前车车人の代码仓库
放到ino文件的相同目录下就可以了 使用#include "componment.h"
做了简单的对象化
左轮对象Lmotor 右轮Rmotor 蜂鸣器Beep 按钮Key 红外避障Sensor(只做了一个，因为好像只用来处理启停)
红外传感器用的IRremote，就没有做单独的封装 霍尔传感器就之后再说
暂时先这样 轮子的封装总感觉不对味儿 到时候看需要再改吧
