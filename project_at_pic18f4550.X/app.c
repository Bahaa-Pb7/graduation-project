/* 
 * File:   app.c
 * Author: mohamedsultan
 *
 * Created on 20 ?????, 2023, 02:10 ?
 */


#include "MCAL_Layer/ECCP/hal_ECCP.h"
#include"MCAL_Layer/ADC/hal_adc.h"
#include "ECU_Layer/Sensor/current/current_sensor.h"


int res=0.0;
int main() {

currant_sensor_init(CHANNEL_AN0);
    while(1)
    {

     res=(int)Read_currant_sensor(1.0);
        
   
        
        
       
    }
    
    
    
    
    
    return (EXIT_SUCCESS);
}

