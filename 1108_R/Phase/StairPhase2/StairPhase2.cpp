// StairPhase2.cpp

#include "StairPhase2.hpp"

StairPhase2::StairPhase2(std::string name, Balancer* balancer) : Phase(name, balancer)
{
}

void StairPhase2::initialize()
{
	balancer->change_offset(0);
}

StairPhase2::StairPhase2(std::string name, Balancer* balancer,int setforwardl,int setforwardr,int setending,int gyoffset) : Phase(name, balancer)
{
	forwardl=setforwardl;
	forwardr=setforwardr;
	endtime=setending;
	gyrooffset=gyoffset;
}

void StairPhase2::calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T)
{
	//EV3‚ğ2‰ñ‚É•ª‚¯‚ÄQ‚©‚·
	if(time <= 2000){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 80;

	//’i·‚ÉÚ‹ß
	}else if(time <= 4000){
		*pwm_L = -8;
		*pwm_R = -8;
		*ang_T = 80;

	//K”ö‚Ì‰Ò“­”ÍˆÍŠm•Û
	}else if(time <= 4400){
		*pwm_L = 8;
		*pwm_R = 8;
		*ang_T = 80;

	//EV3‚ğ‚R‰ñ‚É•ª‚¯‚Ä—§‚Ä‚é
	}else if(time <= 6800){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 83;
	}else if(time <= 7800){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 85;

	//’i·‚ğ¸‚é
	}else if(time <= 8000){
		*pwm_L = -20;
		*pwm_R = -20;
		*ang_T = 40+40*((time-7800)/200);
	}else if(time <= 9200){
		*pwm_L = -20;
		*pwm_R = -20;
		*ang_T = 80;
	}else if(time <= 12000){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 80;

	}else if(time <= 15970){
		*pwm_L = 20;
		*pwm_R = -20;
		*ang_T = 80;
	}

}

bool StairPhase2::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	/*I—¹ğŒ‚ğ–‚½‚¹‚Îtrue,–‚½‚³‚È‚¯‚ê‚Îfalse*/
	if (time <= 15970)
		return false;
	else
		return true;
}
