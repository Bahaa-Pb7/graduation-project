/* 
 * File:   mcal_interrupt_manager.h
 * Author: mohamedsultan
 *
 * Created on 19 ?????, 2023, 10:16 ?
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H
/*------------------ Includs ------------------*/
#include "mcal_interrupt_config.h"

/* -------------------Macro Declarations ---------------*/



/* ------------------- Macro Function Declarations ------------------*/


/* ------------------- Data Type -------------------*/

/* --------------------Software Interfaces Declarations ----------------------*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);
void ccp1_ISR(void);
void ccp2_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */

