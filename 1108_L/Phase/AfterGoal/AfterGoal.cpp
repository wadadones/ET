// AfterGoal.cpp

#include "AfterGoal.hpp"

#define LIGHT_WHITE 40
#define LIGHT_BLACK  0
#define TAIL_ANGLE_DRIVE      15

AfterGoal::AfterGoal(std::string name, Balancer* balancer) : Phase(name, balancer)
{
}

AfterGoal::AfterGoal(std::string name, Balancer* balancer,int setforwardl,int setforwardr,int setending,int gyoffset,int turnoffset,float ikp,float ikd,int setangle1, int setangle2, int setgraytime) : Phase(name, balancer)
{
	forwardl=setforwardl;
	forwardr=setforwardr;
	endtime=setending;
	gyrooffset=gyoffset;
	offset=turnoffset;
	Kp = ikp;
	Kd = ikd;
	beforeangle=setangle1;
	afterangle=setangle2;
	graytime = setgraytime;
}

void AfterGoal::initialize()
{
	fp=fopen("aftergoal.csv","w");
  if(fp==NULL){
    printf("failed\n");
    return;
  }
	fprintf(fp,"time,color,turn,gyro,volt,mtL,mtR\n");
	balancer->change_offset(gyrooffset);
}

void AfterGoal::calc_param(int time,int* forward,signed char* turn,int color){
	int diff_p = 0;
	if(time <= graytime){
		diff_p = std::min(color,LIGHT_WHITE)-(LIGHT_WHITE+15)/2;
	}else{
		diff_p = std::min(color,LIGHT_WHITE)-(LIGHT_WHITE+0)/2;
	}
	int diff_d = diff_p-(diff_prev);
	diff_prev=diff_p;
	int val=(Kp*diff_p+diff_d*Kd)/2;
	if(time==0)val=(Kp*diff_p)/2;
	(*turn)=(signed char)val;
	(*turn)+=offset;

	if(*turn<-50)
		*turn=-50;
	if(*turn>50)
		*turn=50;

}

void AfterGoal::calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T)
{
	int forward=forwardl+(forwardr-forwardl)*time/endtime;
	signed char turn;
	calc_param(time,&forward,&turn,color);
	balancer->setCommand((signed char)forward, turn);
	balancer->update(gyro, motor_ang_r, motor_ang_l, volt);
	*pwm_L = balancer->getPwmLeft();
	*pwm_R = balancer->getPwmRight();
	*ang_T = beforeangle + (afterangle - beforeangle)*time/endtime;
	fprintf(fp,"%d,%d,%d,%d,%d,%d,%d\n",time,color,(int)turn,gyro,volt,(int)*pwm_L,(int)*pwm_R);
}

bool AfterGoal::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	if (endtime==-1 && sonic<33 && sonic>=0)return true;
	if(endtime>=0 && endtime<=time)return true;
		return false;
}
