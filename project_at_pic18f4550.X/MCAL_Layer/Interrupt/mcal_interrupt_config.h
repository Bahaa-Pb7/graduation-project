/* 
 * File:   mcal_interrupt_config.h
 * Author: mohamedsultan
 *
 * Created on 19 ?????, 2023, 10:11 ?
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/*------------------ Includs ------------------*/

#include "pic18f4550.h"
#include "../mcal_std_type.h"
#include "mcal_interrupt_gen_clf.h"
#include "../GPIO/hal_gpio.h"
/* -------------------Macro Declarations ---------------*/

#define INTERRUPT_ENABEL 1
#define INTERRUPT_DISABLE 0
#define INTERRUPT_OCCUR   1
#define INTERRUPT_NOT_OCCUR   1
#define INTERRUPT_PRIORITY_ENABLE 1
#define INTERRUPT_PRIORITY_DISABLE  0
/* ------------------- Macro Function Declarations ------------------*/

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE


#define INTERRUPT_PriorityLevelEnable()         (RCONbits.IPEN=1)
#define INTERRUPT_PriorityLevelDisable()         (RCONbits.IPEN=0)

#define INTERRUPT_GLOBALIntruuptHighEnable()    (INTCONbits.GIEH = 1)
#define INTERRUPT_GLOBALIntruuptHighDisable()    (INTCONbits.GIEH = 0)

#define INTERRUPT_GLOBALIntruuptLowEnable()    (INTCONbits.GIEL = 1)
#define INTERRUPT_GLOBALIntruuptLowDisable()    (INTCONbits.GIEL = 0)

#else

#define INTERRUPT_GLOBALIntruuptEnable()    (INTCONbits.GIE = 1)
#define INTERRUPT_GLOBALIntruuptDisable()    (INTCONbits.GIE = 0)

#define INTERRUPT_PeripheralIntruuptEnable()    (INTCONbits.PEIE = 1)
#define INTERRUPT_PeripheralIntruuptDisable()    (INTCONbits.PEIE = 0)


#endif






/* ------------------- Data Type -------------------*/

typedef enum {
    INTERRUPT_LOW_PRIORITY=0,
    INTERRUPT_HIGH_PRIORITY        
}interrupt_priority_cfg;
/* --------------------Software Interfaces Declarations ----------------------*/




#endif	/* MCAL_INTERRUPT_CONFIG_H */

