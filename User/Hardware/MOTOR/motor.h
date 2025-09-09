#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "stm32f1xx_hal.h"

#define PWM_MAX 7200
#define PWM_MIN -7200


void motor_load(int motor1, int motor2);
void limit_motor(int *motor1, int *motor2);

#endif /* __MOTOR_H__ */
