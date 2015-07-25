/* 
 * File:   module_PWM.h
 * Author: H2
 *
 * Created on 2015年7月17日, 下午5:26
 */

#ifndef MODULE_PWM_H
#define	MODULE_PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

    void initPWM();
    void __attribute__((__interrupt__, no_auto_psv)) _PWM1Interrupt();
    void __attribute__((__interrupt__, no_auto_psv)) _PWM4Interrupt();
    void closePWMAll();
    void openPWMAll();
    void openPWM4();
    void openPWM12();

#ifdef	__cplusplus
}
#endif

#endif	/* MODULE_PWM_H */

