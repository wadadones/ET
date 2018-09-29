// CurvePhase.cpp

#include "CurvePhase.hpp"

#define LIGHT_WHITE 40
#define LIGHT_BLACK  0
#define TAIL_ANGLE_DRIVE      15

CurvePhase::CurvePhase(std::string name, Balancer* balancer) : Phase(name, balancer)
{
}

CurvePhase::CurvePhase(std::string name, Balancer* balancer,int setforwardl,int setforwardr,int setending,int gyoffset,int turnoffset,float ikp,float ikd) : Phase(name, balancer)
{
	forwardl=setforwardl;
	forwardr=setforwardr;
	endtime=setending;
	gyrooffset=gyoffset;
	offset=turnoffset;
	Kp = ikp;
	Kd = ikd;
}

void CurvePhase::initialize()
{
/*
	char fine_name[] = "";
	strcat(fine_name, name.c_str());
	strcat(fine_name, ".csv");
	fp=fopen(fine_name,"w");
  if(fp==NULL){
    printf("failed\n");
    return;
  }
	fprintf(fp,"time,color,turn,gyro,volt,mtL,mtR\n");
*/
	balancer->change_offset(gyrooffset);
}

void CurvePhase::calc_param(int time,int* forward,signed char* turn,int color){
	int diff_p = std::min(color,LIGHT_WHITE)-(LIGHT_WHITE+LIGHT_BLACK+offset)/2;
	int diff_d = diff_p-(diff_prev);
	diff_prev=diff_p;
	int val=(Kp*diff_p+diff_d*Kd)/2;
	if(time==0)val=(Kp*diff_p)/2;
	(*turn)=(signed char)val;
	if(*turn >= 60)
		*turn = 60;
	if(*turn <= -60)
		*turn = -60;
}

void CurvePhase::calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T)
{
	/*?Z???T?????????????????[?^???o????v?Z????*/
	/*turn = 1??2?l????*/
	int forward=forwardl+(forwardr-forwardl)*time/endtime;
	signed char turn;
	calc_param(time,&forward,&turn,color);
	balancer->setCommand((signed char)forward, turn);
	balancer->update(gyro, motor_ang_r, motor_ang_l, volt);
	*pwm_L = balancer->getPwmLeft();
	*pwm_R = balancer->getPwmRight();
	*ang_T = TAIL_ANGLE_DRIVE;
	//fprintf(fp,"%d,%d,%d,%d,%d,%d,%d\n",time,color,(int)turn,gyro,volt,(int)*pwm_L,(int)*pwm_R);
}

bool CurvePhase::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	if (motor_ang_l > endtime)
		return true;
	else
		return false;
}
