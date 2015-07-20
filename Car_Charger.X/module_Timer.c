#include <xc.h>
#include <stdint.h>

extern uint8_t T2N;
extern uint8_t T4N;
extern uint8_t PowerOnCANOverTime;
extern uint8_t IRef;
extern uint16_t SinTable[];
extern uint16_t SinNum;

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
    T2N--;
    if(T2N == 0)
    {
        T2CONbits.TON = 0;
        PowerOnCANOverTime = 1;
        IRef = 0;
    }
}

/*
 * 定时器1,3,4初始化
 */
void initTimer()
{
    //Timer1
    
}

/*
 * 定时器1中断函数
 */
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt()
{
    T1CONbits.TON = 0;
    SinNum = 0;
    LATCbits.LATC1 = 1;
    LATCbits.LATC2 = 0;
    IFS0bits.T1IF = 0;
}

/*
 * 定时器3中断函数
 */
void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt()
{
    IFS0bits.T3IF = 0;
}

/*
 * 定时器4中断函数
 */
void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt()
{
    T4N--;
    if(T4N == 0)
    {
        //TIMER1s
        T4N = 0;
        T4CONbits.TON = 0;
        IEC1bits.T4IE = 0;
    }
    IFS1bits.T4IF = 0;
}