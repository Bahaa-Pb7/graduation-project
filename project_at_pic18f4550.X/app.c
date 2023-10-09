/* 
 * File:   app.c
 * Author: mohamedsultan
 *
 * Created on 20 ?????, 2023, 02:10 ?
 */


#include "MCAL_Layer/ECCP/hal_ECCP.h"
#include"MCAL_Layer/ADC/hal_adc.h"



adc_conf_t adc={
    
                  
                  .adc_channel=ADC_CHANNEL_AN0,
                   .acquisition_time=ADC_12_TAD,
                  .conversion_clock=ADC_CONVERSION_CLOCK_FOSC_DIV_16,
                  .result_format=ADC_RESULT_RIGHT,
                  .voltage_reference=ADC_VOLTAGE_REFERENCE_DISABLED,
                  
};
uint16 adc_res_1,adc_res_2,adc_res_3;
Std_ReturnType ret=E_OK;


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


#include"ECU_Layer/LED/ecu_led.h"
led_t led_1={
  .pin=PIN2,
.port_name=PORTD_INDEX  
};

int main() {
    led_initialize(&led_1);
ret=ADC_Init(&adc);
ECCP_Init(&eccp_obj);
ECCP_Set_duty(50);
 Eccp_DeadTime(0);

    while(1)
    {
       ret=ADC_GetConversion_Blocking(&adc,ADC_CHANNEL_AN0,&adc_res_1);
      Eccp_DeadTime((uint8)(adc_res_1/40));  // 0->1023   to 0 -> 63
       //ECCP_Set_duty((uint8)(adc_res_1/12));  // 0->1023   to 0 -> 25
    led_toggle(&led_1);
    __delay_ms(1000);
     
        
   
        
        
       
    }
    
    
    
    
    
    return (EXIT_SUCCESS);
}

