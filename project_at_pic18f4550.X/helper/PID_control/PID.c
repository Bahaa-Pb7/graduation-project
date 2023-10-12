/* 
 * File:   PID.h
 * Author: mohamedsultan
 *
 * Created on 10 ??????, 2023, 01:42 ?
 */



#include "PID.h"


double PID_control(PID_t *obj)
{
    double error= obj->target  -  obj->actual ;
    
    static double  prev_error=0;
    double res=0.0;
    double P=error * obj->Kp;
    static double I=0.0;
    double D=(error-prev_error)*obj->Kd;
    
    
    I=I+(error*obj->Ki);
    
    res=I+D+P;
  
    prev_error=error;
    
    if(res>obj->max_PID_value)
    {
        res=obj->max_PID_value;
    }
    else if(res<obj->min_PID_value)
    {
        res=obj->min_PID_value;
    }
    
    
    return res;
}
