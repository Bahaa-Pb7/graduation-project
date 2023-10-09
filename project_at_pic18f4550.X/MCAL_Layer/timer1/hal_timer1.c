/* 
 * File:   hal_timer1.c
 * Author: mohamedsultan
 *
 * Created on 30 ?????, 2023, 12:38 ?
 */


#include "hal_timer1.h"



static inline void Timer1_Mode_Select(const timer1_t * _timer);

#if TIMER0_INTERRUPT_PEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(*TMR1_InterruptHandler)(void)=NULL;

#endif

static uint16 timer1_preload=0;

Std_ReturnType Timer1_Init(const timer1_t * _timer)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL==_timer)
    {
         ret = E_NOT_OK;
    }
    else
    {
        TIMER1_MODULE_DISABLE();
        
        TIMER1_PRESCALER_SELECT(_timer->timer1_prescaler_value);
        Timer1_Mode_Select(_timer);
         TMR1H=(_timer->timer1_preload_value)>>8;
         TMR1L=(uint8)(_timer->timer1_preload_value);
        timer1_preload= _timer->timer1_preload_value;
        
        
        
#if TIMER0_INTERRUPT_PEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
              
            TIMER1_INTERRUPT_ENABLE();
            TIMER1_INTERRUPT_FLAG_CLEAR();
           TMR1_InterruptHandler  = _timer->TMR1_InterruptHandler;
        
        
        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE    
        
          INTERRUPT_PriorityLevelEnable();
         if(INTERRUPT_LOW_PRIORITY==_timer->priority)
         {
             TIMER1_LowPrioritySet();
             INTERRUPT_GLOBALIntruuptLowEnable();
         }
         else if(INTERRUPT_HIGH_PRIORITY==_timer->priority)
         {
             INTERRUPT_GLOBALIntruuptHighEnable();
             TIMER1_HighPrioritySet();
         }
         
#else
         INTERRUPT_GLOBALIntruuptEnable();
         INTERRUPT_PeripheralIntruuptEnable();
#endif       
        
#endif

        TIMER1_MODULE_ENABLE();
        
    }
    
    
    
    
    return ret;
}
Std_ReturnType Timer1_DeInit(const timer1_t * _timer)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL==_timer)
    {
         ret = E_NOT_OK;
    }
    else
    {
        TIMER1_MODULE_DISABLE();
        
#if TIMER0_INTERRUPT_PEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
              
            TIMER1_INTERRUPT_DISABLE();
    
#endif
    
    }
    
    
    
    
    return ret;   
}
Std_ReturnType Timer1_Write_Value(const timer1_t * _timer,uint16 _value)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL==_timer)
    {
         ret = E_NOT_OK;
    }
    else
    {
    
    TMR1H=(_value)>>8;
    TMR1L=(uint8)(_value);
    
    }
    
    
    
    
    return ret;   
}
Std_ReturnType Timer1_Read_Value(const timer1_t * _timer,uint16 *_value)
{
    Std_ReturnType ret = E_OK;
      uint8 tmr1L=0 , tmr1H=0;
    if ((NULL==_timer)|| (NULL==_value))
    {
         ret = E_NOT_OK;
    }
    else
    {
      tmr1L=TMR1L;
      tmr1H=TMR1H;
       
     *_value= (uint16)((tmr1H<<8)  + tmr1L );
    
    
    }
    
    
    
    
    return ret;   
}




void TMR1_ISR(void)
{
    #if TIMER0_INTERRUPT_PEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    TIMER0_INTERRUPT_FLAG_CLEAR();
    TMR0H=(timer1_preload)>>8;
    TMR0L=(uint8)(timer1_preload);
    
    if(TMR1_InterruptHandler)
    {
        TMR1_InterruptHandler();
    }
#endif
}



static inline void Timer1_Mode_Select(const timer1_t * _timer)
{
    if(TIMER1_TIMER_MODE == _timer->timer1_mode)
    {
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if(TIMER1_COUNTER_MODE == _timer->timer1_mode)
    {
        TIMER1_COUNTER_MODE_ENABLE();
        
        if(TIMER1_ASYNC_COUNTER_MODE == _timer->timer1_conuter_mode)
        {
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if (TIMER1_SYNC_COUNTER_MODE == _timer->timer1_conuter_mode)
        {
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
        else{/*Nothing*/}
    }
        else{/*Nothing*/}
    
   
}