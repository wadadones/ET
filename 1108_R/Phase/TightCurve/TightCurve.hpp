// StraightPhase.hpp

#ifndef TIGHT_CURVE_H
#define TIGHT_CURVE_H

#include "../Phase.hpp"
#include <string>
#include <cmath>
#include <algorithm>

class TightCurve: public Phase {
public:
	int diff_prev=20;
  int forwardl=60;
 	int forwardr=60;
	int gyrooffset=0;
	int endtime=5000;
	FILE *fp;
	TightCurve(std::string name, Balancer* balancer);
	TightCurve(std::string name, Balancer* balancer,int setforwardl,int setforwardr,int setending,int gyoffset);
	void initialize();
	void calc_param(int time,int* forward,signed char* turn,int color);
	void calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T);
	bool isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T);
};

#endif
