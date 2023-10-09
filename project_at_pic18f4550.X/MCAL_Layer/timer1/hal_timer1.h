/* 
 * File:   hal_timer1.h
 * Author: mohamedsultan
 *
 * Created on 30 ?????, 2023, 12:38 ?
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/*------------------ Includs ------------------*/
#include "pic18f4550.h"
#include "../mcal_std_type.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* -------------------Macro Declarations ---------------*/




#define TIMER1_TIMER_MODE              0
#define TIMER1_COUNTER_MODE            1


#define TIMER1_ASYNC_COUNTER_MODE      1
#define TIMER1_SYNC_COUNTER_MODE       0

#define  TIMER1_OSCILLATOR_ENABLE       1
#define  TIMER1_OSCILLATOR_DISABLE      0


#define TIMER1_PRESCALER_DIV_BY_1      0
#define TIMER1_PRESCALER_DIV_BY_2      1
#define TIMER1_PRESCALER_DIV_BY_4      2
#define TIMER1_PRESCALER_DIV_BY_8      3


#define TIMER1_8BIT_REFISTER_RW_MODE      0
#define TIMER1_16BIT_REFISTER_RW_MODE     1


/* ------------------- Macro Function Declarations ------------------*/

#define TIMER1_MODULE_ENABLE()                       (T1CONbits.TMR1ON=1)
#define TIMER1_MODULE_DISABLE()                      (T1CONbits.TMR1ON=0)

#define TIMER1_TIMER_MODE_ENABLE()                   (T1CONbits.TMR1CS=0)
#define TIMER1_COUNTER_MODE_ENABLE()                 (T1CONbits.TMR1CS=1)


#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()           (T1CONbits.T1SYNC=1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()            (T1CONbits.T1SYNC=0)



#define  TIMER1_OSC_HW_ENABLE()                      (T1CONbits.T1OSCEN=1)
#define  TIMER1_OSC_HW_DISABLE()                     (T1CONbits.T1OSCEN=0)



#define  TIMER1_PRESCALER_SELECT(_PRESCALER_)       (T1CONbits.T1CKPS=_PRESCALER_)

#define  TIMER1_SYSTEM_CLK_STATUS()                 (T1CONbits.T1RUN)



#define TIMER0_8BIT_REFISTER_RW_ENABLE()            (T1CONbits.RD16=0)  
#define TIMER0_16BIT_REFISTER_RW_ENABLE()           (T1CONbits.RD16=1)    



/* ------------------- Data Type -------------------*/



typedef struct{
     #if TIMER1_INTERRUPT_PEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*TMR1_InterruptHandler)(void);
    interrupt_priority_cfg  priority;
    #endif
     uint16 timer1_preload_value;
     uint8 timer1_prescaler_value :2 ;
     uint8 timer1_mode :1 ;
     uint8 timer1_conuter_mode :1 ;
     uint8 timer1_osc_cfg :1 ;
     uint8 timer1_reg_RW_mode :1 ;
     uint8 timer0_reserved : 2;
      
}timer1_t;

/* --------------------Software Interfaces Declarations ----------------------*/
Std_ReturnType Timer1_Init(const timer1_t * _timer);
Std_ReturnType Timer1_DeInit(const timer1_t * _timer);
Std_ReturnType Timer1_Write_Value(const timer1_t * _timer,uint16 _value);
Std_ReturnType Timer1_Read_Value(const timer1_t * _timer,uint16 *_value);


#endif	/* HAL_TIMER1_H */

