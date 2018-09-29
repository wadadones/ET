// StraightPhase.cpp

#include "StraightPhase.hpp"

#define LIGHT_WHITE  40
/* ???F????Z???T?l */
#define LIGHT_BLACK  0
/* ?o?????X???s????p?x[?x] */
#define TAIL_ANGLE_DRIVE      15

StraightPhase::StraightPhase(std::string name, Balancer* balancer) : Phase(name, balancer)
{
}

StraightPhase::StraightPhase(std::string name, Balancer* balancer,int setforwardl,int setforwardr,int setending,int gyoffset) : Phase(name, balancer)
{
	forwardl=setforwardl;
	forwardr=setforwardr;
	endtime=setending;
	gyrooffset=gyoffset;
}

void StraightPhase::initialize()
{
	fp=fopen("straightlog.csv","w");
  if(fp==NULL){
    printf("failed\n");
    return;
  }
	fprintf(fp,"time,color,turn,gyro,volt,mtL,mtR\n");

	balancer->change_offset(gyrooffset);
	for(int i = 0; i < 50; i++){
		pwm_L_list[i] = 0;
		pwm_R_list[i] = 0;
	}
}

void StraightPhase::calc_param(int time,int* forward,signed char* turn,int color){
	const float Kp = 1.1;
	const float Kd = 10.00;
	int diff_p = std::min(color,LIGHT_WHITE)-(LIGHT_WHITE+LIGHT_BLACK)/2;
	/*
	if(time>=200){
		int va=0;
		for(int i=0;i<4;i++){
			va+=colordi[i];
		}
		va/=50;
		colordi[(time/4)%50]=diff_p;
		diff_p=va;
	}
	*/
	int diff_d = diff_p-(diff_prev);
	diff_prev=diff_p;
	int val=(Kp*diff_p+diff_d*Kd)/2;
	if (time == 0) val = (Kp * diff_p) / 2;
	(*turn)=(signed char)val;
	if(*turn >= 50)
		*turn = 50;
	if(*turn <= -50)
		*turn = -50;
}

void StraightPhase::calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T)
{
	int forward=forwardl+(forwardr-forwardl)*motor_ang_l/endtime;
	signed char turn;
	calc_param(time,&forward,&turn,color);
	balancer->setCommand((signed char)forward, turn);
	balancer->update(gyro, motor_ang_r, motor_ang_l, volt);
	*pwm_L = balancer->getPwmLeft();
	*pwm_R = balancer->getPwmRight();
	*ang_T = TAIL_ANGLE_DRIVE;
	fprintf(fp,"%d,%d,%d,%d,%d,%d,%d\n",time,color,(int)turn,gyro,volt, (int)motor_ang_l,(int)motor_ang_r);
}

bool StraightPhase::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	pwm_L_list[(time/4)%20] = pwm_L;
	pwm_R_list[(time/4)%20] = pwm_R;
	int counts = 0;
	for(int i = 0; i < 20; i++){
		if(pwm_L_list[i] - pwm_R_list[i] >= 20)
			counts++;
	}

	// if (time > endtime){
	// 	return true;
	// }else if(time >= 3000 && counts >= 19){
	// 	return true;
	// }else {
	// 	return false;
	// }

	if (motor_ang_l > endtime){
		return true;
	} else {
		return false;
	}
}
