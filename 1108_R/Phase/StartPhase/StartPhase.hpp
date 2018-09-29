// /*TemplatePhase*/.hpp

#ifndef START_PAHSE
#define START_PHASE

#include "../Phase.hpp"
#include <string>

class StartPhase: public Phase {
public:
	StartPhase(std::string name, Balancer* balancer);
	StartPhase(std::string name, Balancer* balancer,int angle);
	void initialize();
	void calc_param(signed char* forward,signed char* turn,int color);
	void calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T);
	bool isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T);
private:
	int ang;
};

#endif
