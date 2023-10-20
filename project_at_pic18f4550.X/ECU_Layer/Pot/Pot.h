/* 
 * File:   Pot.h
 * Author: ram speed
 *
 * Created on October 20, 2023, 7:45 AM
 */

#ifndef POT_H
#define	POT_H
/* ************************* Includes Section Start ***************** */
#include "../../MCAL_Layer/ADC/hal_adc.h"
/* ************************** Includes Section End ***************** */

/* ***************** Macro Declarations Section Start ************** */

/* ****************** Macro Declarations Section End *************** */

/* ********* Macro Functions Declarations Section Start ************ */

/* ********** Macro Functions Declarations Section End ************* */

/* ************* Data Type Declarations Section Start ************** */

/* ************** Data Type Declarations Section End *************** */

/* **************** Function Declarations Section Start ************ */
Std_ReturnType Pot_initialization(adc_channel_select_t channal);
Std_ReturnType  ECU_Pot_Set( uint32 *Pot_Value,uint16 Ref_value);
/* ***************** Function Declarations Section End ************* */


#endif	/* POT_H */

