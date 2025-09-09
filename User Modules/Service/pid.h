#ifndef __PID_H__
#define __PID_H__

#include "encoder.h"
#include "stm32f1xx_hal.h"

// PID 控制器参数结构体
typedef struct VerticalPID {
  float med;     // 期望角度
  float angle;   // 真实角度
  float gyro_y;  // 角速度
} VerticalPID;

typedef struct VerticalParams {
  float kp;  // 比例增益
  float kd;  // 微分增益
} VerticalParams;

typedef struct VerticalSpeedPID {
  int target;
  Encoder encoder_data;
} VerticalSpeedPID;

typedef struct VelocityParams {
  float kp;  // 比例增益
  float ki;  // 积分增益
} VelocityParams;

typedef struct TurnPID {
  float gyro_z;  // 角速度
  int target;    // 目标角度
} TurnPID;

typedef struct TurnParams {
  float kp;  // 比例增益
  float kd;  // 微分增益
}TurnParams;

#endif  // !__PID_H__
