/* 
 * File:   current_sensor.h
 * Author: mohamedsultan
 *
 * Created on 09 ??????, 2023, 11:49 ?
 */

#include "current_sensor.h"

static adc_conf_t adc={
    
                  
                  .adc_channel=ADC_CHANNEL_AN0,
                   .acquisition_time=ADC_12_TAD,
                  .conversion_clock=ADC_CONVERSION_CLOCK_FOSC_DIV_16,
                  .result_format=ADC_RESULT_RIGHT,
                  .voltage_reference=ADC_VOLTAGE_REFERENCE_DISABLED,
                  
};


Std_ReturnType currant_sensor_init(channel_select_t channal){
    Std_ReturnType ret = E_NOT_OK;
    adc.adc_channel=channal;
}

double Read_currant_sensor(double scale)
{
    uint16 res=0;
    double volt=0.0;
    double Mile_volt_without_base=0.0;
    double current=0.0;
    ADC_GetConversion_Blocking(&adc,adc.adc_channel,&res);
    volt=(res*5.0)/1023.0;
    Mile_volt_without_base=(volt-2.5)*1000.0;
    current=Mile_volt_without_base/66.0;
    current = current * scale;
    
    
    
    
    return current;
}