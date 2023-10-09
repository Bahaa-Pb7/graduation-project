/* 
 * File:   mcal_interrupt_manager.c
 * Author: mohamedsultan
 *
 * Created on 19 ?????, 2023, 10:16 ?
 */

#include"mcal_interrupt_manager.h"

#if  INTERRUPT_PRIORITY_LEVELS_ENABLE ==INTERRUPT_FEATURE_ENABLE

void __interrupt() InterrupyManagerHigh(void)
{
    if((INTERRUPT_ENABEL == INTCONbits.INT0E) && (INTERRUPT_OCCUR== INTCONbits.INT0F) )
    {
        INT0_ISR();
    }
    else{}
     if((INTERRUPT_ENABEL == INTCON3bits.INT2E) && (INTERRUPT_OCCUR== INTCON3bits.INT2F) )
    {
        INT2_ISR();
    }  
    else{}
    
  if((INTERRUPT_ENABEL == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR== INTCONbits.TMR0IF) )
    {
       TMR0_ISR();
    } 
  else{}
}

void __interrupt(low_priority) InterrupyManagerLow(void)
{
    if((INTERRUPT_ENABEL == INTCON3bits.INT1E) && (INTERRUPT_OCCUR== INTCON3bits.INT1F) )
    {
        INT1_ISR();
    }
    else{}  
    
   if((INTERRUPT_ENABEL == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR== INTCONbits.TMR0IF) )
    {
       TMR0_ISR();
    } 
   else{}
  if((INTERRUPT_ENABEL == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR== PIR1bits.TMR1IF) )
    {
       TMR1_ISR();
    }  
    else{}
    
    
    if((INTERRUPT_ENABEL == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF)){
            ccp1_ISR();
        }
        else{ /* Nothing */ }
        if((INTERRUPT_ENABEL == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF)){
            ccp2_ISR();
        }
        else{ /* Nothing */ }
}
#else
void __interrupt() InterrupyManager(void)
{
    if((INTERRUPT_ENABEL == INTCONbits.INT0E) && (INTERRUPT_OCCUR== INTCONbits.INT0F) )
    {
        INT0_ISR();
    }
    else{}
     if((INTERRUPT_ENABEL == INTCON3bits.INT1E) && (INTERRUPT_OCCUR== INTCON3bits.INT1F) )
    {
        INT1_ISR();
    }
    else{}  
      if((INTERRUPT_ENABEL == INTCON3bits.INT2E) && (INTERRUPT_OCCUR== INTCON3bits.INT2F) )
    {
        INT2_ISR();
    }  
    else{}
    
   if((INTERRUPT_ENABEL == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR== INTCONbits.TMR0IF) )
    {
       TMR0_ISR();
    }  
    else{}
    
    if((INTERRUPT_ENABEL == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR== PIR1bits.TMR1IF) )
    {
       TMR1_ISR();
    }  
    else{}
    
    
    if((INTERRUPT_ENABEL == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF)){
        TMR2_ISR();
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABEL == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF)){
        TMR3_ISR();
    }
    else{ /* Nothing */ }
    
    
    if((INTERRUPT_ENABEL == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF)){
            ccp1_ISR();
        }
        else{ /* Nothing */ }
        if((INTERRUPT_ENABEL == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF)){
            ccp2_ISR();
        }
        else{ /* Nothing */ }
    
}

#endif