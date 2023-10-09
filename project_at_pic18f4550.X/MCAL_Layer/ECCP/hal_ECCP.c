/* 
 * File:   hal_ECCP.C
 * Author: mohamedsultan
 *
 * Created on 15 ?????, 2023, 07:45 ?
 */


#include "hal_ECCP.h"
static void Eccp_pin_config(const eccp_t * eccp_obj);
static void Eccp_set_freq(const eccp_t * eccp_obj);
static void Eccp_timer_2 (const eccp_t * eccp_obj);

Std_ReturnType ECCP_Init(const eccp_t * eccp_obj)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL == eccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
      ECCP_mode(ECCP_MODULE_DISABLE); 
      
      if (eccp_obj->mode_selected ==PWM)
      {
          
         
          Eccp_set_freq(eccp_obj);
          PWM_MODE(eccp_obj->pwm_mode); 
          ECCP_Set_duty(eccp_obj->duty_init);
          Eccp_DeadTime(eccp_obj->dead_time);
          Eccp_timer_2(eccp_obj);
          Eccp_pin_config(eccp_obj);
           ECCP_mode(eccp_obj->eccp_mode); 
      }
      else if (eccp_obj->mode_selected ==Capture)
      {
          /* code */
      }
      else if (eccp_obj->mode_selected ==Compare)
      {
            /* code */
      }
      else 
      { }
      
      
        
        
        
    }
    
    
    return ret;
}
Std_ReturnType ECCP_Set_duty( uint8 duty)
{
    Std_ReturnType ret = E_OK;
    uint16 _duty_temp=0;
    
   
        
        _duty_temp= (uint16)(4*(PR2 +1)*(duty / 100.0));
        
         CCP1CONbits.DC1B = _duty_temp & 0x0003;
        CCPR1L  = (uint8) (_duty_temp>>2);
        
    
    
    
    return ret;
}





static void Eccp_pin_config(const eccp_t * eccp_obj)
{
    
    
        if( Single_output == eccp_obj->pwm_mode)
        {
            
            pin_config_t P1A=
              {
                .direction=GPIO_DIRECTION_OUTPUT,
                .pin=PIN2,
                .port=PORTC_INDEX
              };
           
            gpio_pin_intialize(&P1A);
        } 
            
            
        else if(  Full_bridge_output_forward == eccp_obj->pwm_mode)
        {
            // PWM_MODE(eccp_obj->pwm_mode);
                
           pin_config_t P1A=
             {
               .direction=GPIO_DIRECTION_OUTPUT,
               .pin=PIN2,
               .port=PORTC_INDEX
             };
           
           pin_config_t P1B=
             {
               .direction=GPIO_DIRECTION_OUTPUT,
               .pin=PIN5,
               .port=PORTD_INDEX
             };
           
           
            pin_config_t P1C=
             {
               .direction=GPIO_DIRECTION_OUTPUT,
               .pin=PIN6,
               .port=PORTD_INDEX
             };
            
            pin_config_t P1D=
             {
               .direction=GPIO_DIRECTION_OUTPUT,
               .pin=PIN7,
               .port=PORTD_INDEX
             };
            
           gpio_pin_intialize(&P1A);
           gpio_pin_intialize(&P1B);
           gpio_pin_intialize(&P1C);
           gpio_pin_intialize(&P1D);
      
        }  
        else if (  Half_bridge_output == eccp_obj->pwm_mode)
        {
            
          // PWM_MODE(eccp_obj->pwm_mode);
                
           pin_config_t P1A=
             {
               .direction=GPIO_DIRECTION_OUTPUT,
               .pin=PIN2,
               .port=PORTC_INDEX
             };
           
           pin_config_t P1B=
             {
               .direction=GPIO_DIRECTION_OUTPUT,
               .pin=PIN5,
               .port=PORTD_INDEX
             };
           gpio_pin_intialize(&P1A);
           gpio_pin_intialize(&P1B);
           
         
           
           
        }
        else if (  Full_bridge_output_reverse == eccp_obj->pwm_mode)
        {
            //PWM_MODE(eccp_obj->pwm_mode);

           pin_config_t P1A=
             {
               .direction=GPIO_DIRECTION_OUTPUT,
               .pin=PIN2,
               .port=PORTC_INDEX
             };
           
           pin_config_t P1B=
             {
               .direction=GPIO_DIRECTION_OUTPUT,
               .pin=PIN5,
               .port=PORTD_INDEX
             };
           
           
            pin_config_t P1C=
             {
               .direction=GPIO_DIRECTION_OUTPUT,
               .pin=PIN6,
               .port=PORTD_INDEX
             };
            
            pin_config_t P1D=
             {
               .direction=GPIO_DIRECTION_OUTPUT,
               .pin=PIN7,
               .port=PORTD_INDEX
             };
            
           gpio_pin_intialize(&P1A);
           gpio_pin_intialize(&P1B);
           gpio_pin_intialize(&P1C);
           gpio_pin_intialize(&P1D);
        
        }
        else 
        {  }
   
   
    
}


static void Eccp_set_freq(const eccp_t * eccp_obj)
{
    /*
     PWM Period = [(PR2) + 1] ? 4 ? TOSC ?  (TMR2 Prescale Value)  
    */
    PR2=(uint8)((_XTAL_FREQ/(eccp_obj->freq*4.0*(eccp_obj->timer2_postscaler_value +1)*(eccp_obj->timer2_prescaler_value +1)))-1);

}



static void Eccp_timer_2 (const eccp_t * eccp_obj)
{
   PIR1bits.TMR2IF=0;
     timer2_t timer_obj={
        .timer2_postscaler_value=eccp_obj->timer2_postscaler_value,
        .timer2_preload_value=0,
        .timer2_prescaler_value=eccp_obj->timer2_prescaler_value  
    };
    
    
    Timer2_Init(&timer_obj);
    while(PIR1bits.TMR2IF==0);
}
Std_ReturnType  Eccp_DeadTime(uint8 time)
{
   /*   Delay = 4 * TOSC * (PWM1CON<6:0>)    */ 
    
    //PWM1CON = (4*(1/_XTAL_FREQ)) / time ;
    
    ECCP1DEL=time;
    
    
}