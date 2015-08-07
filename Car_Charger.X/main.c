/* 
 * File:   main.c
 * Author: H2
 *
 * Created on 2015年7月17日, 上午11:41
 */

#include <stdio.h>
#include <stdlib.h>
#define MAIN
#include "system_config.h"
#include "system_global.h"
    
/*
 * 主函数
 */
int main()
{
    initPLL();
    INTCON2bits.GIE = 0;
    initIO();
    if(PORT_OUTCONNECT == 0)
        closePWMAll();        //PWM封锁
    initCAN();
    initTimer2();
    INTCON2bits.GIE = 1;
    /*
     * 启动CAN
     */
    T2CONbits.TON = 1;
    while(poweron_CAN_overtime == 0 && poweron_CAN_received == 0);      //等待上位机信号或超时使用默认值
    initADC();
    initTimer();
    initIC();
    initPWM();
    while(1)
    {
        /*
         * CAN收发
         */
        //电压达标且硬件就绪时根据状态处理
        if(Ug_ADC.mean == 311 && PORT_RDY == 1)
        {
            if(PORT_OUTCONNECT == 1)
                stateBadConnect();
            else
                if(error_Temp == 1)
                    stateOverTemp();
                else
                    if(error_LOCK == 1)
                        if(error_FLT == 1)
                            stateLockAll();
                        else
                            stateLockLOCK();
                    else
                        if(error_FLT == 1)
                            stateLockFLT();
                        else
                            stateOperation();
        }
        else
            closePWMAll();
    }
    return (EXIT_SUCCESS);
}

