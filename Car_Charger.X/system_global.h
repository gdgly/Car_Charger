/* 
 * File:   system_global.h
 * Author: H2
 *
 * Created on 2015年7月21日, 下午4:44
 */

#ifndef SYSTEM_GLOBAL_H
#define	SYSTEM_GLOBAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>

//IO口定义
#define PORT_OUTCONNECT PORTDbits.RD11      //电池反接检测口
#define PORT_RDY PORTAbits.RA3              //硬件就绪口
#define PORT_OPENPWM LATAbits.LATA15        //PWM封锁
#define PORT_OUTREVIND LATFbits.LATF2       //电池反接指示
#define PORT_RST LATDbits.LATD10            //封锁复位
#define PORT_PFCLEFT LATCbits.LATC1         //PFC输出PWM控制
#define PORT_PFCRIGHT LATCbits.LATC2
//锁相环
#define TIMING_PHASELOCK 0
//PFC调节常量
#define UDC_REF 400      //直流母线电压给定
#define UDC_REF_LIMIT 450      //直流母线电压超限值
#define UDC_ERROR_LIMITUP 30     //直流母线电压误差上下限
#define UDC_ERROR_LIMITDOWN -30
#define UDC_OUTPUT_LIMITUP 3000     //PI调节器输出上下限
#define UDC_OUTPUT_LIMITDOWN -3000
#define UDC_PI_KP 1     //PFC电压环PI调节参数
#define UDC_PI_KITSAMP 1
//DCDC电压调节常量
#define UO_REF 900      //输出电压给定值
#define UO_REF_LIMIT 900        //输出电压超限值
#define UO_REF_SWITCH 900      //恒流恒压模式切换临界值
#define UO_REF_OPEN 900        //后级电路开启基准值
#define UO_ERROR_LIMITUP 30     //输出电压误差上下限
#define UO_ERROR_LIMITDOWN -30
#define UO_OUTPUT_LIMITUP 3000      //PI调节祈输出上下限
#define UO_OUTPUT_LIMITDOWN -3000
#define UO_PI_KP 1      //DCDC电压环PI调节参数
#define UO_PI_KITSAMP 1
//DCDC电流调节常量
#define IO_DEFAULT 600      //电流给定默认值
#define IO_REF_LIMIT 900        //电流给定超限值
#define IO_ERROR_LIMITUP 30
#define IO_ERROR_LIMITDOWN -30
#define IO_OUTPUT_LIMITUP 3000
#define IO_OUTPUT_LIMITDOWN -3000
#define IO_PI_KP 1      //DCDC电流环PI调节参数
#define IO_PI_KITSAMP 1

typedef struct
{
    uint16_t samp;
    uint16_t sum;
    uint16_t mean;
    uint16_t real;
    uint16_t filter[4];
    uint8_t count;
} DATA_ADC;     //ADC采样数据
typedef struct
{
    int16_t error;     //误差
    int16_t errorex;       //前一采样周期误差
    int16_t output;
    int16_t outputex;
} DATA_PI;      //PI调节参数
    
#ifdef MAIN

//定时器计数
uint8_t T2_count = 50;          //定时器2循环计数次数，50*0.2s=10s
uint8_t T4_count = 5;           //定时器4循环计数次数，5*0.2s=1s
//开机信号标志
uint8_t poweron_CAN_overtime = 0;     //上电等待上位机信号超时标志
uint8_t poweron_CAN_received = 0;     //上电接收上位机信号完成标志
//正弦表
uint16_t sin_table[] = {0, 6, 13, 19, 25, 31, 38, 44, 50, 56, 62, 68, 74, 80, 86, 92, 98, 104, 109, 115, 121, 126, 132, 137, 142, 147, 152, 157, 162, 167, 172, 177, 181, 185, 190, 194, 198, 202, 206, 209, 213, 216, 220, 223, 226, 229, 231, 234, 237, 239, 241, 243, 245, 247, 248, 250, 251, 252, 253, 254, 255, 255, 256, 256, 256, 256, 256, 255, 255, 254, 253, 252, 251, 250, 248, 247, 245, 243, 241, 239, 237, 234, 231, 229, 226, 223, 220, 216, 213, 209, 206, 202, 198, 194, 190, 185, 181, 177, 172, 167, 162, 157, 152, 147, 142, 137, 132, 126, 121, 115, 109, 104, 98, 92, 86, 80, 74, 68, 62, 56, 50, 44, 38, 31, 25, 19, 13, 6};
uint16_t sin_num = 0;        //正弦读取计位
//锁相环
uint16_t period_AC_buff0 = 0, period_AC_buff1 = 0, period_AC = 0;        //AC周期存储
//故障标志
uint8_t error_count = 0, error_testcount = 0;      //异常计数
uint8_t error_LOCK = 0, error_FLT = 0, error_Temp = 0;      //LOCK、FLT、温度故障标志
//过程标志
uint8_t flag_timingRST = 0;      //重启尝试延时1s完成标志
uint8_t flag_PWM4 = 0;      //PWM4周期结束标志
uint8_t flag_PWM1 = 0;      //PWM1周期结束标志
//上位机信号
uint8_t host_turnon = 0;        //开机信号
uint16_t host_Ioorder = 0;      //给定恒流参考值
//PI调节参数
DATA_PI Udc_PI = {0,0,0,0};
DATA_PI Uo_PI = {0,0,0,0};
DATA_PI Io_PI = {0,0,0,0};
//恒流恒压切换
uint16_t Io_ref = 0;      //恒流模式给定值
uint8_t Uo_count = 0;       //切换电压维持计数，Uo_count>20切换
uint8_t switch_start = 0, switch_complete = 0, switch_count = 0, switch_hold = 0;        //切换开始、完成、切换延迟、电压稳定标志
//ADC采样
DATA_ADC Ug_ADC = {0,0,0,0,{0,0,0,0},0};
DATA_ADC Ig_ADC = {0,0,0,0,{0,0,0,0},0};
DATA_ADC Udc_ADC = {0,0,0,0,{0,0,0,0},0};
DATA_ADC Uo_ADC = {0,0,0,0,{0,0,0,0},0};
DATA_ADC Io_ADC = {0,0,0,0,{0,0,0,0},0};
DATA_ADC Temp_ADC = {0,0,0,0,{0,0,0,0},0};

#else

extern uint8_t T2_count, T4_count;
extern uint8_t poweron_CAN_overtime, poweron_CAN_received;
extern uint16_t sin_table[], sin_num;
extern uint16_t period_AC_buff0, period_AC_buff1, period_AC;
extern uint8_t error_count, error_testcount;
extern uint8_t error_LOCK, error_FLT, error_Temp;
extern uint8_t flag_timingRST, flag_PWM4, flag_PWM1;
extern uint8_t host_turnon;
extern uint16_t host_Ioorder;
extern DATA_PI Udc_PI, Uo_PI, Io_PI;
extern uint8_t Uo_count;
extern uint16_t Io_ref;
extern DATA_ADC Ug_ADC, Ig_ADC, Udc_ADC, Uo_ADC, Io_ADC, Temp_ADC;
extern uint8_t switch_start, switch_complete, switch_count, switch_hold;  

#endif

#include "module_CAN.h"
#include "module_Timer.h"
#include "module_ADC.h"
#include "module_IC.h"
#include "module_PWM.h"
#include "process_state.h"
#include "process_update.h"
#include "process_PIcontrol.h"


#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_GLOBAL_H */

