// /*DetectNansho*/.cpp
// setting-> offset: +10, CMD_MAX=60
#include "DetectNansho.hpp"

#define LIGHT_WHITE  40
#define LIGHT_BLACK  0
#define TAIL_ANGLE_DRIVE      3

DetectNansho::DetectNansho(std::string name, Balancer* balancer) : Phase(name, balancer)
{
}

void DetectNansho::initialize()
{
	balancer->change_offset(0);
	fp=fopen("log.csv","w");
  if(fp==NULL){
    printf("failed\n");
    return;
  }
	fprintf(fp,"time,color\n");
	cnt=0;
	for(int i=0;i<100;i++){
		data[i]=0;
	}
}

void DetectNansho::calc_param(signed char* forward,signed char* turn,int color){
	if(color>=(LIGHT_WHITE+LIGHT_BLACK)/2*1.7){
		*turn = 10;
	}else if(color>=(LIGHT_WHITE+LIGHT_BLACK)/2){
		*turn=2;
	}else{
		*turn=-2;
	}
}

void DetectNansho::calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T)
{
	signed char forward;
	signed char turn;
	if(time<500)forward=45;
	else forward=25;
	calc_param(&forward,&turn,color);
	fprintf(fp,"%d,%d,%d,%d\n",time,color,(int)forward,(int)turn);
	balancer->setCommand(forward, turn);
	balancer->update(gyro, motor_ang_r, motor_ang_l, volt);
	*pwm_L = balancer->getPwmRight();
	*pwm_R = balancer->getPwmLeft();
	*ang_T = 80;
}

bool DetectNansho::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	int Graymin=17;
	int Graymax=27;
	int tim=time/4;
	if(tim>=1000){
			if(tim>=1100){
					cnt-=(data[tim%100]>=Graymin && data[tim%100]<=Graymax)?1:0;
			}
			data[tim%100]=color;
			cnt+=(data[tim%100]>=Graymin && data[tim%100]<=Graymax)?1:0;
			if(tim>=1100 && cnt>=50){
					return true;
			}
	}
	return false;
}
