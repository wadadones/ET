// TightCurve.cpp

#include "TightCurve.hpp"

#define LIGHT_WHITE  40
/* 黒色の光センサ値 */
#define LIGHT_BLACK  0
/* バランス走行時の角度[度] */
#define TAIL_ANGLE_DRIVE      3

TightCurve::TightCurve(std::string name, Balancer* balancer) : Phase(name, balancer)
{
}

void TightCurve::initialize()
{
	fp=fopen("tightcurvelog.csv","w");
  if(fp==NULL){
    printf("failed\n");
    return;
  }
	fprintf(fp,"time,color,turn,gyro,volt,mtL,mtR\n");
	balancer->change_offset(gyrooffset);
}

TightCurve::TightCurve(std::string name, Balancer* balancer,int setforwardl,int setforwardr,int setending,int gyoffset) : Phase(name, balancer)
{
	forwardl=setforwardl;
	forwardr=setforwardr;
	endtime=setending;
	gyrooffset=gyoffset;
}

void TightCurve::calc_param(int time,int* forward,signed char* turn,int color){
	const float Kp = 1.13;
	const float Kd = 10.00;
	int offset=-2;
	int diff_p = std::min(color,LIGHT_WHITE)-(LIGHT_WHITE+LIGHT_BLACK)/2;
	int diff_d = diff_p-(diff_prev);
	diff_prev=diff_p;
	int val=(Kp*diff_p+diff_d*Kd)/2;
	if(time==0)val=(Kp*diff_p)/2;
	(*turn)=(signed char)val;
	(*turn)+=offset;
	(*turn)*=-1;
	if(*turn<-12){
		*turn=-12;
	}
	if(*turn>12){
		*turn=12;
	}
}

void TightCurve::calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T)
{
	/*センサからの入力をもとにモータへの出力を計算する*/
	/*turn = 1の2値制御*/
	int forward=forwardl+(forwardr-forwardl)*time/endtime;
	signed char turn;
	calc_param(time,&forward,&turn,color);
	balancer->setCommand((signed char)forward, turn);
	balancer->update(gyro, motor_ang_r, motor_ang_l, volt);
	*pwm_L = balancer->getPwmRight();
	*pwm_R = balancer->getPwmLeft();
	*ang_T = TAIL_ANGLE_DRIVE;
	fprintf(fp,"%d,%d,%d,%d,%d,%d,%d\n",time,color,(int)turn,gyro,volt,(int)*pwm_L,(int)*pwm_R);
}

bool TightCurve::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	/*終了条件を満たせばtrue,満たさなければfalse*/
	if (time <= endtime)
		return false;
	else
		return true;
}
