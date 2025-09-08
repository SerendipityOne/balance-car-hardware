#include "encoder.h"

// 读取速度
int read_speed(TIM_HandleTypeDef* htim) {
  int speed = 0;
  speed = (short)__HAL_TIM_GetCounter(htim);  // 获取当前计数值
  /*这里用short类型来存储计数值，因为计数值为0~65535，速度有正有负，所以用short类型-32768~32767来存储*/
  __HAL_TIM_SetCounter(htim, 0);  // 归零计数器
  return speed;
}
