/* 
 * File:   main.c
 * Author: H2
 *
 * Created on 2015年7月17日, 上午11:41
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "global.h"

extern unsigned int PowerOnCANOverTime;
extern unsigned int PowerOnCANReceived;

/*
 * 主函数
 */
int main()
{
    initPLL();
    INTCON2bits.GIE = 0;
    initIO();
    if(PORTDbits.RD11 == 0)
        LATAbits.LATA15 = 0;
    initCAN();
    initTimer2();
    INTCON2bits.GIE = 1;
    //启动CAN********
    T2CONbits.TON = 1;
    while(PowerOnCANOverTime == 0 && PowerOnCANReceived == 0);
    initADC();
    initTimer();
    initIC();
    initPWM();
    while(1)
    {
    }
    return (EXIT_SUCCESS);
}

