/* 
 * File:   mcal_internal_interrupt.h
 * Author: mohamedsultan
 *
 * Created on 19 ?????, 2023, 10:13 ?
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H



/*------------------ Includs ------------------*/
#include "mcal_interrupt_config.h"
/* -------------------Macro Declarations ---------------*/



/* ------------------- Macro Function Declarations ------------------*/
#if TIMER0_INTERRUPT_PEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_DISABLE()               (INTCONbits.TMR0IE=0)
#define TIMER0_INTERRUPT_ENABLE()                (INTCONbits.TMR0IE=1)
#define TIMER0_INTERRUPT_FLAG_CLEAR()            (INTCONbits.TMR0IF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

#define TIMER0_HighPrioritySet()                (INTCON2bits.TMR0IP=1)
#define TIMER0_LowPrioritySet()                 (INTCON2bits.TMR0IP=0)

#endif
#endif






#if TIMER1_INTERRUPT_PEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

#define TIMER1_INTERRUPT_DISABLE()               (PIE1bits.TMR1IE=0)
#define TIMER1_INTERRUPT_ENABLE()                (PIE1bits.TMR1IE=1)
#define TIMER1_INTERRUPT_FLAG_CLEAR()            (PIR1bits.TMR1IF=0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

#define TIMER1_HighPrioritySet()                (IPR11bits.TMR1IP=1)
#define TIMER1_LowPrioritySet()                 (IPR11bits.TMR1IP=0)

#endif
#endif

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the TIMER2 Module */
#define TIMER2_InterruptDisable()         (PIE1bits.TMR2IE = 0)
/* This routine sets the interrupt enable for the TIMER2 Module */
#define TIMER2_InterruptEnable()          (PIE1bits.TMR2IE = 1)
/* This routine clears the interrupt flag for the TIMER2 Module */
#define TIMER2_InterruptFlagClear()       (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the TIMER2 Module Interrupt Priority to be High priority */
#define TIMER2_HighPrioritySet()          (IPR1bits.TMR2IP = 1)
/* This routine set the TIMER2 Module Interrupt Priority to be Low priority */
#define TIMER2_LowPrioritySet()           (IPR1bits.TMR2IP = 0)
#endif
#endif

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the TIMER3 Module */
#define TIMER3_InterruptDisable()         (PIE2bits.TMR3IE = 0)
/* This routine sets the interrupt enable for the TIMER3 Module */
#define TIMER3_InterruptEnable()          (PIE2bits.TMR3IE = 1)
/* This routine clears the interrupt flag for the TIMER3 Module */
#define TIMER3_InterruptFlagClear()       (PIR2bits.TMR3IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the TIMER3 Module Interrupt Priority to be High priority */
#define TIMER3_HighPrioritySet()          (IPR2bits.TMR3IP = 1)
/* This routine set the TIMER3 Module Interrupt Priority to be Low priority */
#define TIMER3_LowPrioritySet()           (IPR2bits.TMR3IP = 0)
#endif
#endif






#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the CCP1 Module */
#define CCP1_InterruptDisable()         (PIE1bits.CCP1IE = 0)
/* This routine sets the interrupt enable for the CCP1 Module */
#define CCP1_InterruptEnable()          (PIE1bits.CCP1IE  = 1)
/* This routine clears the interrupt flag for the CCP1 Module */
#define CCP1_InterruptFlagClear()       (PIR1bits.CCP1IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the CCP1 Module Interrupt Priority to be High priority */
#define CCP1_HighPrioritySet()          (IPR1bits.CCP1IP = 1)
/* This routine set the TIMER3 Module Interrupt Priority to be Low priority */
#define CCP1_LowPrioritySet()           (IPR1bits.CCP1IP = 0)
#endif
#endif



#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the CCP1 Module */
#define CCP2_InterruptDisable()         (PIE2bits.CCP2IE = 0)
/* This routine sets the interrupt enable for the CCP1 Module */
#define CCP2_InterruptEnable()          (PIE2bits.CCP2IE  = 1)
/* This routine clears the interrupt flag for the CCP1 Module */
#define CCP2_InterruptFlagClear()       (PIR2bits.CCP2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the CCP1 Module Interrupt Priority to be High priority */
#define CCP2_HighPrioritySet()          (IPR2bits.CCP2IP = 1)
/* This routine set the TIMER3 Module Interrupt Priority to be Low priority */
#define CCP2_LowPrioritySet()           (IPR2bits.CCP2IP = 0)
#endif
#endif



/* ------------------- Data Type -------------------*/

/* --------------------Software Interfaces Declarations ----------------------*/

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

