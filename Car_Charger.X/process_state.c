#include "system_global.h"

/*
 * 复位信号高电平延时
 */
void delayRST()
{
    
}

/*
 * 电池反接处理子程序
 * PORT_OUTCONNECT = 0
 */
void stateBadConnect()
{
    PORT_OPENPWM = 0;
    PTCONbits.PTEN = 0;
    PORT_OUTREVIND = 1;
}

/*
 * 温度故障处理子程序
 * PORT_OUTCONNECT = 1，error_temp = 1
 */
void stateOverTemp()
{
    PORT_OPENPWM = 0;
    PTCONbits.PTEN = 0;
    PORT_OUTREVIND = 0;
}

/*
 * 故障LOCK+FTL处理子程序
 * PORT_OUTCONNECT = 1，error_temp = 0，error_LOCK = 1，error_FLT = 1
 */
void stateLockAll()
{
    PORT_OUTREVIND = 0;
    if(host_trunon == 1 && (error_count == 0 || (error_count == 1 && flag_timingRST == 1)) && Io.mean < I_ref0 )
    {
        error_FLT = 0;
        error_LOCK = 0;
        PORT_OPENPWM = 1;
        PORT_RST = 1;
        delayRST();
        PORT_RST = 0;
    }
    else
    {
        PORT_OPENPWM = 0;
        PTCONbits.PTEN = 0;
    }
}

/*
 * 故障LOCK处理子程序
 * PORT_OUTCONNECT = 1，error_temp = 0，error_LOCK = 1，，error_FLT = 0
 */
void stateLockLOCK()
{
    
}

/*
 * 故障FLT处理子程序
 * PORT_OUTCONNECT = 1，error_temp = 0，error_LOCK = 0，error_FLT = 1
 */
void stateLockFLT()
{

}

/*
 * 正常运行子程序
 * PORT_OUTCONNECT = 1，error_temp = 0，error_LOCK = 0，error_FLT = 0
 */
void stateOperation()
{
    
}