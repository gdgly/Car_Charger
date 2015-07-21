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

#define PORT_OUTCONNECT PORTDbits.RD11      //电池反接检测口
#define PORT_RDY PORTAbits.RA3              //硬件就绪口
#define PORT_OPENPWM LATAbits.LATA15        //PWM封锁
#define PORT_OUTREVIND LATFbits.LATF2       //电池反接指示
#define PORT_RST LATDbits.LATD10            //封锁复位

typedef struct{
    uint16_t mean;
} ADC_DATA;
    
#ifdef MAIN

uint8_t T2_count = 50;          //定时器2循环计数次数，50*0.2s=10s
uint8_t T4_count = 5;           //定时器4循环计数次数，50*0.2s=10s
uint8_t poweron_CAN_overtime = 0;     //上电等待上位机信号超时标志
uint8_t poweron_CAN_received = 0;     //上电接收上位机信号完成标志
uint8_t I_ref = 0, I_ref0 = 0;
uint16_t sin_table[] = {0,8,16,24,32,40,47,55,63,71,79,86,94,101,108,116,123,130,137,143,150,156,163,169,175,181,186,192,197,202,207,211,216,220,224,228,231,234,238,240,243,245,247,249,251,252,253,254,255,255,256,255,255,254,253,252,251,249,247,245,243,240,238,234,231,228,224,220,216,211,207,202,197,192,186,181,175,169,163,156,150,143,137,130,123,116,108,101,94,86,79,71,63,55,47,40,32,24,16,8,0};
uint16_t sin_num = 0;        //正弦读取计位
uint16_t period_AC_buff0 = 0, period_AC_buff1 = 0, period_AC = 0;        //AC周期存储
uint8_t error_count = 0;      //异常计数
uint8_t error_LOCK = 0, error_FLT = 0, error_temp = 0;      //LOCK、FLT、温度故障标志
uint8_t flag_timingRST = 0;      //重启尝试延时1s完成标志
uint8_t host_trunon = 0;        //上位机信号

ADC_DATA Ug, Io;

#else

extern uint8_t T2_count;
extern uint8_t T4_count;
extern uint8_t poweron_CAN_overtime;
extern uint8_t poweron_CAN_received;
extern uint8_t I_ref, I_ref0;
extern uint16_t sin_table[];
extern uint16_t sin_num;
extern uint16_t period_AC_buff0, period_AC_buff1, period_AC;
extern uint8_t error_count;
extern uint8_t error_LOCK, error_FLT, error_temp;
extern uint8_t flag_timingRST;
extern uint8_t host_trunon;
extern ADC_DATA Ug, Io;

#endif


#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_GLOBAL_H */

