#include "SR04.h"
#include "stm32f1xx_hal_tim.h"

uint16_t count;
float distance;
extern TIM_HandleTypeDef htim3;

void RCCdelay_us(uint32_t udelay)
{
  __IO uint32_t Delay = udelay * 72 / 8;//(SystemCoreClock / 8U / 1000000U)
  //见stm32f1xx_hal_rcc.c -- static void RCC_Delay(uint32_t mdelay)
  do
  {
    __NOP();
  }
  while (Delay --);
}

void Get_Distance(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET); //PA3输出高电平
    RCCdelay_us(12); //延时12us   
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET); //PA3输出低电平  
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_2) 
    {
        if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==GPIO_PIN_SET)
        {
            __HAL_TIM_SET_COUNTER(&htim3, 0); // 字母全部大写  计数器清零
            HAL_TIM_Base_Start(&htim3); //开启定时器
        }
        else
        {
             HAL_TIM_Base_Stop(&htim3);
            count = __HAL_TIM_GET_COUNTER(&htim3); //获取计数器的值  单位us
             distance = count * 0.017f; //计算距离，单位为cm        count/1000000*340*100/2   距离(cm) = [时间(微秒) 转 时间(秒)] × 速度(m/s) 转 距离(cm) ÷ 双程变单程
        }
    }
}
