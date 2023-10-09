/* 
 * File:   hal_timer0.c
 * Author: mohamedsultan
 *
 * Created on 24 ?????, 2023, 01:58 ?
 */

#include "hal_timer0.h"

static inline Std_ReturnType Timer0_Prescaler_Config(const timer0_t * _timer);
static inline void Timer0_Mode_Select(const timer0_t * _timer);
static inline void Timer0_Register_Size_Config(const timer0_t * _timer);
#if TIMER0_INTERRUPT_PEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(*TMR0_InterruptHandler)(void)=NULL;

#endif

static uint16 timer0_preload=0;

Std_ReturnType Timer0_Init(const timer0_t * _timer)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == _timer)
        
    {
        ret=E_NOT_OK;
    }
    else 
    {
       TIMER0_MODULE_DISABLE();
       Timer0_Prescaler_Config(_timer);
       Timer0_Mode_Select(_timer);
       Timer0_Register_Size_Config(_timer);
       TMR0H=(_timer->timer0_preload_value)>>8;
       TMR0L=(uint8)(_timer->timer0_preload_value);
       
       timer0_preload= _timer->timer0_preload_value;
#if TIMER0_INTERRUPT_PEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            
            TIMER0_INTERRUPT_ENABLE();
            TIMER0_INTERRUPT_FLAG_CLEAR();
         TMR0_InterruptHandler  = _timer->TMR0_InterruptHandler;
         
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
         
         INTERRUPT_PriorityLevelEnable();
         if(INTERRUPT_LOW_PRIORITY==_timer->priority)
         {
             TIMER0_LowPrioritySet();
             INTERRUPT_GLOBALIntruuptLowEnable();
         }
         else if(INTERRUPT_HIGH_PRIORITY==_timer->priority)
         {
             INTERRUPT_GLOBALIntruuptHighEnable();
             TIMER0_HighPrioritySet();
         }
         
#else
         INTERRUPT_GLOBALIntruuptEnable();
         INTERRUPT_PeripheralIntruuptEnable();
 #endif
 #endif

         TIMER0_MODULE_ENABLE() ;
    }
    
    
    return ret;
}
Std_ReturnType Timer0_DeInit(const timer0_t * _timer)
{
      Std_ReturnType ret = E_OK;
    
    if(NULL == _timer)
        
    {
        ret=E_NOT_OK;
    }
    else 
    {
         TIMER0_MODULE_DISABLE();
        #if TIMER0_INTERRUPT_PEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

        TIMER0_INTERRUPT_DISABLE();
        
        #endif
    }
    
    
    return ret;
}
Std_ReturnType Timer0_Write_Value(const timer0_t * _timer,uint16 _value)
{
      Std_ReturnType ret = E_OK;
    
    if((NULL == _timer))
        
    {
        ret=E_NOT_OK;
    }
    else 
    {
       TMR0H=(_value)>>8;
       TMR0L=(uint8)(_value);
    }
    
    
    return ret;
}
Std_ReturnType Timer0_Read_Value(const timer0_t * _timer,uint16 *_value)
{
         Std_ReturnType ret = E_OK;
         uint8 tmr0L=0 , tmr0H=0;
    
    if((NULL == _timer) || (NULL == _value))
        
    {
        ret=E_NOT_OK;
    }
    else 
    {
        
       tmr0L=TMR0L;
       tmr0H=TMR0H;
       
       *_value= (uint16)((tmr0H<<8)  + tmr0L );
        
    }
    
    
    return ret;
}

void TMR0_ISR(void)
{
    #if TIMER0_INTERRUPT_PEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    TIMER0_INTERRUPT_FLAG_CLEAR();
    TMR0H=(timer0_preload)>>8;
    TMR0L=(uint8)(timer0_preload);
    
    if(TMR0_InterruptHandler)
    {
        TMR0_InterruptHandler();
    }
#endif
}
static inline Std_ReturnType Timer0_Prescaler_Config(const timer0_t * _timer)
{
      Std_ReturnType ret = E_OK;
    
    if((NULL == _timer))
        
    {
        ret=E_NOT_OK;
    }
    else 
    {
        if ( TIMER0_PERSCALER_ENABLE_CFG ==_timer->prescaler_enable)
        {
            TIMER0_PRESCALER_ENABLE();
            T0CONbits.T0PS=_timer->prescaler_value;
            
        }
        else if( TIMER0_PERSCALER_DISABLE_CFG ==_timer->prescaler_enable)
        {
            TIMER0_PRESCALER_DISABLE();
        }
        else{}
        
    }
    
    
    return ret;
}

static inline void Timer0_Mode_Select(const timer0_t * _timer)
{
    if(TIMER0_TIMER_MODE == _timer->timer0_mode)
    {
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if(TIMER0_COUNTER_MODE == _timer->timer0_mode)
    {
        TIMER0_COUNTER_MODE_ENABLE();
        if(TIMER0_RISING_EDGE_ENABLE_CFG==_timer->timer0_counter_edge)
        {
            TIMER0_RISING_EDGE_ENABLE();
        }
        else if(TIMER0_FALLING_EDGE_ENABLE_CFG==_timer->timer0_counter_edge)
        {
            TIMER0_FALLING_EDGE_ENABLE();
        }
        else{}
    }
    else{}
}

static inline void Timer0_Register_Size_Config(const timer0_t * _timer)
{
    if(TIMER0_8BIT_REFISTER_MODE ==_timer->timer0_register_size )
    {
        TIMER0_8BIT_REFISTER_MODE_ENABLE();
    }
    else if (TIMER0_16BIT_REFISTER_MODE ==_timer->timer0_register_size )
    {
          TIMER0_16BIT_REFISTER_MODE_ENABLE();
    }
    else{}
}