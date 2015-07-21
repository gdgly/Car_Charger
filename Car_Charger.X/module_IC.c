#include "system_global.h"

/*
 * 捕获初始化
 */
void initIC()
{
    //IC1 CrossZeroPoint T3时钟源，下降沿捕捉，单次中断
    IC1CON1bits.ICTSEL = 0b000; //select Timer3 as the clock source
    IC1CON1bits.ICI = 0b00;     //interrupt on every capture event
    IC1CON1bits.ICM = 0b010;    //capture every falling edge
    IPC0bits.IC1IP = 6;         //interrupt priority level 6
    IFS0bits.IC1IF = 0;
    IEC0bits.IC1IE = 1;
    //IC2 LOCK封锁信号 Fosc时钟源，下降沿捕捉，单次中断
    IC2CON1bits.ICTSEL = 0b111; //select Fosc as the clock source
    IC2CON1bits.ICI = 0b00;     //interrupt on every capture event
    IC2CON1bits.ICM = 0b010;    //capture every falling edge
    IPC1bits.IC2IP = 7;         //interrupt priority level 7
    IFS0bits.IC2IF = 0;
    IEC0bits.IC2IE = 1;
    //IC3 FLT信号 Fosc时钟源，上升沿捕捉，单次中断
    IC3CON1bits.ICTSEL = 0b111; //select Fosc as the clock source
    IC3CON1bits.ICI = 0b00;     //interrupt on every capture event
    IC3CON1bits.ICM = 0b011;    //capture every rising edge
    IPC9bits.IC3IP = 7;         //interrupt priority level 7
    IFS2bits.IC3IF = 0;
    IEC2bits.IC3IE = 1;
}

/*
 * 捕获1中断函数
 * 锁相，计算输入电压周期
 */
void __attribute__((__interrupt__, no_auto_psv)) _IC1Interrupt()
{
    T1CONbits.TON = 1;
    period_AC_buff0 = period_AC_buff1;
    period_AC_buff1 = IC1BUF;
    period_AC = period_AC_buff0 < period_AC_buff1 ? period_AC_buff1 - period_AC_buff0 : PR3 - period_AC_buff0 + period_AC_buff1 ;
    IFS0bits.IC1IF = 0;
}

/*
 * 捕获2中断函数
 * 硬件保护信号捕获
 */
void __attribute__((__interrupt__, no_auto_psv)) _IC2Interrupt()
{
    LATAbits.LATA15 = 0;
    PTCONbits.PTEN = 0;
    error_count++;
    if(error_count < 2)
        T4CONbits.TON = 1;
    error_LOCK = 1;
    IFS0bits.IC2IF = 0;
}

/*
 * 捕获3中断函数
 * FLT过流信号捕获
 */
void __attribute__((__interrupt__, no_auto_psv)) _IC3Interrupt()
{
    LATAbits.LATA15 = 0;
    PTCONbits.PTEN = 0;
    error_FLT = 1;
    IFS2bits.IC3IF = 0;
}
