#include "pid.h"

// 闭环控制中间变量
int vertical_out, velocity_out, turn_out, target_turn;
int motor1, motor2;
float med_angle;  // 平衡时角度值偏移量

VelocityPID velocity_pid_data;   // 速度环PID控制器数据
VerticalPID vertical_pid_data;   // 直立环PID控制器数据
TurnPID turn_pid_data;           // 转向环PID控制器数据
MPU mpu_data;                    // MPU6050数据
VerticalParams vertical_params;  // 直立环控制参数
VelocityParams velocity_params;  // 速度环控制参数
TurnParams turn_params;          // 转向环控制参数
uint8_t stop;                    // 停止标志位

extern TIM_HandleTypeDef htim2, htim4;

// 直立环PD控制器
// 输入：期望角度、真实角度、角速度
// 一个典型的PD控制器，用于保持系统直立
int vertical_pid(VerticalPID pid) {
  // kp*(角度误差) + kd*角速度
  return vertical_params.kp * (pid.angle - pid.med) + vertical_params.kd * pid.gyro_y;
}

// 速度环PI控制器
// 输入:期望速度、左编码器、右编码器
// 输出:电机速度的控制输出量
int velocity_pid(VelocityPID pid) {
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

void control(void) {  // 每隔10ms调用一次
  int pwm_out;        // 电机输出信号

  /* 1.读取编码器和陀螺仪的数据 */
  velocity_pid_data.encoder_data.encoder_left = read_speed(&htim2);
  velocity_pid_data.encoder_data.encoder_right = read_speed(&htim4);
  mpu_dmp_get_data(&mpu_data);
  MPU_Get_Gyroscope(&mpu_data);
  MPU_Get_Accelerometer(&mpu_data);

  /* 2.将数据传入PID控制器,计算输出结果,左右电机转速值 */
  velocity_out = velocity_pid(velocity_pid_data);
  vertical_pid_data.med = velocity_out + med_angle;
  vertical_out = vertical_pid(vertical_pid_data);
  turn_out = turn(turn_pid_data);
  pwm_out = turn_out;
  motor1 = vertical_out - pwm_out;
  motor2 = vertical_out + pwm_out;
  limit_motor(&motor1, &motor2);  // 限幅电机转速值
  motor_load(motor1, motor2);
}
