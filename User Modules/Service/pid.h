#ifndef __PID_H__
#define __PID_H__

#include "encoder.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
#include "stm32f1xx_hal.h"
#include "motor.h"

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

typedef struct VelocityPID {
  int target;
  Encoder encoder_data;
} VelocityPID;

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
} TurnParams;

int vertical_pid(VerticalPID pid);
int velocity_pid(VelocityPID pid);
int turn(TurnPID pid);
void control(void);

#endif  // !__PID_H__
