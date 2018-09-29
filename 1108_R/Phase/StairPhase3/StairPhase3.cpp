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
	if(time <= 1000){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 78;
	}else if(time <= 2000){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 88;
	}else if(time <= 3000){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 91;
	}else if(time <= 4000){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 94;
	}else if(time <= 5000){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 96;
	}else if(time <= 6000){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 98;
	}else if(time <= 7000){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 100;
	}else if(time <= 30000){
		balancer->setCommand(15, 0);
		balancer->update(gyro, motor_ang_r, motor_ang_l, volt);
		*pwm_L = balancer->getPwmRight();
		*pwm_R = balancer->getPwmLeft();
		*ang_T = 30;
	}

}

bool StairPhase3::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	/*I—¹ğŒ‚ğ–‚½‚¹‚Îtrue,–‚½‚³‚È‚¯‚ê‚Îfalse*/
	if (time <= 30000)
		return false;
	else
		return true;
}
