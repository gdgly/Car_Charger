#include "system_global.h"

/*
 * 配置PLL时钟
 * Fosc=8M*60/2/2=120M
 */
void initPLL()
{
    PLLFBDbits.PLLDIV = 58;
    CLKDIVbits.PLLPOST = 0;
    CLKDIVbits.PLLPRE = 0;
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(0x01);
    while(OSCCONbits.COSC != 0b011);
    while(OSCCONbits.LOCK != 1);
}

/*
 * IO初始化
 */
void initIO()
{
    //ADC
    ANSELA=ANSELB=ANSELC=ANSELD=ANSELE=ANSELG=0;
    ANSELB=0x033f;      //AN0, AN1, AN2, AN3, AN4, AN5, AN8, AN9
    //Signal
    TRISDbits.TRISD11 = 0;      //OUT-REV-DET 电池反插检测
    TRISAbits.TRISA15 = 0;      //IO-3 PWM封锁信号
    TRISAbits.TRISA3 = 0;       //CAP-RDY 硬件就绪信号
    TRISFbits.TRISF2 = 1;       //电池反接指示
    TRISDbits.TRISD10 = 1;      //封锁复位
    //CAN1******
    TRISDbits.TRISD3 = 0;
    RPOR1bits.RP67R = 0x0e;
    TRISDbits.TRISD12 = 1;
    RPINR26bits.C1RXR = 0x4c;
    //CAN2*******
    TRISDbits.TRISD4 = 0;
    RPOR2bits.RP68R = 0x0f;
    TRISDbits.TRISD13 = 1;
    RPINR26bits.C2RXR = 0x4d;
    //IC1 
    RPINR7bits.IC1R = 0x12;     //RPI18
    TRISAbits.TRISA2 = 1;       //RA2 set to input
    //IC2
    RPINR7bits.IC2R = 0x40;     //RP64 LOCK
    TRISDbits.TRISD0 = 1;       //RD0 set to input
    //IC3
    RPINR8bits.IC3R = 0x1E;     //RP30 CAP-FLT
    TRISAbits.TRISA14 = 1;      //RA14 set to input
}
