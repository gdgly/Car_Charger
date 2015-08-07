#include "system_global.h"

/*
 * PWM初始化
 */
void initPWM()
{
    PTCON2bits.PCLKDIV = 0b000;     //clock divided by 1
    PTPER = 6000;                   //PTPER=Fosc*T=120M*50us=6000
    //PWM1 DC-DC互补模式
    PWMCON1bits.ITB = 0;            //PTPER provides timing for PWM1 generator
    PWMCON1bits.MDCS = 0;           //PDC1,SDC1 provide duty cycle information for PWM1 generator
    PWMCON1bits.DTC = 1;            //negative dead zone
    IOCON1bits.PENH = 1;            //PWM1 module controls PWM1H pin
    IOCON1bits.PENL = 1;            //PWM1 module controls PWM1L pin
    IOCON1bits.SWAP = 1;            //swap the signal
    IOCON1bits.PMOD = 0b00;         //complementary output module
    PDC1 = 3000;                    //default duty cycle D=0.5
    DTR1 = 120;                     //dead time 1us
    ALTDTR1 = 120;                  //dead time 1us
    PHASE1 = 0;                     //no phase shift
    IPC23bits.PWM1IP = 7;
    IFS5bits.PWM1IF = 0;
    IEC5bits.PWM1IE = 1;
    //PWM2 
    PWMCON2bits.ITB = 0;
    IOCON2bits.PENH = 1;            //PWM2 module controls PWM2H pin
    IOCON2bits.PENL = 1;            //PWM2 module controls PWM2H pin
    IOCON2bits.PMOD = 0b00;         //complementary output module
    //PWM3 
    //PWM4 PFC单路输出
    IOCON4bits.PMOD = 0b11;         //true independent PWM output mode
    IOCON4bits.PENH = 1;            //PWM module controls PWM4H pin
    PWMCON4bits.ITB = 1;            //use PHASE and SPHASE to sepcific period
    PHASE4 = 4687;                  //F=50Hz*256=12800Hz
    PDC4 = 2343;                    //default duty cycle D=0.5
    IPC24bits.PWM4IP = 7;
    IFS6bits.PWM4IF = 0;
    IEC6bits.PWM4IE = 1;
    PTCONbits.PTEN = 1;             //turn on PWM
}

/*
 * PWM1周期中断
 */
void __attribute__((__interrupt__, no_auto_psv)) _PWM1Interrupt()
{
    flag_PWM1 = 1;      //周期结束标志置位
    IFS5bits.PWM1IF = 0;
}

/*
 * PWM4周期中断
 */
void __attribute__((__interrupt__, no_auto_psv)) _PWM4Interrupt()
{
    flag_PWM4 = 1;      //周期结束标志置位
    IFS6bits.PWM4IF = 0;
}

/*
 * PWM关闭函数
 */
void closePWMAll()
{
    PORT_OPENPWM = 0;        //硬件封锁
    IOCON1bits.OVRENH = 1;   //软件封锁
    IOCON1bits.OVRENL = 1;
    IOCON2bits.OVRENH = 1;
    IOCON2bits.OVRENL = 1;
    IOCON3bits.OVRENH = 1;
    IOCON3bits.OVRENL = 1;
    IOCON4bits.OVRENH = 1;
    IOCON4bits.OVRENL = 1;
}

/*
 * PWM开启函数
 */
void openPWMAll()
{
    PORT_OPENPWM = 1;        //硬件开启
    IOCON1bits.OVRENH = 0;   //软件开启
    IOCON1bits.OVRENL = 0;
    IOCON2bits.OVRENH = 0;
    IOCON2bits.OVRENL = 0;
    IOCON3bits.OVRENH = 0;
    IOCON3bits.OVRENL = 0;
    IOCON4bits.OVRENH = 0;
    IOCON4bits.OVRENL = 0;
}

/*
 * PWM4开启函数
 */
void openPWM4()
{
    PORT_OPENPWM = 1;        //硬件开启
    IOCON4bits.OVRENH = 0;   //软件开启
    IOCON4bits.OVRENL = 0;
}

/*
 * PWM1、2开启函数
 */
void openPWM12()
{
    PORT_OPENPWM = 1;        //硬件开启
    IOCON1bits.OVRENH = 0;   //软件开启
    IOCON1bits.OVRENL = 0;
    IOCON2bits.OVRENH = 0;
    IOCON2bits.OVRENL = 0;
}

/*
 * PWM1、2关闭函数
 */
void closePWM12()
{
    PORT_OPENPWM = 0;        //硬件关闭
    IOCON1bits.OVRENH = 1;   //软件关闭
    IOCON1bits.OVRENL = 1;
    IOCON2bits.OVRENH = 1;
    IOCON2bits.OVRENL = 1;
}