// Operator.cpp

#include "Operator.hpp"

//�J�E���g�A�b�v����
#define COUNT_TIME 4
//�^�X�N���~����
#define SLEEP_TIME 3

//�R���X�g���N�^
Operator::Operator(EV3* ev3, Balancer* balancer, Schedule* schedule)
{
	this->ev3 = ev3;
	this->balancer = balancer;
	this->schedule = schedule;
}

void Operator::run()
{
	//���s���t�F�[�Y�̃|�C���^
	Phase* currentPhase;
	//�e�t�F�[�Y�̌o�ߎ���
	int time;
	//�Z���T�����̓���
	int32_t motor_ang_l;
	int32_t motor_ang_r;
	int color;
	int gyro;
	int sonic;
	int volt;
	//���[�^�ւ̏o��
	signed char pwm_L;
	signed char pwm_R;
	signed int ang_T;

	//EV3�̐ݒ�
	ev3->setUpEV3();
	//�X�^�[�g�w���҂�
	ev3->waitForStart();
	//�Z���T�̃��Z�b�g
	ev3->resetSensorValue();
	//�|�����s���C�u�����̏�����
	balancer->init();

	while(schedule->isEmpty()){
		//���̃t�F�[�Y�������o��
		currentPhase = schedule->popPhase();
		//�t�F�[�Y�̏�������
		currentPhase->initialize();
		//�^�C�}�[�̃��Z�b�g
		time = 0;
		//�X�^�[�g�ʒm
		ev3->playTone();

		do{
			//�Z���T�������͂��Ⴄ
			ev3->getSensorValue(&motor_ang_l, &motor_ang_r, &color, &gyro, &sonic, &volt);
			//���͒l�����o�͒l���t�F�[�Y���Ƃ̕��@�ŎZ�o
			currentPhase->calculate(time, motor_ang_l, motor_ang_r, color, gyro, sonic, volt, &pwm_L, &pwm_R, &ang_T);
			//���[�^�ɏo�͂��n��
			ev3->setMotorValue(pwm_L, pwm_R, ang_T);
			//���₷��
			ev3->sleep(SLEEP_TIME);
			//�^�C�}�[�̃C���N�������g
			time += COUNT_TIME;
			//�����̃{�^���ŏI��
			if(ev3->buttonIsPressed()) break;
		}while(!currentPhase->isFinished(time, motor_ang_l, motor_ang_r, color, gyro, sonic, volt, pwm_L, pwm_R, ang_T));

		//�����̃{�^����ry
		if(ev3->buttonIsPressed()) break;
	}

	//�I���ʒm
	ev3->playTone();
	//EV3�̏I������
	ev3->shutDownEV3();

	return;
}
