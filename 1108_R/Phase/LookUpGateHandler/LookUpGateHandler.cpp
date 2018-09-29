#include "LookUpGateHandler.hpp"

#define TAIL_ANGLE_STAND_UP 93
#define TAIL_ANGLE_DRIVE 15
#define TAIL_ANGLE_LUG 70
#define MOTOR_FORWARD 7
#define MOTOR_STOP 0
#define MOTOR_FORWARD_SLOW 2
#define MOTOR_BACKWARD_SLOW -2
#define TIME_SECTION 5175
#define LINE_TRACE 4
#define LIGHT_WHITE 8
#define LIGHT_BLACK 0
#define MUSIC_DURATION 500
#define MUSIC_ELEMENT 16

std::array<int, 9> tail_down{93, 90, 87, 84, 81, 78, 75, 72, 70};
std::array<int, 6> tail_up{70, 75, 80, 85, 89, 92};

double tone_array[MUSIC_ELEMENT] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_C4};

LookUpGateHandler::LookUpGateHandler(std::string name, Balancer* balancer) : Phase(name, balancer)
{

}

void LookUpGateHandler::initialize()
{

}
//修正前 ~1：前進小, ~2.0：前進大, ~3.0：回転, ~5.0：前進, ~6.0：回転, ~8.0：前進
void LookUpGateHandler::calculate(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char* pwm_L, signed char* pwm_R, signed int* ang_T)
{
	if(time < 0.2 * TIME_SECTION){
		*pwm_L = MOTOR_FORWARD + 3;
		*pwm_R = MOTOR_FORWARD + 3;
		//*ang_T = tail_down[time / (TIME_SECTION / DIVISION)];
	}else if(time < 1 * TIME_SECTION){
		*pwm_L = MOTOR_FORWARD_SLOW;
		*pwm_R = MOTOR_FORWARD_SLOW;
		*ang_T = tail_down[time / (TIME_SECTION / tail_down.size())]; //DIVISION
	}else if(time < 20*TIME_SECTION/10){
		*pwm_L = MOTOR_FORWARD;
		*pwm_R = MOTOR_FORWARD;
		if(color > 2 * (LIGHT_WHITE + LIGHT_BLACK) / 3){
			*pwm_R = *pwm_R - LINE_TRACE;
		}else if(color < 1 * (LIGHT_WHITE + LIGHT_BLACK) / 3){
			*pwm_L = *pwm_L - LINE_TRACE;
		}
		*ang_T = TAIL_ANGLE_LUG;
	}else if(time < 30 * TIME_SECTION/10 + 50){
		*pwm_L = 6;
		*pwm_R = -6;
		*ang_T = TAIL_ANGLE_LUG;
	}else if(time < 47 * TIME_SECTION/10){
		*pwm_L = MOTOR_FORWARD;
		*pwm_R = MOTOR_FORWARD;
		if(color > 2 * (LIGHT_WHITE + LIGHT_BLACK) / 3){
			*pwm_L = *pwm_L - LINE_TRACE;
		}else if(color < 1 * (LIGHT_WHITE + LIGHT_BLACK) / 3){
			*pwm_R = *pwm_R - LINE_TRACE;
		}
		*ang_T = TAIL_ANGLE_LUG;
	}else if(time < 57 * TIME_SECTION/10 - 250){
		*pwm_L = 6;
		*pwm_R = -6;
		*ang_T = TAIL_ANGLE_LUG;
	}else if(time < 72 * TIME_SECTION/10){
		*pwm_L = MOTOR_FORWARD;
		*pwm_R = MOTOR_FORWARD;
		if(color > 2 * (LIGHT_WHITE + LIGHT_BLACK) / 3){
			*pwm_R = *pwm_R - LINE_TRACE;
		}else if(color < 1 * (LIGHT_WHITE + LIGHT_BLACK) / 3){
			*pwm_L = *pwm_L - LINE_TRACE;
		}
		*ang_T = TAIL_ANGLE_LUG;
	}else{
		*pwm_L = MOTOR_BACKWARD_SLOW;
		*pwm_R = MOTOR_BACKWARD_SLOW;
		*ang_T = tail_up[(time - 72 * TIME_SECTION/10) / (TIME_SECTION / tail_up.size())]; // DIVISION
	}
	//if(time % MUSIC_DURATION == 0) ev3_speaker_play_tone(tone_array[(time / MUSIC_DURATION) % MUSIC_ELEMENT], MUSIC_DURATION);
}

bool LookUpGateHandler::isFinished(int time, int32_t motor_ang_l, int32_t motor_ang_r, int color, int gyro, int sonic, int volt, signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	if(time < 82 * TIME_SECTION/10) return false;
	else return true;
}
