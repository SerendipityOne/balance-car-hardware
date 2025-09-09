#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f1xx_hal.h"

typedef struct Encoder {
  int encoder_left, encoder_right;  // 编码器数据
} Encoder;


int read_speed(TIM_HandleTypeDef* htim);



#endif // !__ENCODER_H
