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
	//EV3を2回に分けて寝かす
	if(time <= 2000){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 80;

	//段差に接近
	}else if(time <= 4000){
		*pwm_L = -8;
		*pwm_R = -8;
		*ang_T = 80;

	//尻尾の稼働範囲確保
	}else if(time <= 4400){
		*pwm_L = 8;
		*pwm_R = 8;
		*ang_T = 80;

	//EV3を３回に分けて立てる
	}else if(time <= 6800){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 83;
	}else if(time <= 7800){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 85;

	//段差を昇る
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
	/*終了条件を満たせばtrue,満たさなければfalse*/
	if (time <= 15970)
		return false;
	else
		return true;
}
