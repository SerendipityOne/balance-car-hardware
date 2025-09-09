#include "sr04.h"

extern TIM_HandleTypeDef htim3;
uint16_t count;  // 定时器时间
float distance;  // CM/S

void delay_us(uint32_t udelay) {
  __IO uint32_t Delay = udelay * 72 / 8;  //(SystemCoreClock / 8U / 1000000U)
  //见stm32f1xx_hal_rcc.c -- static void RCC_Delay(uint32_t mdelay)
  do {
    __NOP();
  } while (Delay--);
}

void get_distance(void) {
  // PA3触发
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
  delay_us(10);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET) {  // 上升沿
    __HAL_TIM_SetCounter(&htim3, 0);                          // 定时器清零
    HAL_TIM_Base_Start(&htim3);                               // 开启定时器
  } else {                                                    //下降沿
    HAL_TIM_Base_Stop(&htim3);                                // 关闭定时器
    count = __HAL_TIM_GetCounter(&htim3);
    distance = count * 0.017;
  }
}
