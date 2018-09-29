// StraightPhase.hpp

#ifndef STRAIGHT_PHASE_H
#define STRAIGHT_PHASE_H

#include "../Phase.hpp"
#include <string>

class StraightPhase: public Phase {
public:
	int diff_prev=20;
	int forwardl=60;
	int forwardr=60;
	int colordi[50];
	int pwm_L_list[50];
	int pwm_R_list[50];
	int timel=0;
	int timer=0;
	int gyrooffset=0;
	int endtime=5000;
	FILE* fp;
	StraightPhase(std::string name, Balancer* balancer);
	StraightPhase(std::string name, Balancer* balancer,int setforwardl,int setforwardr,int setending,int gyoffset);
	void initialize();
	void calc_param(int time,int* forward,signed char* turn,int color);
	void calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T);
	bool isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T);
};

#endif
