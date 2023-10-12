/* 
 * File:   app.c
 * Author: mohamedsultan
 *
 * Created on 20 ?????, 2023, 02:10 ?
 */


#include "MCAL_Layer/ECCP/hal_ECCP.h"
#include"MCAL_Layer/ADC/hal_adc.h"
#include "ECU_Layer/Sensor/current/current_sensor.h"
#include "helper/PID_control/PID.h"
#include "helper/helper_function.h"




eccp_t eccp_obj={
  .dead_time= 0 ,
  .mode_selected=PWM,
  .eccp_mode = ECCP_PWM_MODE_P1A_P1C_active_high_P1B_P1D_active_high,
  .freq=20000,
  .pwm_mode=Half_bridge_output,
  .timer2_postscaler_value= TIMER2_POSTSCALER_DIV_BY_1,
  .timer2_prescaler_value=TIMER2_PRESCALER_DIV_BY_1,
  .duty_init=50,
  
};

double res=0.0;
int main() {
    
    PID_t pid_obj={
      .Kd=0,
      .Ki=0,
      .Kp=30,
      .target=2.0,
      .max_PID_value=100,
      .min_PID_value=0
    };
ECCP_Init(&eccp_obj);
ECCP_Set_duty(50);
Eccp_DeadTime(0);
currant_sensor_init(CHANNEL_AN0);
    while(1)
    {
       pid_obj.actual=Read_currant_sensor(1.0);

       pid_obj.actual=Read_currant_sensor(1.0);
       double pid=PID_control(&pid_obj);
       
       int val=(int)map(pid,0,100,63,0);
       Eccp_DeadTime(val);     // 0->1023   to 0 -> 63
   
        
        
       
    }
    
    
    
    
    
    return (EXIT_SUCCESS);
}

