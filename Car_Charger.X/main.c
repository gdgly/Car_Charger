/* 
 * File:   main.c
 * Author: H2
 *
 * Created on 2015年7月17日, 上午11:41
 */

#include <stdio.h>
#include <stdlib.h>
#define MAIN
#include "system_global.h"
#include "system_config.h"
#include "module_CAN.h"
#include "module_Timer.h"
#include "module_ADC.h"
#include "module_IC.h"
#include "module_PWM.h"
#include "process_state.h"
    
/*
 * 主函数
 */
int main()
{
    initPLL();
    INTCON2bits.GIE = 0;
    initIO();
    if(PORT_OUTCONNECT == 0)
        PORT_OPENPWM = 0;        //软件封锁PWM
    initCAN();
    initTimer2();
    INTCON2bits.GIE = 1;
    //启动CAN********
    T2CONbits.TON = 1;
    while(poweron_CAN_overtime == 0 && poweron_CAN_received == 0);
    initADC();
    initTimer();
    initIC();
    initPWM();
    while(1)
    {
        //ADC采样处理
        //CAN收发
        if(Ug.mean == 311 && PORT_RDY == 1)
        {
            if(PORT_OUTCONNECT == 1)
                stateBadConnect();
            else
                if(error_temp == 1)
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
        {
            PORT_OPENPWM = 0;        //PWM封锁
            PTCONbits.PTEN = 0;
        }
    }
    return (EXIT_SUCCESS);
}

