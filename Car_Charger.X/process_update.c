#include "system_global.h"

/*
 * PWM4周期占空比更新子程序
 */
void updatePWM4DutyCycle()
{
    if(sin_num == 100)
    {
        LATCbits.LATC1 = 0;
        LATCbits.LATC2 = 1;
    }
    if(Udc_ADC.mean > UDC_REF_LIMIT)
        closePWMAll();
    else
    {
        if(sin_num == 0)
        {
            PIUdc();
        }
        //赋值
    }
    sin_num++;
    flag_PWM4 = 0;
}

/*
 * PWM1、PWM2周期占空比更新子程序
 */
void updatePWM12DutyCycle()
{
    if(Uo_ADC.mean > UO_REF_SWITCH)
    {
        if(flag_switch_start == 1)
        {
            openPWM12();
        }
    }
    else
    {
        if(Uo_ADC.mean > UO_REF_LIMIT)
            closePWMAll();
        else
            PIUo();
    }
}
