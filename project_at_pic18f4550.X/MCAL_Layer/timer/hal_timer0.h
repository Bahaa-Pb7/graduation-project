/* 
 * File:   hal_timer0.h
 * Author: mohamedsultan
 *
 * Created on 24 ?????, 2023, 01:58 ?
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H



/*------------------ Includs ------------------*/
#include "pic18f4550.h"
#include "../mcal_std_type.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/* -------------------Macro Declarations ---------------*/

#define TIMER0_PERSCALER_ENABLE_CFG    1
#define TIMER0_PERSCALER_DISABLE_CFG   0

#define TIMER0_RISING_EDGE_ENABLE_CFG  1
#define TIMER0_FALLING_EDGE_ENABLE_CFG 0

#define TIMER0_TIMER_MODE              1
#define TIMER0_COUNTER_MODE            0

#define TIMER0_8BIT_REFISTER_MODE      1
#define TIMER0_16BIT_REFISTER_MODE     0


/* ------------------- Macro Function Declarations ------------------*/

#define TIMER0_PRESCALER_ENABLE()      (T0CONbits.PSA=0)
#define TIMER0_PRESCALER_DISABLE()     (T0CONbits.PSA=1)

#define TIMER0_RISING_EDGE_ENABLE()    (T0CONbits.T0SE=0)
#define TIMER0_FALLING_EDGE_ENABLE()   (T0CONbits.T0SE=1)


#define TIMER0_TIMER_MODE_ENABLE()     (T0CONbits.T0CS=0)
#define TIMER0_COUNTER_MODE_ENABLE()   (T0CONbits.T0CS=1)

#define TIMER0_8BIT_REFISTER_MODE_ENABLE()  (T0CONbits.T08BIT=1)  
#define TIMER0_16BIT_REFISTER_MODE_ENABLE() (T0CONbits.T08BIT=0)    

#define TIMER0_MODULE_ENABLE()   (T0CONbits.TMR0ON=1)
#define TIMER0_MODULE_DISABLE()  (T0CONbits.TMR0ON=0)

/* ------------------- Data Type -------------------*/

typedef enum {
    TIMER0_PRESCALER_DIV_BY_2=0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256
    
} timer0_prescaler_select_t;


typedef struct{
    #if TIMER0_INTERRUPT_PEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*TMR0_InterruptHandler)(void);
    interrupt_priority_cfg  priority;
    #endif
    uint16 timer0_preload_value;
    timer0_prescaler_select_t prescaler_value;
    uint8 prescaler_enable :1 ;
    uint8 timer0_counter_edge :1 ;
    uint8 timer0_mode :1 ;
    uint8 timer0_register_size :1;
    uint8 timer0_reserved : 4;
    
 
            
}timer0_t;

/* --------------------Software Interfaces Declarations ----------------------*/
Std_ReturnType Timer0_Init(const timer0_t * _timer);
Std_ReturnType Timer0_DeInit(const timer0_t * _timer);
Std_ReturnType Timer0_Write_Value(const timer0_t * _timer,uint16 _value);
Std_ReturnType Timer0_Read_Value(const timer0_t * _timer,uint16 *_value);


#endif	/* HAL_TIMER0_H */

