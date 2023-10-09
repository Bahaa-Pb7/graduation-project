/* 
 * File:   hal_gpio.c
 * Author: mohamedsultan
 *
 * Created on 27 ?????, 2023, 04:48 ?
 */

#include "hal_gpio.h"

volatile uint8 *tris_regsiter[]={&TRISA,&TRISB,&TRISC ,&TRISD,&TRISE};
volatile uint8 *lat_regsiter[]={&LATA,&LATB,&LATC ,&LATD,&LATE};
volatile uint8 *port_regsiter[]={&PORTA,&PORTB,&PORTC ,&PORTD,&PORTE};


/**
 * 
 * @param _pin_config
 * @return 
 */

#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t * _pin_config)
{
    Std_ReturnType ret= E_OK ;
    
    if ((NULL == _pin_config) || (_pin_config->pin > PORT_PIN_MAX_NUMBER - 1))
    {
        ret= E_NOT_OK;
    }
    else
    {
        switch(_pin_config->direction)
            {
                case GPIO_DIRECTION_OUTPUT:

                    CLEAR_BIT(*tris_regsiter[_pin_config->port],_pin_config->pin);

                    break;

                case GPIO_DIRECTION_INPUT:

                    SET_BIT(*tris_regsiter[_pin_config->port],_pin_config->pin);

                    break;

                default:
                    ret= E_NOT_OK;


            }
    
    }
  
    return ret;
    
}
#endif
/**
 * 
 * @param _pin_config
 * @param direction_status
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * _pin_config,direction_t *direction_status)
{
     Std_ReturnType ret= E_OK ;
      if ((NULL == _pin_config) || (NULL== direction_status)|| (_pin_config->pin > PORT_PIN_MAX_NUMBER - 1))
    {
        ret= E_NOT_OK;
    }
    else
    {
          *direction_status= READ_BIT(*tris_regsiter[_pin_config->port],_pin_config->pin);
          
    }
     
     
     return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t * _pin_config,logic_t logic)
{
      Std_ReturnType ret= E_OK ;
    if ((NULL == _pin_config) || (_pin_config->pin > PORT_PIN_MAX_NUMBER - 1))
    {
        ret= E_NOT_OK;
    }
    else
    {
        switch(logic)
        {
            case LOW:
                CLEAR_BIT(*lat_regsiter[_pin_config->port],_pin_config->pin);
                break;
                
            case HIGH:
                SET_BIT(*lat_regsiter[_pin_config->port],_pin_config->pin);
                break;
                
            default :
                        
                 ret= E_NOT_OK;  
                        
            
        }
          
    }
     
     
     return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t * _pin_config,logic_t *logic)
{
    Std_ReturnType ret= E_OK ;
    if ((NULL == _pin_config) || (NULL== logic)|| (_pin_config->pin > PORT_PIN_MAX_NUMBER - 1))
    {
        ret= E_NOT_OK;
    }
    else
    {
          *logic= READ_BIT(*port_regsiter[_pin_config->port],_pin_config->pin);
    }
     
     
     return ret;
}
#endif
/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_intialize(const pin_config_t * _pin_config)
{
     Std_ReturnType ret= E_OK ;
     if(NULL== _pin_config)
     {
         ret=E_NOT_OK;
     }
     else
     {
         ret  =gpio_pin_direction_intialize(_pin_config);
         ret |= gpio_pin_write_logic(_pin_config,_pin_config->logic);
         
         
     }
     
     
     return ret;
    
}
#endif
/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * _pin_config)
{
    Std_ReturnType ret= E_OK ;
    
    if ((NULL == _pin_config)|| (_pin_config->pin > PORT_PIN_MAX_NUMBER - 1))
    {
        ret= E_NOT_OK;
    }
    else
    {
        
        TOGGEL_BIT(*lat_regsiter[_pin_config->port],_pin_config->pin);
    }
     
     
     
     return ret;
}
#endif

/**
 * 
 * @param port
 * @param direction
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction)
{
      Std_ReturnType ret= E_OK ;
     if ( port > PORT_MAX_NUMBER-1)
    {
        ret= E_NOT_OK;
    }
    else
    {
         *tris_regsiter[port]=direction;
        
          
    }
     
     
     return ret;
}
#endif
/**
 * 
 * @param port
 * @param direction_status
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(port_index_t port,uint8 * direction_status)
{
    Std_ReturnType ret= E_OK ;
     
    if ((NULL == direction_status)|| (port > PORT_MAX_NUMBER-1))
    {
        ret= E_NOT_OK;
    }
    else
    {
        *direction_status=*tris_regsiter[port];
          
    }
     
     
     return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port,uint8 logic)
{
     Std_ReturnType ret= E_OK ;
     if(port> PORT_MAX_NUMBER-1)
     {
          ret= E_NOT_OK;
     }
     else
     {
         *lat_regsiter[port]=logic;
     }
     
     
     return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port,uint8 *logic)
{
    Std_ReturnType ret= E_OK ;
    if ((NULL == logic) || (port> PORT_MAX_NUMBER-1))
    {
        ret= E_NOT_OK;
    }
    else
    {
          *logic = *lat_regsiter[port];
    }
          
    
     
     return ret;
}
#endif
/**
 * 
 * @param port
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
      Std_ReturnType ret= E_OK ;
     if(port> PORT_MAX_NUMBER-1)
     {
          ret= E_NOT_OK;
     }
     else
     {
         *lat_regsiter[port] ^= MASK_TOGGEL_PORT;
     }
     
     
     return ret;
}
#endif