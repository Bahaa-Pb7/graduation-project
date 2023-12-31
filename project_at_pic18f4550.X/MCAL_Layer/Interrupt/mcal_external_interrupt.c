/* 
 * File:   mcal_external_interrupt.c
 * Author: mohamedsultan
 *
 * Created on 19 ?????, 2023, 10:15 ?
 */

#include "mcal_external_interrupt.h"

static void (*INT0_InterruptHandler) (void)=NULL;
static void (*INT1_InterruptHandler) (void)=NULL;
static void (*INT2_InterruptHandler) (void)=NULL;

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t * int_obj );
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t * int_obj );
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t * int_obj );
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t * int_obj );
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t * int_obj );
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t * int_obj );

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler) (void) );
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler) (void) );
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler) (void) );

static Std_ReturnType INTx_SetInterruptHandler(const interrupt_INTx_t * int_obj);



/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t * int_obj ){
    Std_ReturnType ret= E_OK;
    if(NULL==int_obj)
    {
        ret=E_NOT_OK;
    }
    else
    {
        /* Disable  this Interrupt*/
        ret=Interrupt_INTx_Disable(int_obj);
        /* Clear Interrupt flag*/
         ret=Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure External interrupt edg*/
         ret=Interrupt_INTx_Edge_Init(int_obj);
         #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
         /* Configure External interrupt Priority*/
         ret=Interrupt_INTx_Priority_Init(int_obj);
          #endif
       /* Configure External interrupt I/O pin*/
         ret=Interrupt_INTx_Pin_Init(int_obj);
       /* Configure External interrupt callBack*/
ret=INTx_SetInterruptHandler(int_obj);
        /* Enable  this Interrupt*/
        ret=Interrupt_INTx_Enable(int_obj);
    }
    
    
    return ret;
}

void INT0_ISR(void){
    EXT_INT0_InterruptFlagClear();
    
    /*code*/
    
    if(INT0_InterruptHandler)
    {
        INT0_InterruptHandler();
    }
}

void INT1_ISR(void){
    EXT_INT1_InterruptFlagClear();
    
    /*code*/
    
    if(INT1_InterruptHandler)
    {
        INT1_InterruptHandler();
    }
}
void INT2_ISR(void){
    EXT_INT2_InterruptFlagClear();
    
    /*code*/
    
    if(INT2_InterruptHandler)
    {
        INT2_InterruptHandler();
    }
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t * int_obj ){
    Std_ReturnType ret= E_OK;
    if(NULL==int_obj)
    {
        ret=E_NOT_OK;
    }
    else
    {
        ret=Interrupt_INTx_Disable(int_obj);
    }
    
    
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_INTx_t * int_obj ){
    Std_ReturnType ret= E_OK;
    if(NULL==int_obj)
    {
        ret=E_NOT_OK;
    }
    else
    {
        
    }
    
    
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_INTx_t * int_obj ){
    Std_ReturnType ret= E_OK;
    if(NULL==int_obj)
    {
        ret=E_NOT_OK;
    }
    else
    {
        
    }
    
    
    return ret;
}

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t * int_obj )
{
   Std_ReturnType ret= E_OK;
    if(NULL==int_obj)
    {
        ret=E_NOT_OK;
    }
    else
    {
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
           //INTERRUPT_GLOBALIntruuptHighEnable();
           //INTERRUPT_GLOBALIntruuptLowEnable();
        #else
                INTERRUPT_GLOBALIntruuptEnable();
                INTERRUPT_PeripheralIntruuptEnable();
        #endif
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptEnable();
                 break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptEnable();
                break;
            default:
                ret=E_NOT_OK;

        }
    }
    
    
    return ret;
}
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t * int_obj )
{
    Std_ReturnType ret= E_OK;
    if(NULL==int_obj)
    {
        ret=E_NOT_OK;
    }
    else
    {
         switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptDisable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptDisable();
                 break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptDisable();
                break;
            default:
                ret=E_NOT_OK;

        }
        
    }
    
    
    return ret;
    
}
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t * int_obj )
{
    Std_ReturnType ret= E_OK;
    if(NULL==int_obj)
    {
        ret=E_NOT_OK;
    }
    else
    {
        INTERRUPT_PriorityLevelEnable();
        switch (int_obj->source){
               
            case INTERRUPT_EXTERNAL_INT1:
                
                if(INTERRUPT_LOW_PRIORITY==int_obj->priority )
                {
                    INTERRUPT_GLOBALIntruuptLowEnable();
                    EXT_INT1_LowPrioritySet();
                }
                else if(INTERRUPT_HIGH_PRIORITY==int_obj->priority){
                   
                    
                    INTERRUPT_GLOBALIntruuptHighEnable();
                     EXT_INT1_HighPrioritySet();
                }
                else{}
                
                break;
                
            case INTERRUPT_EXTERNAL_INT2:
                if(INTERRUPT_LOW_PRIORITY==int_obj->priority )
                {
                   INTERRUPT_GLOBALIntruuptLowEnable();
                    EXT_INT2_LowPrioritySet();
                }
                else if(INTERRUPT_HIGH_PRIORITY==int_obj->priority){
                   INTERRUPT_GLOBALIntruuptHighEnable();
                   EXT_INT2_HighPrioritySet();

                }
                else{}
                break;
                
            
        }
        
    }
    
    
    return ret;
}
#endif
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t * int_obj )
{
    Std_ReturnType ret= E_OK;
    if(NULL==int_obj)
    {
        ret=E_NOT_OK;
    }
    else
    {
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                if(INTERRUPT_FALLING_EDGE==int_obj->edg)
                {
                    EXT_INT0_FallingEdgeSet();
                }
                else if (INTERRUPT_RISING_EDGE==int_obj->edg)
                {
                    EXT_INT0_RisingEdgeSet() ;
                    
                }
                else {}
                
                break;
            case INTERRUPT_EXTERNAL_INT1:
                if(INTERRUPT_FALLING_EDGE==int_obj->edg){
                    EXT_INT1_FallingEdgeSet();
                }
                else if (INTERRUPT_RISING_EDGE==int_obj->edg){
                    EXT_INT1_RisingEdgeSet() ;
                }
                else {}
                
                 break;
            case INTERRUPT_EXTERNAL_INT2:
               if(INTERRUPT_FALLING_EDGE==int_obj->edg){
                   EXT_INT2_FallingEdgeSet();
                }
                else if (INTERRUPT_RISING_EDGE==int_obj->edg){
                    EXT_INT2_RisingEdgeSet() ;
                }
                else {}
                
                break;
            default:
                ret=E_NOT_OK;

        }
    }
    
    
    return ret;
}
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t * int_obj )
{
    Std_ReturnType ret= E_OK;
    if(NULL==int_obj)
    {
        ret=E_NOT_OK;
    }
    else
    {
        ret=gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    
    
    return ret;
}

    
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t * int_obj )
{
    Std_ReturnType ret= E_OK;
    if(NULL==int_obj)
    {
        ret=E_NOT_OK;
    }
    else
    {
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptFlagClear();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                 EXT_INT1_InterruptFlagClear();
                 break;
            case INTERRUPT_EXTERNAL_INT2:
                 EXT_INT2_InterruptFlagClear();
                break;
            default:
                ret=E_NOT_OK;

        }
    }
    
}


static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler) (void) )
{
    Std_ReturnType ret = E_OK;
    if (NULL==InterruptHandler )
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT0_InterruptHandler=InterruptHandler;
    }
    
    return ret;
}
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler) (void) )
{
    Std_ReturnType ret = E_OK;
    if (NULL==InterruptHandler )
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT1_InterruptHandler=InterruptHandler;
    }
    
    return ret;
}
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler) (void) )
{
    Std_ReturnType ret = E_OK;
    if (NULL==InterruptHandler )
    {
        ret = E_NOT_OK;
    }
    else
    {
       INT2_InterruptHandler=InterruptHandler;

    }
    
    return ret;
}

static Std_ReturnType INTx_SetInterruptHandler(const interrupt_INTx_t * int_obj)
{
    Std_ReturnType ret = E_OK;
    if (NULL==int_obj )
    {
        ret = E_NOT_OK;
    }
    else
    {
          switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0:
              ret= INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1:
                 ret= INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                 break;
            case INTERRUPT_EXTERNAL_INT2:
                ret= INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            default:
                ret=E_NOT_OK;

        }
    }
        
    
    
    return ret;
}