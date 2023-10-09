/* 
 * File:   ecu_led.h
 * Author: mohamedsultan
 *
 * Created on 07 ?????, 2023, 12:01 ?
 */

#ifndef ECU_LED_H
#define	ECU_LED_H


/*------------------ Includs ------------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"


/* -------------------Macro Declarations ---------------*/


/* ------------------- Macro Function Declarations ------------------*/


/* ------------------- Data Type -------------------*/
typedef enum {
    LED_OFF,
    LED_ON        
    
}led_status_t;


typedef struct {
    
    uint8 port_name :4;
    uint8 pin :3;
    uint8 led_status :1;
}led_t;
/* --------------------Software Interfaces Declarations ----------------------*/

/**
 * @brief initialize the assigned pin to be OUTPUT and turn the led off
 * @param led : pointer to the led module configuration  
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK): the function has issue while performing this action
 */
Std_ReturnType led_initialize(const led_t * led);
/**
 * @brief Turn the led on
 * @param led : pointer to the led module configuration  
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK): the function has issue while performing this action
 */
Std_ReturnType led_turn_on(const led_t * led);
/**
 * @brief Turn the led off
 * @param led : pointer to the led module configuration  
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK): the function has issue while performing this action
 */
Std_ReturnType led_turn_off(const led_t * led);
/**
 * @brief Toggle the led
 * @param led : pointer to the led module configuration  
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK): the function has issue while performing this action
 */
Std_ReturnType led_toggle(const led_t * led);
#endif	/* ECU_LED_H */

