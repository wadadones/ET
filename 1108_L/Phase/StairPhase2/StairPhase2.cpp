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
	//EV3��2���ɕ����ĐQ����
	if(time <= 2000){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 80;

	//�i���ɐڋ�
	}else if(time <= 4000){
		*pwm_L = -8;
		*pwm_R = -8;
		*ang_T = 80;

	//�K���̉ғ��͈͊m��
	}else if(time <= 4400){
		*pwm_L = 8;
		*pwm_R = 8;
		*ang_T = 80;

	//EV3���R���ɕ����ė��Ă�
	}else if(time <= 6800){
		*pwm_L = 0;
		*pwm_R = 0;
		*ang_T = 83;
	}else if(time <= 7800){
		*pwm_L = 0;
		*pwm_R = 0;
		if(volt >= 8600){
			*ang_T = 82;
		}else if(volt >= 8400){
			*ang_T = 84;
		}else {
			*ang_T = 85;
		}

	//�i��������
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
	/*�I�������𖞂�����true,�������Ȃ�����false*/
	if (time <= 15970)
		return false;
	else
		return true;
}
