/* 
 * File:   process_state.h
 * Author: H2
 *
 * Created on 2015年7月21日, 下午7:17
 */

#ifndef PROCESS_STATE_H
#define	PROCESS_STATE_H

#ifdef	__cplusplus
extern "C" {
#endif

    void outRSTPulse();
    void stateBadConnect();
    void stateOverTemp();
    void stateLockAll();
    void stateLockLOCK();
    void stateLockFLT();
    void stateOperation();


#ifdef	__cplusplus
}
#endif

#endif	/* PROCESS_STATE_H */

