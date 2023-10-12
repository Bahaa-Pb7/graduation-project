/* 
 * File:   PID.h
 * Author: mohamedsultan
 *
 * Created on 10 ??????, 2023, 01:42 ?
 */

#ifndef PID_H
#define	PID_H


typedef struct
{  
    double target ;
    double actual ;
    double Kp;
    double Ki;
    double Kd;
}PID_t;
double PID_control(PID_t *obj);



#endif	/* PID_H */

