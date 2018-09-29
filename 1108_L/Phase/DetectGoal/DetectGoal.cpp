// /*DetectGoal*/.cpp
// setting-> offset: +10, CMD_MAX=60

#include "DetectGoal.hpp"

#define LIGHT_WHITE  40
#define LIGHT_BLACK  0
#define TAIL_ANGLE_DRIVE   3
#define TIME_BAND   36

DetectGoal::DetectGoal(std::string name, Balancer* balancer) : Phase(name, balancer)
{
}

DetectGoal::DetectGoal(std::string name, Balancer* balancer,int setforwardl,int setforwardr,int maxspeedtime,int gyoffset) : Phase(name, balancer)
{
	forwardl=setforwardl;
	forwardr=setforwardr;
	mxsptime=maxspeedtime;
	gyrooffset=gyoffset;
}

void DetectGoal::initialize()
{
	balancer->change_offset(0);
	fp=fopen("detectgoallog.csv","w");
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

void DetectGoal::calc_param(int time,int* forward,signed char* turn,int color){
	const float Kp = 1.1;
	const float Kd = 10.00;
	int diff_p = std::min(color,LIGHT_WHITE)-(LIGHT_WHITE+LIGHT_BLACK)/2;
	int diff_d = diff_p-(diff_prev);
	diff_prev=diff_p;
	int val=(Kp*diff_p+diff_d*Kd)/2;
	if (time == 0) val = (Kp * diff_p) / 2;
	(*turn)=(signed char)val;
	if(*turn<-50)
		*turn=-50;
	if(*turn>50)
		*turn=50;
}

void DetectGoal::calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T)
{
	int forward=forwardl+(forwardr-forwardl)*std::min(time,mxsptime)/mxsptime;
	signed char turn;
	calc_param(time,&forward,&turn,color);
	balancer->setCommand((signed char)forward, turn);
	balancer->update(gyro, motor_ang_r, motor_ang_l, volt);
	*pwm_L = balancer->getPwmLeft();
	*pwm_R = balancer->getPwmRight();
	*ang_T = TAIL_ANGLE_DRIVE;
	//fprintf(fp,"%d,%d\n",time,color);
}

bool DetectGoal::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	int tim=time/4;
	data[tim%TIME_BAND]=color;
	if(time>=3000){
		int diff1=0;
		int diff2=0;
		for(int i=0;i<TIME_BAND/3;i++){
			diff1+=data[(tim-i+TIME_BAND)%TIME_BAND];
			diff2+=data[(tim+i+1)%TIME_BAND];
		}
		if(diff1-diff2>=(TIME_BAND/3)*10) return true;
	}
//	if(time>=10000)return true;
	return false;
}
