#include "system_global.h"

/*
 * PFC电压环PI调节函数
 */
void PIUdc()
{
    Udc_PI.error = UDC_REF - Udc_ADC.mean;
    if(Udc_PI.error > UDC_ERROR_LIMITUP)        //输入限幅
        Udc_PI.error = UDC_ERROR_LIMITUP;
    if(Udc_PI.error < UDC_ERROR_LIMITDOWN)
        Udc_PI.error = UDC_ERROR_LIMITDOWN;
    Udc_PI.output = __builtin_muluu(UDC_PI_KP, Udc_PI.error - Udc_PI.errorex)+__builtin_muluu(UDC_PI_KITSAMP, Udc_PI.error)+Udc_PI.errorex;
    if(Udc_PI.output > UDC_OUTPUT_LIMITUP)        //输出限幅
        Udc_PI.output = UDC_OUTPUT_LIMITUP;
    if(Udc_PI.output < UDC_OUTPUT_LIMITDOWN)
        Udc_PI.output = UDC_OUTPUT_LIMITDOWN;
    Udc_PI.errorex = Udc_PI.error;
    Udc_PI.outputex = Udc_PI.output;
}

/*
 * DCDC电压环PI调节函数
 */
void PIUo()
{
    Uo_PI.error = UO_REF - Uo_ADC.mean;
    if(Uo_PI.error > UO_ERROR_LIMITUP)        //输入限幅
        Uo_PI.error = UO_ERROR_LIMITUP;
    if(Uo_PI.error < UO_ERROR_LIMITDOWN)
        Uo_PI.error = UO_ERROR_LIMITDOWN;
    Uo_PI.output = __builtin_muluu(UO_PI_KP, Uo_PI.error - Uo_PI.errorex)+__builtin_muluu(UO_PI_KITSAMP, Uo_PI.error)+Uo_PI.errorex;
    if(Uo_PI.output > UO_OUTPUT_LIMITUP)        //输出限幅
        Uo_PI.output = UO_OUTPUT_LIMITUP;
    if(Uo_PI.output < UO_OUTPUT_LIMITDOWN)
        Uo_PI.output = UO_OUTPUT_LIMITDOWN;
    Uo_PI.errorex = Uo_PI.error;
    Uo_PI.outputex = Uo_PI.output;
}

/*
 * DCDC电流环PI调节函数
 */
void PIIo()
{
    Io_PI.error = Io_ref - Io_ADC.mean;
    if(Io_PI.error > IO_ERROR_LIMITUP)        //输入限幅
        Io_PI.error = IO_ERROR_LIMITUP;
    if(Io_PI.error < IO_ERROR_LIMITDOWN)
        Io_PI.error = IO_ERROR_LIMITDOWN;
    Io_PI.output = __builtin_muluu(IO_PI_KP, Io_PI.error - Io_PI.errorex)+__builtin_muluu(IO_PI_KITSAMP, Io_PI.error)+Io_PI.errorex;
    if(Io_PI.output > IO_OUTPUT_LIMITUP)        //输出限幅
        Io_PI.output = IO_OUTPUT_LIMITUP;
    if(Io_PI.output < IO_OUTPUT_LIMITDOWN)
        Io_PI.output = IO_OUTPUT_LIMITDOWN;
    Io_PI.errorex = Io_PI.error;
    Io_PI.outputex = Io_PI.output;
}
