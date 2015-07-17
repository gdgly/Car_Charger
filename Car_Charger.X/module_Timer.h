/* 
 * File:   module_Timer.h
 * Author: H2
 *
 * Created on 2015年7月17日, 下午5:22
 */

#ifndef MODULE_TIMER_H
#define	MODULE_TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

    void initTimer2();
    void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt();
    void initTimer();

#ifdef	__cplusplus
}
#endif

#endif	/* MODULE_TIMER_H */

