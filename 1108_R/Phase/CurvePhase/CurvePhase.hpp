// StraightPhase.hpp

#ifndef CURVE_PHASE_H
#define CURVE_PHASE_H

#include "../Phase.hpp"
#include <string>

class CurvePhase: public Phase {
public:
	int diff_prev=20;
	int forwardl=60;
	int forwardr=60;
	int gyrooffset=0;
	int offset=0;
	int endtime=5000;
	float Kp = 1.5;
	float Kd = 12.00;
	//FILE *fp;
	CurvePhase(std::string name, Balancer* balancer);
	CurvePhase(std::string name, Balancer* balancer,int setforwardl,int setforwardr,int setending,int gyoffset,int turnoffset,float ikp,float ikd);
	void initialize();
	void calc_param(int time,int* forward,signed char* turn,int color);
	void calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T);
	bool isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T);
};

#endif
