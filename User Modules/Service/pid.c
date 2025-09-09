#include "pid.h"

VerticalParams vertical_params;  // 直立环控制参数
VelocityParams velocity_params;  // 速度环控制参数
TurnParams turn_params;          // 转向环控制参数
uint8_t stop;                    // 停止标志位

// 直立环PD控制器
// 输入：期望角度、真实角度、角速度
// 一个典型的PD控制器，用于保持系统直立
int vertical_pid(VerticalPID pid) {
	// kp*(角度误差) + kd*角速度
  return vertical_params.kp * (pid.angle - pid.med) + vertical_params.kd * pid.gyro_y;
}

// 速度环PI控制器
// 输入:期望速度、左编码器、右编码器
int vertical_speed_pid(VerticalSpeedPID pid) {
  static int err_lowout_last, encoder_s;
  static float a = 0.7;
  // 计算误差
  int err, err_lowout;
  err = pid.encoder_data.encoder_left + pid.encoder_data.encoder_right - pid.target;
  // 低通滤波
  err_lowout = (1 - a) * err + err_lowout_last;
  err_lowout_last = err_lowout;
  // 计算积分
  encoder_s += err_lowout;
  // 积分限幅（-20000~20000）
  encoder_s = encoder_s > 20000 ? 20000 : (encoder_s < -20000 ? -20000 : encoder_s);
  if (stop == 1) encoder_s = 0, stop = 0;
	// kp*滤波后误差 + ki*积分项
  return velocity_params.kp * err_lowout + velocity_params.ki * encoder_s;
}

//转向环PD控制器
//输入：角速度、角度值
int turn(TurnPID pid) {
	// kp*目标角度 + kd*角速度
  return turn_params.kp * pid.target + turn_params.kd * pid.gyro_z;
}
