// GaragePhase.cpp

#include "GaragePhase.hpp"
#define TIME_BAND   250
#define TAIL_ANGLE_DRIVE   15

GaragePhase::GaragePhase(std::string name, Balancer* balancer,int setforwardl,int setforwardr,int setending,int gyoffset,int turnoffset,float ikp,float ikd,int itailangle, int setmcntl, int setmcntr, int setstoptime) : Phase(name, balancer)
{
	forwardl=setforwardl;
	forwardr=setforwardr;
	endtime=setending;
	gyrooffset=gyoffset;
	offset=turnoffset;
	Kp = ikp;
	Kd = ikd;
	tailangle=itailangle;
	mcntlval=setmcntl;
	mcntrval=setmcntr;
	stoptime=setstoptime;
}

void GaragePhase::initialize()
{
	fp=fopen("garagephase.csv","w");
  if(fp==NULL){
    printf("failed\n");
    return;
  }
	fprintf(fp,"time,color,turn,gyro,volt,mtL,mtR,flag,mcntl,mcntr\n");
	balancer->change_offset(gyrooffset);
}

void GaragePhase::calc_param(int time,int* forward,signed char* turn,int color){
	int diff_p = std::min(color,LIGHT_WHITE)-(LIGHT_WHITE+LIGHT_BLACK/*+offset*/)/2;
	int diff_d = diff_p-(diff_prev);
	diff_prev=diff_p;
	int val=(Kp*diff_p+diff_d*Kd)/2;
	if(time==0)val=(Kp*diff_p)/2;
	(*turn)=(signed char)val;
	if(*turn<=-2){
		*turn=-2;
	}
	if(*turn>=2){
		*turn=2;
	}
}


void GaragePhase::calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T)
{
	int forward=forwardl+(forwardr-forwardl)*time/endtime;
	signed char turn;
	calc_param(time,&forward,&turn,color);
	*pwm_L = 7;
	*pwm_R = 7;
	if(turn>0)*pwm_R-=turn;
	if(turn<0)*pwm_L+=turn;
	*ang_T = tailangle;
	if(pflag==2){
		*pwm_R=0;
		*pwm_L=0;
	}
	fprintf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",time,color,(int)turn,gyro,volt,(int)*pwm_L,(int)*pwm_R,pflag,mcntl,mcntr);
}

bool GaragePhase::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	int tim = time / 4;

	if (time >= 2500) {
		int idx = tim % TIME_BAND;

		if (time >= 3500 && data[idx] <= boundary) {
			cnt--;
		}
		data[idx] = color;
		if (data[idx] <= boundary) cnt++;
	}
	if(time>=3500 && cnt>210 && pflag==0){
		pflag=1;
		ev3_speaker_play_tone(50, 1000);
	}
	if(time>=6500 && pflag==0){
		int val=0;
		for(int i=0;i<5;i++){
			val+=data[(tim-i+TIME_BAND)%TIME_BAND];
			val-=data[(tim+i+1)%TIME_BAND];
		}
		if(val>=40)pflag=1;
	}
	if(pflag>=1){
		mcntl+=(int)pwm_L;
		mcntr+=(int)pwm_R;
	}
	if(pflag==1 && mcntl>=mcntlval && mcntr>=mcntrval){//Garage：mcntlval=5200, mcntrval=5200
		pflag=2;
		ev3_speaker_play_tone(70, 1000);
	}
	if(pflag==2)tim2++;
	if(tim2>=stoptime)return true;//Garage：stoptime=2000
	return false;
}
