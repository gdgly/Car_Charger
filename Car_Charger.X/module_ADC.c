#include "system_global.h"

/*
 * ADC1初始化
 */
void initADC()
{
    //ADC1
    AD1CON1bits.AD12B = 0;          //10-bit operation mode
    AD1CON1bits.FORM = 0b10;        //output format fractional
    AD1CON1bits.ASAM = 0;           //manual sample
    AD1CON1bits.SSRCG = 0;          //automatic conversion sequence
    AD1CON1bits.SSRC = 0b111;
    AD1CON1bits.SIMSAM = 1;         //sample simultaneously
    AD1CON2bits.VCFG = 0b000;       //voltage reference AVdd, AVss
    AD1CON2bits.CHPS = 0b11;        //sample CH0, CH1, CH2, CH3
    AD1CON2bits.SMPI = 0b000;       //generate interrupt at every operation
    AD1CON3bits.ADRC = 0;           //use system clock
    AD1CON3bits.ADCS = 4;           //Tad=Tcy*5=1/60M*5=1/12M
    AD1CON3bits.SAMC = 2;           //auto-sample time 2Tad
    AD1CON4bits.ADDMAEN = 0;        //DMA disabled
    AD1CHS0bits.CH0SA = 0b01000;    //positive input CHO-AN8
    AD1CHS0bits.CH0NA = 0;          //nagitive input CHO-Vref
    AD1CHS123bits.CH123SA = 0;      //positive input CH1-AN0, CH2-AN1, CH3-AN2
    AD1CHS123bits.CH123NA = 0b00;   //nagitive input CH1-Vref, CH2-Vref, CH3-Vref
    IPC3bits.AD1IP = 6;             //
    IFS0bits.AD1IF = 0;
    IEC0bits.AD1IE = 1;
    AD1CON1bits.ADON = 1;           //turn on ADC
    AD1CON1bits.SAMP = 1;           //start sample
}
