/* 
 * File:   main.c
 * Author: H2
 *
 * Created on 2015年7月17日, 上午11:41
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include "system_config.h"
#include "module_CAN.h"
#include "module_Timer.h"
#include "module_ADC.h"
#include "module_IC.h"
#include "module_PWM.h"

uint8_t T2N = 50;          //定时器2循环计数次数，T2N*0.2s=10s
uint8_t T4N = 0;           //定时器4循环计数次数，T4N*
uint8_t PowerOnCANOverTime = 0;     //上电等待上位机信号超时标志
uint8_t PowerOnCANReceived = 0;     //上电接收上位机信号完成标志
uint8_t IRef = 0;
uint16_t SinTable[] = {0,8,16,24,32,40,47,55,63,71,79,86,94,101,108,116,123,130,137,143,150,156,163,169,175,181,186,192,197,202,207,211,216,220,224,228,231,234,238,240,243,245,247,249,251,252,253,254,255,255,256,255,255,254,253,252,251,249,247,245,243,240,238,234,231,228,224,220,216,211,207,202,197,192,186,181,175,169,163,156,150,143,137,130,123,116,108,101,94,86,79,71,63,55,47,40,32,24,16,8,0};
uint16_t SinNum = 0;        //正弦读取计位
uint16_t PeriodACBuff0 = 0, PeriodACBuff1 = 0, PeriodAC = 0;        //AC周期存储
    
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

