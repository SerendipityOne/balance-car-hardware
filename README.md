# 平衡车硬件项目 (Balance Car Hardware)

基于STM32F103的二轮自平衡小车硬件控制代码。

## 项目概述

这是一个使用STM32F103微控制器开发的二轮自平衡小车项目。该项目集成了多种传感器和执行器，实现了小车的姿态检测、电机控制、距离测量等功能。

## 硬件配置

### 主控芯片
- **STM32F103** - ARM Cortex-M3 内核微控制器

### 传感器模块
- **MPU6050** - 六轴陀螺仪加速度计，用于姿态检测
- **HC-SR04** - 超声波测距模块
- **编码器** - 电机转速反馈

### 执行器
- **双直流电机** - 驱动小车前进后退
- **OLED显示屏** - 显示系统状态信息

### 通信接口
- **UART3** - 串口通信，用于调试和数据传输
- **I2C** - 与MPU6050传感器通信

## 功能特性

- ✅ **姿态检测**: 使用MPU6050获取pitch、roll、yaw角度信息
- ✅ **电机控制**: PWM控制双电机，支持正反转
- ✅ **速度测量**: 编码器反馈电机转速
- ✅ **距离测量**: 超声波测距避障
- ✅ **显示功能**: OLED屏幕显示系统状态
- ✅ **串口通信**: 支持数据监控和调试
- 🚧 **平衡算法**: PID控制算法（待实现）

## 文件结构

```
balance-car-hardware/
├── Core/
│   ├── Inc/                    # 头文件目录
│   │   ├── main.h             # 主程序头文件
│   │   ├── motor.h            # 电机控制头文件
│   │   ├── encoder.h          # 编码器头文件
│   │   ├── oled.h             # OLED显示头文件
│   │   ├── sr04.h             # 超声波传感器头文件
│   │   └── ...
│   └── Src/                    # 源文件目录
│       ├── main.c             # 主程序文件
│       ├── motor.c            # 电机控制实现
│       ├── encoder.c          # 编码器读取实现
│       ├── oled.c             # OLED显示实现
│       ├── sr04.c             # 超声波测距实现
│       └── ...
├── MyCode/                     # 自定义代码
│   ├── mpu6050.c              # MPU6050驱动
│   ├── mpu6050.h
│   ├── IIC.c                  # I2C通信
│   ├── IIC.h
│   └── ...
├── Drivers/                    # STM32 HAL库
└── MDK-ARM/                   # Keil工程文件
```

## 硬件连接

### 电机驱动
- **电机A**: PB12(方向1), PB13(方向2), TIM1_CH4(PWM)
- **电机B**: PB14(方向1), PB15(方向2), TIM1_CH1(PWM)

### 编码器接口
- **编码器1**: TIM2 编码器模式
- **编码器2**: TIM4 编码器模式

### 传感器接口
- **MPU6050**: I2C1接口
- **超声波**: GPIO触发和回波检测

### 显示和通信
- **OLED**: I2C接口
- **串口**: UART3 (调试输出)

## 开发环境

- **IDE**: Keil uVision5 / STM32CubeIDE
- **HAL库**: STM32F1xx HAL Driver
- **编程语言**: C语言
- **调试器**: ST-Link V2

## 使用说明

### 1. 环境搭建
1. 安装Keil uVision5或STM32CubeIDE
2. 安装STM32F1xx HAL库
3. 连接ST-Link调试器

### 2. 编译下载
1. 打开工程文件
2. 编译项目
3. 通过ST-Link下载到STM32F103

### 3. 功能测试
1. 上电后OLED显示"Init Success"
2. 串口输出"Hello World!"
3. 可通过串口监控传感器数据

### 4. 调试模式
在`main.c`中取消注释相关代码段可开启：
- 编码器数据显示
- 姿态角度显示  
- 超声波距离显示

## API 接口

### 电机控制
```c
void motor_load(int motor1, int motor2);
// motor1, motor2: 电机速度 (-7200~7200)
```

### 编码器读取
```c
int read_speed(TIM_HandleTypeDef* htim);
// 返回编码器脉冲计数
```

### 姿态获取
```c
uint8_t mpu_dmp_get_data(float* pitch, float* roll, float* yaw);
// 获取欧拉角数据
```

### 距离测量
```c
void get_distance(void);
// 获取超声波距离数据
```

## 开发计划

- [ ] 实现PID平衡控制算法
- [ ] 添加遥控功能
- [ ] 优化电机控制精度
- [ ] 增加蓝牙通信模块
- [ ] 完善上位机监控软件

## 贡献指南

欢迎提交Issue和Pull Request来改进项目！

1. Fork 本项目
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 创建Pull Request

## 许可证

本项目基于MIT许可证开源 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 联系方式

- 项目维护者: SerendipityOne
- 项目链接: [https://github.com/SerendipityOne/balance-car-hardware](https://github.com/SerendipityOne/balance-car-hardware)

## 致谢

- STMicroelectronics - STM32 HAL库
- InvenSense - MPU6050传感器支持
- 开源社区的贡献者们

---

⭐ 如果这个项目对您有帮助，请给个星标支持！