// DetectGoal.hpp

#ifndef DETECTGOAL_H
#define DETECTGOAL_H

#include "../Phase.hpp"
#include <string>

class DetectGoal: public Phase {
public:
	int cnt;
	int diff_prev=20;
	int forwardl=60;
	int forwardr=60;
	int gyrooffset=0;
	int mxsptime=5000;
	int data[100];
FILE *fp;
	DetectGoal(std::string name, Balancer* balancer);
	DetectGoal(std::string name, Balancer* balancer,int setforwardl,int setforwardr,int maxspeedtime,int gyoffset);
	void initialize();
	void calc_param(int time,int* forward,signed char* turn,int color);
	void calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T);
	bool isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T);
};

#endif
