// ImmediatePhase.cpp

#include "ImmediatePhase.hpp"

ImmediatePhase::ImmediatePhase(std::string name, Balancer* balancer) : Phase(name, balancer)
{
	/*�R���X�g���N�^*/;
}

ImmediatePhase::ImmediatePhase(std::string name, Balancer* balancer, int setforward, int settime, int setangle) : Phase(name, balancer)
{
	forward = setforward;
	endtime = settime;
	angle = setangle;

}

void ImmediatePhase::initialize()
{
	/*��������*/;
}

void ImmediatePhase::calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T)
{
	/*�Z���T�����̓��͂����ƂɃ��[�^�ւ̏o�͂��v�Z����*/
	*pwm_L = forward;
	*pwm_R = forward;
	*ang_T = angle;
}

bool ImmediatePhase::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	/*�I�������𖞂�����true,�������Ȃ�����false*/
	if(time <= endtime)
		return false;
	else
		return true;
}
