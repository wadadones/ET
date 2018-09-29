// StairPhase3.cpp

#include "StairPhase3.hpp"

StairPhase3::StairPhase3(std::string name, Balancer* balancer) : Phase(name, balancer)
{
}

void StairPhase3::initialize()
{
	balancer->change_offset(0);
}

StairPhase3::StairPhase3(std::string name, Balancer* balancer,int setforwardl,int setforwardr,int setending,int gyoffset) : Phase(name, balancer)
{
	forwardl=setforwardl;
	forwardr=setforwardr;
	endtime=setending;
	gyrooffset=gyoffset;
}

void StairPhase3::calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T)
{
	if(time <= 500){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 78;
	}else if(time <= 1500){
		*pwm_L = 8;
		*pwm_R = 8;
		*ang_T = 78;
	}else if(time <= 2000){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 82;
	}else if(time <= 3000){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 82;
	}else if(time<10000){
		*pwm_L = 25;
		*pwm_R = 25;
		*ang_T =78;
	}
}

bool StairPhase3::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	if (time <= 10800)
		return false;
	else
		return true;
}