// BeforeStair.hpp

#ifndef BEFORE_STAIR_H
#define BEFORE_STAIR_H

#include "../Phase.hpp"
#include <string>

class BeforeStair: public Phase {
public:

	int angle;

	FILE *fp;
	BeforeStair(std::string name, Balancer* balancer);
	BeforeStair(std::string name, Balancer* balancer,int tailangle);
	void initialize();
	void calc_param(int time,int* forward,signed char* turn,int color);
	void calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T);
	bool isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T);
};

#endif
