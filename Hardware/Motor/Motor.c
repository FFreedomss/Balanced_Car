#include "Motor.h"

extern TIM_HandleTypeDef htim1;
//取绝对值
int abs(int p)
{
  if(p>0)
    return p;// 如果本来就是正数，直接原样返回
  else
    return -p;// 如果是负数（比如-3000），加上负号让它负负得正（变成3000）
}

void Load(int moto1, int moto2)       //-7200~7200
{
    //左轮
  if(moto1<0)
  {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);//AIN1=1
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);//AIN2=0
  }
  else
  {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);//AIN1=0
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);//AIN2=1
  }
  __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_4, abs(moto1));//动态修改输出给电机的 PWM 脉冲宽度（也就是改变占空比），从而控制轮子转动的速度 因为定时器的 CCR 寄存器只认识正数（比如 0 到 7200）。在物理世界里，不存在“宽度为负数”的波形。
        // 直接操作底层寄存器的方法：htim1.Instance->CCR1 = abs(moto1);
    
    //右轮
  if(moto2<0)
  {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);//BIN1=1
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);//BIN2=0
  }
  else
  {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);//BIN1=0
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);//BIN2=1
  }
  __HAL_TIM_SetCompare (&htim1, TIM_CHANNEL_1, abs(moto2));
}
