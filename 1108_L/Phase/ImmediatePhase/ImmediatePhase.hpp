// ImmediatePhase.hpp

#ifndef IMMEDIATE_PHASE_H
#define IMMEDIATE_PHASE_H

#include "../Phase.hpp"
#include <string>

class ImmediatePhase: public Phase {
public:
	int forward;
	int endtime;
	int angle;
	ImmediatePhase(std::string name, Balancer* balancer);
	ImmediatePhase(std::string name, Balancer* balancer, int setforward, int settime, int setangle);

	void initialize();
	void calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T);
	bool isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T);
};

#endif
