#include "motor.h"

extern TIM_HandleTypeDef htim1;

int abs(int a) {
  if (a > 0)
    return a;
  else
    return -a;
}

/**
 * @param motor1: AIN的速度 (-7200~7200)
 * @param motor2: BIN的速度 (-7200~7200)
 * 
 */
void motor_load(int motor1, int motor2) {
  if (motor1 < 0) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
  }
  // 计算PWM占空比
  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, abs(motor1));

  if (motor2 < 0) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
  }
  // 计算PWM占空比
  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, abs(motor2));
}

void limit_motor(int *motor1, int *motor2){
  if(*motor1 > PWM_MAX) *motor1 = PWM_MAX;
  if(*motor1 < PWM_MIN) *motor1 = PWM_MIN;
  if(*motor2 > PWM_MAX) *motor2 = PWM_MAX;
  if(*motor2 < PWM_MIN) *motor2 = PWM_MIN;
}
