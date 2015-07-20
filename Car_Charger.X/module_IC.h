/* 
 * File:   module_IC.h
 * Author: H2
 *
 * Created on 2015年7月17日, 下午5:24
 */

#ifndef MODULE_IC_H
#define	MODULE_IC_H

#ifdef	__cplusplus
extern "C" {
#endif

    void initIC();
    void __attribute__((__interrupt__, no_auto_psv)) _IC1Interrupt();
    void __attribute__((__interrupt__, no_auto_psv)) _IC2Interrupt();
    void __attribute__((__interrupt__, no_auto_psv)) _IC3Interrupt();

#ifdef	__cplusplus
}
#endif

#endif	/* MODULE_IC_H */

