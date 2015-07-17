#include <xc.h>

/*
 * PWM初始化
 */
void initPWM()
{
    PTCON2bits.PCLKDIV = 0b000;     //clock divided by 1
    PTPER = 6000;                   //PTPER=Fosc*T=120M*50us=6000
    //PWM1 互补模式
    PWMCON1bits.ITB = 0;            //PTPER provides timing for PWM1 generator
    PWMCON1bits.MDCS = 0;           //PDC1,SDC1 provide duty cycle information for PWM1 generator
    IOCON1bits.PENH = 1;            //PWM1 module controls PWM1H pin
    IOCON1bits.PENL = 1;            //PWM1 module controls PWM1L pin
    IOCON1bits.PMOD = 0b00;         //complementary output module
    DTR1 = 120;                     //deadtime 1us
    ALTDTR1 = 120;                  //deadtime 1us
    PHASE1 = 0;                     //phase shift 0
    //PWM2 
    PWMCON2bits.ITB = 0;
    IOCON2bits.PENH = 1;            //PWM2 module controls PWM2H pin
    IOCON2bits.PENL = 1;            //PWM2 module controls PWM2H pin
    IOCON2bits.PMOD = 0b00;         //complementary output module
    //PWM3 
    //PWM4 PFC单路输出
    IOCON4bits.PMOD = 0b11;         //true independent PWM output mode
    IOCON4bits.PENL = 1;            //PWM module controls PWM4L pin
    PWMCON4bits.ITB = 1;            //use PHASE and SPHASE to sepcific period
    PWMCON4bits.DTC = 0;            //no deadtime
    SPHASE4 = 12000;                //F=Fosc/SPHSE4=120M/12k=10kHz
    SDC4 = 6000;                    //default duty cycle D=0.5
    PTCONbits.PTEN = 1;             //turn on PWM
}
