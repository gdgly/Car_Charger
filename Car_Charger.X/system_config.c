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
    TRISAbits.TRISA2 = 0;      //OUT-REV-DET 电池反插检测
    TRISAbits.TRISA3 = 0;      //IO-3 PWM封锁信号
    TRISDbits.TRISD11 = 0;       //CAP-RDY 硬件就绪信号
    TRISFbits.TRISF2 = 1;       //电池反接指示
    TRISAbits.TRISA15 = 1;      //封锁复位
    //CAN1
    TRISDbits.TRISD3 = 0;       //CAN-TXD-1
    RPOR1bits.RP67R = 0x0E;
    TRISDbits.TRISD12 = 1;      //CAN-RXD-1
    RPINR26bits.C1RXR = 0x4C;
    //CAN2
    TRISGbits.TRISG14 = 0;      //CAN-TXD-2
    RPOR15bits.RP126R = 0x0F;
    TRISGbits.TRISG13 = 1;      //CAN-RXD-2
    RPINR26bits.C2RXR = 0x7C;
    //IC1 
    RPINR7bits.IC1R = 0x4A;     //RPI18
    TRISDbits.TRISD10 = 1;
    //IC2
    RPINR7bits.IC2R = 0x14;     //RP64 LOCK
    TRISAbits.TRISA14 = 1;
    //IC3
    RPINR8bits.IC3R = 0x40;     //RP30 CAP-FLT
    TRISDbits.TRISD0 = 1;
}
