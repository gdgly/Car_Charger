#include "system_global.h"

/*
 * ADC初始化
 * AN0-Io, AN1-Ig, AN3-Uo, AN4-Temp, AN8-Udc, AN9-Ug
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
    AD1CHS0bits.CH0NA = 0;          //negative input CHO-Vref
    AD1CHS123bits.CH123SA = 0;      //positive input CH1-AN0, CH2-AN1, CH3-AN2
    AD1CHS123bits.CH123NA = 0b00;   //negative input CH1-Vref, CH2-Vref, CH3-Vref
    IPC3bits.AD1IP = 6;
    IFS0bits.AD1IF = 0;
    IEC0bits.AD1IE = 1;
    AD1CON1bits.ADON = 1;           //turn on ADC
    AD1CON1bits.SAMP = 1;           //start sample
    //ADC2
    AD2CON1bits.FORM = 0b10;        //output format fractional
    AD2CON1bits.ASAM = 0;           //manual sample
    AD2CON1bits.SSRCG = 0;          //automatic conversion sequence
    AD2CON1bits.SSRC = 0b111;
    AD2CON1bits.SIMSAM = 1;         //sample simultaneously
    AD2CON2bits.VCFG = 0b000;       //voltage reference AVdd, AVss
    AD2CON2bits.CHPS = 0b11;        //sample CH0, CH1, CH2, CH3
    AD2CON2bits.SMPI = 0b000;       //generate interrupt at every operation
    AD2CON3bits.ADRC = 0;           //use system clock
    AD2CON3bits.ADCS = 4;           //Tad=Tcy*5=1/60M*5=1/12M
    AD2CON3bits.SAMC = 2;           //auto-sample time 2Tad
    AD2CON4bits.ADDMAEN = 0;        //DMA disabled
    AD2CHS0bits.CH0SA = 0b01000;    //positive input CHO-AN9
    AD2CHS0bits.CH0NA = 0;          //negative input CHO-Vref
    AD2CHS123bits.CH123SA = 0;      //positive input CH1-AN3, CH2-AN4, CH3-AN5
    AD2CHS123bits.CH123NA = 0b00;   //negative input CH1-Vref, CH2-Vref, CH3-Vref
    IPC5bits.AD2IP = 6;
    IFS1bits.AD2IF = 0;
    IEC1bits.AD2IE = 1;
    AD2CON1bits.ADON = 1;           //turn on ADC
    AD2CON1bits.SAMP = 1;           //start sample
}

/*
 * ADC1采样转换结束中断
 * 读取数值存储，进行下一次采样
 */
void __attribute__((_interrupt_, no_auto_psv)) _ADC1Interrupt()
{
    //Udc采样
    Udc_ADC.sum = Udc_ADC.sum-Udc_ADC.filter[Udc_ADC.count];
    Udc_ADC.samp = ADC1BUF0;
    Udc_ADC.filter[Udc_ADC.count] = Udc_ADC.samp;
    Udc_ADC.sum = Udc_ADC.sum+Udc_ADC.filter[Udc_ADC.count];
    Udc_ADC.mean = Udc_ADC.sum>>2;
    Udc_ADC.count++;
    if(Udc_ADC.count > 3)
        Udc_ADC.count = 0;
    //Io采样
    Io_ADC.sum = Io_ADC.sum-Io_ADC.filter[Io_ADC.count];
    Io_ADC.samp = ADC1BUF1;
    Io_ADC.filter[Io_ADC.count] = Io_ADC.samp;
    Io_ADC.sum = Io_ADC.sum+Io_ADC.filter[Io_ADC.count];
    Io_ADC.mean = Io_ADC.sum>>2;
    Io_ADC.count++;
    if(Io_ADC.count > 3)
        Io_ADC.count = 0;
    //Ig采样
    Ig_ADC.sum = Ig_ADC.sum-Ig_ADC.filter[Ig_ADC.count];
    Ig_ADC.samp = ADC1BUF2;
    Ig_ADC.filter[Ig_ADC.count] = Ig_ADC.samp;
    Ig_ADC.sum = Ig_ADC.sum+Ig_ADC.filter[Ig_ADC.count];
    Ig_ADC.mean = Ig_ADC.sum>>2;
    Ig_ADC.count++;
    if(Ig_ADC.count > 3)
        Ig_ADC.count = 0;
    IFS0bits.AD1IF = 0;
    AD1CON1bits.SAMP = 1;
}

/*
 * ADC2采样转换结束中断
 * 读取数值存储，进行下一次采样
 */
void __attribute__((_interrupt_, no_auto_psv)) _ADC2Interrupt()
{
    //Ug采样
    Ug_ADC.sum = Ug_ADC.sum-Ug_ADC.filter[Ug_ADC.count];
    Ug_ADC.samp = ADC2BUF0;
    Ug_ADC.filter[Ug_ADC.count] = Ug_ADC.samp;
    Ug_ADC.sum = Ug_ADC.sum+Ug_ADC.filter[Ug_ADC.count];
    Ug_ADC.mean = Ug_ADC.sum>>2;
    Ug_ADC.count++;
    if(Ug_ADC.count > 3)
        Ug_ADC.count = 0;
    //Uo采样
    Uo_ADC.sum = Uo_ADC.sum-Uo_ADC.filter[Uo_ADC.count];
    Uo_ADC.samp = ADC2BUF1;
    Uo_ADC.filter[Uo_ADC.count] = Uo_ADC.samp;
    Uo_ADC.sum = Uo_ADC.sum+Uo_ADC.filter[Uo_ADC.count];
    Uo_ADC.mean = Uo_ADC.sum>>2;
    Uo_ADC.count++;
    if(Uo_ADC.count > 3)
        Uo_ADC.count = 0;
    //Temp采样
    Temp_ADC.sum = Temp_ADC.sum-Temp_ADC.filter[Temp_ADC.count];
    Temp_ADC.samp = ADC1BUF2;
    Temp_ADC.filter[Temp_ADC.count] = Temp_ADC.samp;
    Temp_ADC.sum = Temp_ADC.sum+Temp_ADC.filter[Temp_ADC.count];
    Temp_ADC.mean = Temp_ADC.sum>>2;
    Temp_ADC.count++;
    if(Temp_ADC.count > 3)
        Temp_ADC.count = 0;
    IFS1bits.AD2IF = 0;
    AD2CON1bits.SAMP = 1;
}