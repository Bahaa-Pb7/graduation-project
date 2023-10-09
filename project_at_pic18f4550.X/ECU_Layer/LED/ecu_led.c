/* 
 * File:   ecu_led.c
 * Author: mohamedsultan
 *
 * Created on 07 ?????, 2023, 12:01 ?
 */


#include "ecu_led.h"

/**
 * @brief initialize the assigned pin to be OUTPUT and turn the led off
 * @param led : pointer to the led module configuration  
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK): the function has issue while performing this action
 */
Std_ReturnType led_initialize(const led_t * led)
{
    
    Std_ReturnType ret = E_OK;
    if (NULL == led)
    {
        ret = E_NOT_OK;
    }
    else 
    {
         pin_config_t pin_obj ={
          .direction=GPIO_DIRECTION_OUTPUT,
          .logic=led->led_status,
          .pin= led->pin,
          .port=led->port_name
        };
        
        ret=gpio_pin_intialize(&pin_obj);
    }
    
    return ret;
}

/**
 * @brief Turn the led on
 * @param led : pointer to the led module configuration  
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK): the function has issue while performing this action
 */
Std_ReturnType led_turn_on(const led_t * led)
{
    Std_ReturnType ret = E_OK;
    if (NULL == led)
    {
        ret = E_NOT_OK;
    }
    else 
    {
          pin_config_t pin_obj ={
          .direction=GPIO_DIRECTION_OUTPUT,
          .logic=led->led_status,
          .pin= led->pin,
          .port=led->port_name
        };
        
        ret=gpio_pin_write_logic(&pin_obj,HIGH);
    }
    
    return ret;
}
/**
 * @brief Turn the led off
 * @param led : pointer to the led module configuration  
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK): the function has issue while performing this action
 */
Std_ReturnType led_turn_off(const led_t * led)
{
    Std_ReturnType ret = E_OK;
    if (NULL == led)
    {
        ret = E_NOT_OK;
    }
    else 
    {
         pin_config_t pin_obj ={
          .direction=GPIO_DIRECTION_OUTPUT,
          .logic=led->led_status,
          .pin= led->pin,
          .port=led->port_name
        };
        
        ret=gpio_pin_write_logic(&pin_obj,LOW);
    }
    
    return ret; 
}
/**
 * @brief Toggle the led
 * @param led : pointer to the led module configuration  
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK): the function has issue while performing this action
 */
Std_ReturnType led_toggle(const led_t * led)
{
    Std_ReturnType ret = E_OK;
    if (NULL == led)
    {
        ret = E_NOT_OK;
    }
    else 
    {
           pin_config_t pin_obj ={
          .direction=GPIO_DIRECTION_OUTPUT,
          .logic=led->led_status,
          .pin= led->pin,
          .port=led->port_name
        };
        
        ret=gpio_pin_toggle_logic(&pin_obj);
    }
    
    return ret;
}