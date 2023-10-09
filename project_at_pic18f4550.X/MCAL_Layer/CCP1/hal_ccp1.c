/* 
 * File:   hal_ccp1.h
 * Author: mohamedsultan
 *
 * Created on 03 ?????, 2023, 07:33 ?
 */



/*------------------ Includs ------------------*/
#include "hal_ccp1.h"



static void ccp_Interrupt_Config(const ccp_t * _ccp_obj);
static void CCP_PWM_Mode_Config(const ccp_t * _ccp_obj);
static void ccp_Capture_Mode_Timer_Select(const ccp_t * _ccp_obj);

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(*CCP1_InterruptHandler)(void)=NULL;

#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(*CCP2_InterruptHandler)(void)=NULL;

#endif

Std_ReturnType  CCP_Init(const ccp_t * _ccp_obj)
{
    Std_ReturnType ret=E_OK;
    
    if(NULL == _ccp_obj)
    {
        ret=E_NOT_OK;
        
    }
    else
    {
          if(_ccp_obj->ccp_inst ==CCP1_INST)
          {
             CCP1_SET_MODE(CCP_MODULE_DISABLE);
          }
          
          else if (_ccp_obj->ccp_inst ==CCP2_INST)
          {
               CCP2_SET_MODE(CCP_MODULE_DISABLE);
          }
        if(CCP_CFG_CAPTURE_MODE_SELECTED ==_ccp_obj->ccp_mode )
        {
            ccp_Capture_Mode_Timer_Select(_ccp_obj);
            switch(_ccp_obj ->ccp_mode_variant)
            {
                
                case CCP_CAPTURE_MODE_1_FALLING_EDGE:
                     CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); 
                     break;
                
                case CCP_CAPTURE_MODE_1_RISING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE); 
                     break;
                     
                case CCP_CAPTURE_MODE_4_RISING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE); 
                     break;
                     
                 case CCP_CAPTURE_MODE_16_RISING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); 
                     break;
                     
                default : ret=E_NOT_OK;
            }
             
            
            
        }
            
        else if (CCP_CFG_COMPARE_MODE_SELECTED == _ccp_obj->ccp_mode)
        {
            switch(_ccp_obj ->ccp_mode_variant){
                
                case CCP_COMPARE_MODE_SET_PIN_LOW:
                     CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW); 
                     break;
                
                case CCP_COMPARE_MODE_SET_PIN_HIGH:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH); 
                     break;
                     
                case CCP_COMPARE_MODE_TOGGEL_ON_MATCH:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGEL_ON_MATCH); 
                     break;
                     
                 case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); 
                     break;
                  case CCP_COMPARE_MODE_GEN_EVENT:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT); 
                     break;    
                default : ret=E_NOT_OK;
            }
            
            
        }
        else if(CCP_CFG_PWM_MODE_SELECTED==_ccp_obj->ccp_mode)
        {
                  CCP_PWM_Mode_Config(_ccp_obj);
        }
        else
        {    
              ret=E_NOT_OK;
        
        }
        
        
    }
    
    /* pin configration */
     ret=gpio_pin_intialize(&(_ccp_obj->pin));
     
     /*Interrupt Configration */
     ccp_Interrupt_Config(_ccp_obj);
         
         
         
    return ret;

}
Std_ReturnType  CCP_DeInit(const ccp_t * _ccp_obj)
{
    Std_ReturnType ret=E_OK;
    
    if(NULL == _ccp_obj)
    {
        ret=E_NOT_OK;
        
    }
    else
    {
        CCP1_SET_MODE(CCP_MODULE_DISABLE);
        
 #if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
CCP1_InterruptDisable();
#endif
        
    }
    
    return ret;
    
}

#if CCP_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED
   
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t * _ccp_obj ,const uint8 _duty)
{
      Std_ReturnType  ret=E_OK;
   
   if(NULL==_ccp_obj)
   {
       ret=E_NOT_OK;
   }
   else
   {
        uint16 _duty_temp=0;
        _duty_temp= (uint16)(4*(PR2 +1)*(_duty / 100.0));
       if(_ccp_obj->ccp_inst ==CCP1_INST)
       {
            CCP1CONbits.DC1B= (uint8) (_duty_temp & 0x0003);
            CCPR1L=(uint8)(_duty_temp >>2);
       }
       
       else if (_ccp_obj->ccp_inst ==CCP2_INST)
       {
           CCP2CONbits.DC2B= (uint8) (_duty_temp & 0x0003);
           CCPR2L=(uint8)(_duty_temp >>2);
       }
       else 
       {  /*  Nothing */}
   }
     
    
    return ret;
    
    
    
    
  
    
   
  
    
}
Std_ReturnType CCP_PWM_Start(const ccp_t * _ccp_obj)
{
   Std_ReturnType  ret=E_OK;
   
   if(NULL==_ccp_obj)
   {
       ret=E_NOT_OK;
   }
   else
   {
       if(_ccp_obj->ccp_inst ==CCP1_INST)
       {
           CCP1_SET_MODE(CCP_PWM_MODE);
       }
       
       else if (_ccp_obj->ccp_inst ==CCP2_INST)
       {
           CCP2_SET_MODE(CCP_PWM_MODE);
       }
       else 
       {  /*  Nothing */}
   }
     
    
    return ret; 
}


Std_ReturnType CCP_PWM_Stop(const ccp_t * _ccp_obj)
{
    
  Std_ReturnType  ret=E_OK;
   
   if(NULL==_ccp_obj)
   {
       ret=E_NOT_OK;
   }
   else
   {
       if(_ccp_obj->ccp_inst ==CCP1_INST)
       {
           CCP1_SET_MODE(CCP_MODULE_DISABLE);
       }
       
       else if (_ccp_obj->ccp_inst ==CCP2_INST)
       {
           CCP2_SET_MODE(CCP_MODULE_DISABLE);
       }
       else 
       {  /*  Nothing */}
   }
     
    
    return ret; 
}
#endif  


#if CCP_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED
Std_ReturnType CCP_ISCompareDataReady(uint8 * _compare_status)
{
    Std_ReturnType ret=E_OK;
    
    if(NULL == _compare_status)
    {
        ret=E_NOT_OK;
        
    }
    else
    {
        
         if(CCP_COMPARE_READY == PIR1bits.CCP1IF)
        {
           * _compare_status =CCP_COMPARE_READY;
            CCP1_InterruptFlagClear();
        }
        else
        {
             * _compare_status =CCP_COMPARE_NOT_READY;
        }
        
    }
    
    return ret;
    
}
Std_ReturnType CCP_Compare_Mode_Set_Value(uint16  Compare_Value)
{
    Std_ReturnType ret = E_OK;
      CCP_REG_T capture_Temp_value={.ccpr1_low =0 , .ccpr1_high =0};
      
      capture_Temp_value.ccpr1_16Bit=Compare_Value;
      CCPR1L=capture_Temp_value.ccpr1_low;
      CCPR1H=capture_Temp_value.ccpr1_high;
      
      return ret;
}
#endif  


#if CCP_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED
Std_ReturnType CCP_ISCapturedDataReady(uint8 * _capture_status)
{
      Std_ReturnType ret=E_OK;
    
    if(NULL == _capture_status)
    {
        ret=E_NOT_OK;
        
    }
    else
    {
        if(CCP_CAPTURE_READY == PIR1bits.CCP1IF)
        {
           * _capture_status =CCP_CAPTURE_READY;
            CCP1_InterruptFlagClear();
        }
        else
        {
             * _capture_status =CCP_CAPTURE_NOT_READY;
        }
    }
    
    return ret;
    
}
Std_ReturnType CCP_Capture_Mode_Read_Value(uint16* _capture_Value)
{
       Std_ReturnType ret=E_OK;
    CCP_REG_T capture_Temp_value={.ccpr1_low =0 , .ccpr1_high =0};
    if(NULL == _capture_Value)
    {
        ret=E_NOT_OK;
        
    }
    else
    {
        capture_Temp_value.ccpr1_low=CCPR1L;
         capture_Temp_value.ccpr1_high=CCPR1H;
         * _capture_Value=capture_Temp_value.ccpr1_16Bit;
    }
    
    return ret;
    
}

#endif


static void CCP_PWM_Mode_Config(const ccp_t * _ccp_obj)
{
    #if CCP_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED

            
           
             if(_ccp_obj->ccp_inst ==CCP1_INST)
                    {
                        if(CCP_PWM_MODE == _ccp_obj->ccp_mode_variant)
                        {
                            CCP1_SET_MODE(CCP_PWM_MODE); 
                        }
                        else
                        {
                             /*Nothing */
                        }
                    }
       
             else if (_ccp_obj->ccp_inst ==CCP2_INST)
                    {
                        if(CCP_PWM_MODE == _ccp_obj->ccp_mode_variant)
                        {
                            CCP2_SET_MODE(CCP_PWM_MODE); 
                        }
                        else
                        {
                              /*Nothing */
                        }
                    }
              else 
                     {   /*  Nothing */}

            
            PR2=(uint8)((_XTAL_FREQ/(_ccp_obj->PWM_Frequency*4.0*_ccp_obj->timer2_postscaler_value*_ccp_obj->timer2_prescaler_value))-1);


#endif       
}


static void ccp_Interrupt_Config(const ccp_t * _ccp_obj)
{
    
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

     CCP1_InterruptEnable();
     CCP1_InterruptFlagClear();
   CCP1_InterruptHandler=  _ccp_obj->CCP1_InterruptHandler;
   
 #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
            
         INTERRUPT_PriorityLevelEnable();
         if(INTERRUPT_LOW_PRIORITY==_ccp_obj->ccp1_priority)
         {
              CCP1_LowPrioritySet();
             INTERRUPT_GLOBALIntruuptLowEnable();
         }
         else if(INTERRUPT_HIGH_PRIORITY==_ccp_obj->ccp1_priority)
         {
             INTERRUPT_GLOBALIntruuptHighEnable();
              CCP1_HighPrioritySet();
         }
         
#else
         INTERRUPT_GLOBALIntruuptEnable();
         INTERRUPT_PeripheralIntruuptEnable();


#endif    
#endif 
    
         
         
         
  #if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

     CCP2_InterruptEnable();
     CCP2_InterruptFlagClear();
   CCP2_InterruptHandler=  _ccp_obj->CCP2_InterruptHandler;
   
 #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
            
         INTERRUPT_PriorityLevelEnable();
         if(INTERRUPT_LOW_PRIORITY==_ccp_obj->ccp2_priority)
         {
              CCP2_LowPrioritySet();
             INTERRUPT_GLOBALIntruuptLowEnable();
         }
         else if(INTERRUPT_HIGH_PRIORITY==_ccp_obj->ccp2_priority)
         {
             INTERRUPT_GLOBALIntruuptHighEnable();
              CCP2_HighPrioritySet();
         }
         
#else
         INTERRUPT_GLOBALIntruuptEnable();
         INTERRUPT_PeripheralIntruuptEnable();


#endif    
#endif        
}




#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void ccp1_ISR(void)
{
    CCP1_InterruptFlagClear();
    
    if(CCP1_InterruptHandler)
    {
        CCP1_InterruptHandler();
    }
    else
    {  }
}

#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void ccp2_ISR(void)
{
    CCP2_InterruptFlagClear();
    
    if(CCP2_InterruptHandler)
    {
        CCP2_InterruptHandler();
    }
    else
    {  }
}

#endif

static void ccp_Capture_Mode_Timer_Select(const ccp_t * _ccp_obj)
{
    if(CCP1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer)
    {
        
        T3CONbits.T3CCP1=0;
        T3CONbits.T3CCP1=1;
    }
    else if (CCP1_TIMER1_CCP2_TIMER2 == _ccp_obj->ccp_capture_timer)
    {
        T3CONbits.T3CCP1=1;
        T3CONbits.T3CCP1=0;
    }
    else if (CCP1_CCP2_TIMER1 == _ccp_obj->ccp_capture_timer)
    {
        T3CONbits.T3CCP1=0;
        T3CONbits.T3CCP1=0;
    }
    
}