#include "system_global.h"

/*
 * PWM4周期占空比更新子程序
 */
void updatePWM4DutyCycle()
{
    if(sin_num == 128)      //半周期后切换
    {
        PORT_PFCLEFT = 0;
        PORT_PFCRIGHT = 1;
        sin_num = 0;
    }
    if(Udc_ADC.mean > UDC_REF_LIMIT)
        closePWMAll();
    else
    {
        openPWMAll();
        if(sin_num == 0)
            PIUdc();
        SDC4 = __builtin_muluu(Udc_PI.output, sin_table[sin_num]);
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
        if(switch_start == 1)
        {
            openPWM12();
            if(switch_complete == 1)
            {
                if(Io_ADC.mean > IO_REF_LIMIT)
                    closePWMAll();
                else
                {
                    openPWMAll();
                    PIUo();
                }
            }
            else
            {
                switch_count++;
                if(switch_count > 4)
                {
                    switch_complete = 1;
                    switch_count = 0;
                }
                PIUo();
            }
        }
        else
        {
            closePWM12();
            switch_hold++;
            if(switch_hold > 2000)
            {
                switch_hold = 0;
                switch_start = 1;
            }
        }
    }
    else
    {
        if(Uo_ADC.mean > UO_REF_LIMIT)
            closePWMAll();
        else
        {
            openPWMAll();
            PIUo();
        }
    }
}
