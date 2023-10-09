/* 
 * File:   mcal_interrupt_gen_clf.h
 * Author: mohamedsultan
 *
 * Created on 20 ?????, 2023, 12:13 ?
 */

#ifndef MCAL_INTERRUPT_GEN_CLF_H
#define	MCAL_INTERRUPT_GEN_CLF_H
/*------------------ Includs ------------------*/

/* -------------------Macro Declarations ---------------*/

#define INTERRUPT_FEATURE_ENABLE  1
#define INTERRUPT_FEATURE_DISABLE  0

#define INTERRUPT_PRIORITY_LEVELS_ENABLE             INTERRUPT_FEATURE_DISABLE
#define EXTERNAL_INTERRUPT_INTX_FEATURE_ENABLE       INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE   INTERRUPT_FEATURE_ENABLE



#define TIMER0_INTERRUPT_PEATURE_ENABLE              INTERRUPT_FEATURE_DISABLE

#define TIMER1_INTERRUPT_PEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE


#define TIMER2_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_DISABLE


#define TIMER3_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE


#define CCP1_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE
/* ------------------- Macro Function Declarations ------------------*/


/* ------------------- Data Type -------------------*/

/* --------------------Software Interfaces Declarations ----------------------*/


#endif	/* MCAL_INTERRUPT_GEN_CLF_H */

