#include "system_global.h"

#define I_DEFAULT 0
#define TIMING_PHASELOCK 0

/*
 * 定时器2初始化
 * 定时器模式，上电CAN接收超时定时10s
 * T=46875*256/60M=0.2s
 */
void initTimer2()
{
    T2CONbits.TCS = 0;
    T2CONbits.TGATE = 0;
    T2CONbits.TCKPS = 0b11;
    TMR2 = 0x00;
    PR2 = 46875;
    IPC1bits.T2IP = 1;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
}

/*
 * 定时器2中断函数
 * 定时10s，50次中断后超时，关定时器，标志置位
 */
void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt()
{
    T2_count--;
    if(T2_count == 0)
    {
        T2CONbits.TON = 0;
        poweron_CAN_overtime = 1;
        I_ref = I_DEFAULT;
    }
}

/*
 * 定时器1,3,4初始化
 */
void initTimer()
{
    //Timer1 锁相定时
    T1CONbits.TCKPS = 0b00;         //1:1 prescale value
    T1CONbits.TCS = 0;              //select internal clock as clock source
    T1CONbits.TGATE = 0;            //gated time accumulation disabled
    TMR1 = 0x00;
    PR1 = TIMING_PHASELOCK;
    IPC0bits.T1IP = 6;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    //Timer3 IC1定时器时钟源
    T3CONbits.TCKPS = 0b10;         //1:64 prescale value
    T3CONbits.TCS = 0;              //select internal clock as clock source
    T3CONbits.TGATE = 0;            //gated time accumulation disabled
    TMR3 = 0x00;
    PR3 = 0xFFFF;
    IEC0bits.T3IE = 0;              //disable interrupt of Timer3
    T3CONbits.TON = 1;
    //Timer4 重启尝试延时
    T4CONbits.TCKPS = 0b11;         //1:256 prescale value
    T4CONbits.TCS = 0;              //select internal clock as clock source
    T4CONbits.TGATE = 0;            //gated time accumulation disabled
    TMR4 = 0x00;
    PR4 = 46875;
    IPC6bits.T4IP = 6;
    IFS1bits.T4IF = 0;
    IEC1bits.T4IE = 1;
}

/*
 * 定时器1中断函数
 * 锁相结束中断，正弦表复位，PFC信号切换
 */
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt()
{
    T1CONbits.TON = 0;
    sin_num = 0;
    LATCbits.LATC1 = 1;
    LATCbits.LATC2 = 0;
    IFS0bits.T1IF = 0;
}

/*
 * 定时器4中断函数
 */
void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt()
{
    T4_count--;
    if(T4_count == 0)
    {
        flag_timingRST = 1;      //重启尝试延时1s完成
        T4_count = 5;
        T4CONbits.TON = 0;
        IEC1bits.T4IE = 0;
    }
    IFS1bits.T4IF = 0;
}