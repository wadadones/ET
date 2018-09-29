// /*TemplatePhase*/.cpp

#include "StartPhase.hpp"
#define LIGHT_WHITE  40
#define LIGHT_BLACK  0
StartPhase::StartPhase(std::string name, Balancer* balancer) : Phase(name, balancer)
{
}

StartPhase::StartPhase(std::string name, Balancer* balancer,int angle) : Phase(name, balancer)
{
	ang=angle;
}

void StartPhase::initialize()
{
	balancer->change_offset(0);
}

void StartPhase::calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T)
{

	*pwm_L = 0;
	*pwm_R = 0;
	*ang_T = ang;

}

bool StartPhase::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	/*?I??????? ?????true,?????????????false*/
	if(time <= 200)
		return false;
	else
		return true;
}
