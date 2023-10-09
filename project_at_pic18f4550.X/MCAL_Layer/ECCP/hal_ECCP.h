/* 
 * File:   hal_ECCP.h
 * Author: mohamedsultan
 *
 * Created on 15 ?????, 2023, 07:45 ?
 */

#ifndef HAL_ECCP_H
#define	HAL_ECCP_H

/* ----------------- Includes -----------------*/
#include "pic18f4550.h"
#include "../mcal_std_type.h"
#include "../GPIO/hal_gpio.h"
#include "../Timer2/hal_timr2.h"
#include "../device_config.h"

/* ----------------- Macro Declarations -----------------*/


                    /* ECCP_mode  */
#define  ECCP_MODULE_DISABLE                                                         ((uint8)0b00000000)
#define  ECCP_PWM_MODE_P1A_P1C_active_high_P1B_P1D_active_high                       ((uint8)0b00001100)
#define  ECCP_PWM_MODE_P1A_P1C_active_high_P1B_P1D_active_low                        ((uint8)0b00001101)
#define  ECCP_PWM_MODE_P1A_P1C_active_low_P1B_P1D_active_high                        ((uint8)0b00001110)
#define  ECCP_PWM_MODE_P1A_P1C_active_low_P1B_P1D_active_low                         ((uint8)0b00001111)





/* ----------------- Macro Functions Declarations -----------------*/

#define PWM_MODE(CONFIG)       (CCP1CONbits.P1M=CONFIG)
#define ECCP_mode(CONFIG)      (CCP1CONbits.CCP1M=CONFIG) 



/* ----------------- Data Type Declarations -----------------*/
typedef enum{
   Single_output=0,
   Full_bridge_output_forward,
   Half_bridge_output,
   Full_bridge_output_reverse
}pwm_mode_t; 
typedef enum{
   PWM=0,
   Capture,
   Compare,
  
}ECCP_mode_selected; 


typedef struct{

    
uint8 eccp_mode;    
pwm_mode_t pwm_mode;
uint8 dead_time;
uint32 freq;
uint8 timer2_postscaler_value;
uint8 timer2_prescaler_value;
ECCP_mode_selected mode_selected ;
uint8 duty_init;
}eccp_t;




/* ----------------- Software Interfaces Declarations -----------------*/

Std_ReturnType ECCP_Init(const eccp_t * eccp_obj);
Std_ReturnType ECCP_Set_duty(uint8 duty);
Std_ReturnType  Eccp_DeadTime(uint8 time);

#endif	/* HAL_ECCP_H */

