// GaragePhase.hpp

#ifndef GARAGE_PHASE_H
#define GARAGE_PHASE_H

#include "../Phase.hpp"
#include "ev3api.h"
#include <string>

class GaragePhase: public Phase {
public:
	int diff_prev=20;
  int forwardl=60;
 	int forwardr=60;
	int gyrooffset=0;
	int offset=0;
	int tailangle=3;
	int boundary=11;
	int boundary2=26;
	int cnt=0;
	int cnt2=0;
	int tim2=0;
	int pflag=0;
	int endtime;
	float Kp = 1.5;
	float Kd = 12.00;
	int mcntl=0;
	int mcntr=0;
	int LIGHT_WHITE=30;
	int LIGHT_BLACK=0;
	int data[300];
	int mcntlval;
	int mcntrval;
	int stoptime;
	FILE *fp;
	GaragePhase(std::string name, Balancer* balancer);
	GaragePhase(std::string name, Balancer* balancer,int setforwardl,int setforwardr,int setending,int gyoffset,int turnoffset,float ikp,float ikd,int itailangle, int setmcntl, int setmcntr, int setstoptime);
	void initialize();
	void calc_param(int time,int* forward,signed char* turn,int color);
	void calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T);
	bool isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T);
};

#endif
