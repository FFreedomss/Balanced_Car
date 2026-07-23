#include "Encoder.h"
//测速底层函数（脉冲）
int Read_Speed(TIM_HandleTypeDef *htim)
{
    int temp;
    temp = (short)__HAL_TIM_GET_COUNTER(htim);// 获取计数器的值,(short)是为了把它当成有符号数来读，这样就能正确处理正转和反转的情况
    __HAL_TIM_SET_COUNTER(htim, 0); // 计数器清零
    return temp;
}
