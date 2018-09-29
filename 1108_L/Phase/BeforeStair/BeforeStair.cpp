// BeforeStair.cpp

#include "BeforeStair.hpp"



#define LIGHT_WHITE 25
#define LIGHT_BLACK 0
#define TURN_MAX 7


BeforeStair::BeforeStair(std::string name, Balancer* balancer) : Phase(name, balancer)
{
	/*�R���X�g���N�^*/;
}

BeforeStair::BeforeStair(std::string name, Balancer* balancer, int tailangle) : Phase(name, balancer)
{

	angle = tailangle;
}




void BeforeStair::initialize()
{
	/*��������*/
	fp = fopen("BeforeStair.csv", "w");
	if (fp == NULL) {
		printf("failed\n");
		return;
	}
	fprintf(fp, "time,color,mtL,mtR\n");
}


void BeforeStair::calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T)
{
		//�ҋ@
	if (time <= 3000) {
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = angle;
		//���]���Č��������ɂȂ�
	} else if (time <= (5125 + 3000)) {
		*pwm_L = 6;
		*pwm_R = -6;
		*ang_T = angle;
	} else if (time <= (5125 + 5000)) {
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = angle;



	}
	fprintf(fp, "%d,%d,%d,%d\n", time, color, (int)*pwm_L, (int)*pwm_R);

}

bool BeforeStair::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	/*�I�������𖞂�����true,�������Ȃ�����false*/
	if (12000 >= time)//17000
		return false;
	else
		return true;
}
