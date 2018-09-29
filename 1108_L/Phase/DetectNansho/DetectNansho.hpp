// DetectNansho.hpp

#ifndef DETECTNANSHO_H
#define DETECTNANSHO_H

#include "../Phase.hpp"
#include <cmath>
#include <algorithm>
#include <string>

class DetectNansho: public Phase {
public:
	int cnt;
int data[100];
double Kp=1.13;
FILE *fp;
	DetectNansho(std::string name, Balancer* balancer);
	void initialize();
	void calc_param(signed char* forward,signed char* turn,int color);
	void calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T);
	bool isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T);
};

#endif
