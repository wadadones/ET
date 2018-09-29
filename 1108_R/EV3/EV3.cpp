// EV3.cpp

#include "EV3.hpp"

/*?Z???T?[?????????`?????*/
static const sensor_port_t
	touch_sensor    = EV3_PORT_1,
	sonar_sensor    = EV3_PORT_2,
	color_sensor    = EV3_PORT_3,
	gyro_sensor     = EV3_PORT_4;

/*???[?^?????????`?????*/
static const motor_port_t
	left_motor      = EV3_PORT_C,
	right_motor     = EV3_PORT_B,
	tail_motor      = EV3_PORT_A;

/* LCD?t?H???g?T?C?Y */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

/* ???S???~????p?x[?x] */
#define TAIL_ANGLE_STAND_UP  98
/* ???S???~?p???[?^?????????W?? */
#define P_GAIN             2.5F
/* ???S???~?p???[?^????PWM???????l */
#define PWM_ABS_MAX          60

/* ?g?[??????? */
#define TONE_F              500
/* ?g?[??????? */
#define TONE_T             1000

/* Bluetooth?t?@?C???n???h?? */
static FILE     *bt = NULL;
/* Bluetooth?R?}???h 1:?????[?g?X?^?[?g */
static int      bt_cmd = 0;

void EV3::setUpEV3()
{
	/* ?Z???T?[????|?[?g???? */
	ev3_sensor_config(sonar_sensor, ULTRASONIC_SENSOR);
	ev3_sensor_config(color_sensor, COLOR_SENSOR);
	ev3_color_sensor_get_reflect(color_sensor); /* ????????[?h */
	ev3_sensor_config(touch_sensor, TOUCH_SENSOR);
	ev3_sensor_config(gyro_sensor, GYRO_SENSOR);

	/* ???[?^?[?o??|?[?g???? */
	ev3_motor_config(left_motor, LARGE_MOTOR);
	ev3_motor_config(right_motor, LARGE_MOTOR);
	ev3_motor_config(tail_motor, LARGE_MOTOR);
	ev3_motor_set_power(tail_motor, -30);
	tslp_tsk(1000);
	ev3_motor_reset_counts(tail_motor);

	/* LCD????\?? */
	ev3_lcd_fill_rect(0, 0, EV3_LCD_WIDTH, EV3_LCD_HEIGHT, EV3_LCD_WHITE);
	int mv = ev3_battery_voltage_mV();
	if(mv >= 9000){
		ev3_lcd_draw_string("over 9000", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 8900){
		ev3_lcd_draw_string("over 8900", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 8800){
		ev3_lcd_draw_string("over 8800", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 8700){
		ev3_lcd_draw_string("over 8700", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 8600){
		ev3_lcd_draw_string("over 8600", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 8500){
		ev3_lcd_draw_string("over 8500", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 8400){
		ev3_lcd_draw_string("over 8400", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 8300){
		ev3_lcd_draw_string("over 8300", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 8200){
		ev3_lcd_draw_string("over 8200", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 8100){
		ev3_lcd_draw_string("over 8100", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 8000){
		ev3_lcd_draw_string("over 8000", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 7900){
		ev3_lcd_draw_string("over 7900", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 7800){
		ev3_lcd_draw_string("over 7800", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 7700){
		ev3_lcd_draw_string("over 7700", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 7600){
		ev3_lcd_draw_string("over 7600", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 7500){
		ev3_lcd_draw_string("over 7500", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 7400){
		ev3_lcd_draw_string("over 7400", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 7300){
		ev3_lcd_draw_string("over 7300", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 7200){
		ev3_lcd_draw_string("over 7200", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 7100){
		ev3_lcd_draw_string("over 7100", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 7000){
		ev3_lcd_draw_string("over 7000", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 6900){
		ev3_lcd_draw_string("over 6900", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 6800){
		ev3_lcd_draw_string("over 6800", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 6700){
		ev3_lcd_draw_string("over 6700", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 6600){
		ev3_lcd_draw_string("over 6600", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 6500){
		ev3_lcd_draw_string("over 6500", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 6400){
		ev3_lcd_draw_string("over 6400", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 6300){
		ev3_lcd_draw_string("over 6300", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 6200){
		ev3_lcd_draw_string("over 6200", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 6100){
		ev3_lcd_draw_string("over 6100", 0, CALIB_FONT_HEIGHT*1);
	}else if(mv >= 6000){
		ev3_lcd_draw_string("over 6000", 0, CALIB_FONT_HEIGHT*1);
	} else {
		ev3_lcd_draw_string("under 6000", 0, CALIB_FONT_HEIGHT*1);
	}

	/* Open Bluetooth file */
	bt = ev3_serial_open_file(EV3_SERIAL_BT);
	assert(bt != NULL);

	/* Bluetooth??M?^?X?N??N?? */
	act_tsk(BT_TASK);

	/* ????????????m */
	ev3_led_set_color(LED_ORANGE);
}

void EV3::waitForStart()
{
	/* ?X?^?[?g??@ */
	int i = TAIL_ANGLE_STAND_UP;
	//int flag = 0;
	while(1){
		ev3_tail_set_angle(i); /* ???S???~?p?p?x????? */

		if(ev3_button_is_pressed(UP_BUTTON)){
			i--;
			while(1){
				if(!ev3_button_is_pressed(UP_BUTTON)) break;
			}
		}
		if(ev3_button_is_pressed(DOWN_BUTTON)){
			i++;
			while(1){
				if(!ev3_button_is_pressed(DOWN_BUTTON)) break;
			}
		}

		if (bt_cmd == 1){
			break; /* ?????[?g?X?^?[?g */
		}

		if (ev3_touch_sensor_is_pressed(touch_sensor) == 1){
			break; /* ?^?b?`?Z???T???????? */
		}

		tslp_tsk(10); /* 10msec?E?F?C?g */
	}

	/* ?X?^?[?g??m */
	ev3_led_set_color(LED_GREEN);
}

void EV3::resetSensorValue()
{
	/* ???s???[?^?[?G???R?[?_?[???Z?b?g */
	ev3_motor_reset_counts(left_motor);
	ev3_motor_reset_counts(right_motor);

	/* ?W???C???Z???T?[???Z?b?g */
	ev3_gyro_sensor_reset(gyro_sensor);
}

void EV3::playTone()
{
	ev3_speaker_play_tone(TONE_F, TONE_T);
}

void EV3::getSensorValue(int32_t* motor_ang_l, int32_t* motor_ang_r, int* color, int* gyro, int* sonic, int *volt)
{
	*motor_ang_l = ev3_motor_get_counts(left_motor);
	*motor_ang_r = ev3_motor_get_counts(right_motor);
	*color = ev3_color_sensor_get_reflect(color_sensor);
	*gyro = ev3_gyro_sensor_get_rate(gyro_sensor);
	*sonic = ev3_ultrasonic_sensor_get_distance(sonar_sensor);
	*volt = ev3_battery_voltage_mV();
}

void EV3::setMotorValue(signed char pwm_L, signed char pwm_R, signed int ang_T)
{
	if (pwm_L == 0){
		ev3_motor_stop(left_motor, true);
	}else{
		ev3_motor_set_power(left_motor, (int)pwm_L);
	}
	if (pwm_R == 0){
		ev3_motor_stop(right_motor, true);
	}else{
		ev3_motor_set_power(right_motor, (int)pwm_R);
	}
	ev3_tail_set_angle(ang_T);
}

void EV3::sleep(int sleep_sec)
{
	tslp_tsk(sleep_sec);
}

bool EV3::buttonIsPressed()
{
	return ev3_button_is_pressed(BACK_BUTTON);
}

void EV3::shutDownEV3()
{
	ev3_motor_stop(left_motor, false);
	ev3_motor_stop(right_motor, false);

	ter_tsk(BT_TASK);
	fclose(bt);
}

void EV3::ev3_tail_set_angle(signed int angle)
{
	/* ?????? */
	float pwm = (float)(angle - ev3_motor_get_counts(tail_motor))*P_GAIN;
	/* PWM?o??O?a???? */
	if (pwm > PWM_ABS_MAX){
		pwm = PWM_ABS_MAX;
	}
	else if (pwm < -PWM_ABS_MAX){
		pwm = -PWM_ABS_MAX;
	}

	if (pwm == 0){
		ev3_motor_stop(tail_motor, true);
	}
	else{
		ev3_motor_set_power(tail_motor, (signed char)pwm);
	}
}

FILE* EV3::getBT()
{
	return bt;
}

void EV3::setBTcmd(int cmd)
{
	bt_cmd = cmd;
}