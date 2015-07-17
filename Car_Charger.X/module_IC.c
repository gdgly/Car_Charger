#include <xc.h>

/*
 * 捕获初始化
 */
void initIC()
{
    //IC1
    IC1CON1bits.ICTSEL = 0b111; //select Fosc as the clock source
    IC1CON1bits.ICI = 0b00;     //interrupt on every capture event
    IC1CON1bits.ICM = 0b010;    //capture every falling edge
    IPC0bits.IC1IP = 7;         //
    IFS0bits.IC1IF = 0;         //
    IEC0bits.IC1IE = 1;         //
    //IC2 LOCK信号硬件封锁 系统时钟源，下降沿捕捉，单次中断
    IC2CON1bits.ICTSEL = 0b111; //select Fosc as the clock source
    IC2CON1bits.ICI = 0b00;     //interrupt on every capture event
    IC2CON1bits.ICM = 0b010;    //capture every falling edge
    IPC1bits.IC2IP = 7;
    IFS0bits.IC2IF = 0;
    IEC0bits.IC2IE = 1;
    //IC3
    
}
