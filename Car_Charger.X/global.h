/* 
 * File:   global.h
 * Author: H2
 *
 * Created on 2015年7月17日, 下午4:55
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "system_config.h"
    unsigned int T2N = 50;          //定时器2循环计数次数，T2N*0.2s=10s
    unsigned int PowerOnCANOverTime = 0;     //上电等待上位机信号超时标志
    unsigned int PowerOnCANReceived = 0;     //上电接收上位机信号完成标志
    unsigned int IRef = 0;
#include "module_CAN.h"
#include "module_Timer.h"
#include "module_ADC.h"
#include "module_IC.h"
#include "module_PWM.h"
    
#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_H */

