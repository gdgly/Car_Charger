#include "system_global.h"

#define DELAY_PULSE 0

/*
 * 复位信号高电平延时
 */
void outRSTPulse()
{
    int i=0;
    PORT_RST = 1;
    for(i=0; i<DELAY_PULSE; i++);
    PORT_RST = 0;
}

/*
 * 电池反接处理子程序
 * PORT_OUTCONNECT = 0
 */
void stateBadConnect()
{
    openPWMAll();
    PORT_OUTREVIND = 1;
}

/*
 * 温度故障处理子程序
 * PORT_OUTCONNECT = 1，error_temp = 1
 */
void stateOverTemp()
{
    openPWMAll();
    PORT_OUTREVIND = 0;
}

/*
 * 故障LOCK+FTL处理子程序
 * PORT_OUTCONNECT = 1，error_temp = 0，error_LOCK = 1，error_FLT = 1
 */
void stateLockAll()
{
    PORT_OUTREVIND = 0;
    if(host_turnon == 1 && (error_count == 0 || (error_count == 1 && flag_timingRST == 1)) && Io_ADC.mean < IO_REF_LIMIT )
    {
        error_FLT = 0;
        error_LOCK = 0;
        openPWMAll();
        outRSTPulse();
    }
    else
        closePWMAll();
}

/*
 * 故障LOCK处理子程序
 * PORT_OUTCONNECT = 1，error_temp = 0，error_LOCK = 1，，error_FLT = 0
 */
void stateLockLOCK()
{
    PORT_OUTREVIND = 0;
    if(host_turnon == 1 && (error_count == 0 || (error_count == 1 && flag_timingRST == 1)) && Io_ADC.mean < IO_REF_LIMIT )
    {
        error_LOCK = 0;
        openPWMAll();
        outRSTPulse();
    }
    else
        closePWMAll();
}

/*
 * 故障FLT处理子程序
 * PORT_OUTCONNECT = 1，error_temp = 0，error_LOCK = 0，error_FLT = 1
 */
void stateLockFLT()
{
    PORT_OUTREVIND = 0;
    if(host_turnon == 1 && (error_count == 0 || (error_count == 1 && flag_timingRST == 1)) && Io_ADC.mean < IO_REF_LIMIT )
    {
        error_FLT = 0;
        openPWMAll();
    }
    else
        closePWMAll();
}

/*
 * 正常运行子程序
 * PORT_OUTCONNECT = 1，error_temp = 0，error_LOCK = 0，error_FLT = 0
 */
void stateOperation()
{
    PORT_OUTREVIND = 0;
    if(error_count == 1)
    {
        error_testcount++;
        if(error_testcount > 200)
        {
            error_count = 0;
            error_testcount = 0;
        }
    }
    if(host_turnon == 1)
    {
        openPWM4();
        if(flag_PWM4)
            updatePWM4DutyCycle();
        if(Udc_ADC.samp > UDC_REF)
        {
            openPWM12();
            if(flag_PWM1)
                updatePWM12DutyCycle();
        }
    }
    else
        closePWMAll();
}