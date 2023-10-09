/* 
 * File:   hal_gpio.h
 * Author: mohamedsultan
 *
 * Created on 27 ?????, 2023, 04:49 ?
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H


/* Section : Includes */
#include "../mcal_std_type.h"
#include "../std_libraries.h"
#include "../compiler.h"
#include "hal_gpio_cfg.h"
#include "pic18f4550.h"

/* Section : Macro Declarations */
#define GPIO_PORT_PIN_CONFIGURATION CONFIG_ENABLE
#define GPIO_PORT_CONFIGURATION CONFIG_ENABLE
#define BIT_MASK  ((uint8)1)
#define PORT_PIN_MAX_NUMBER 8
#define PORT_MAX_NUMBER     5
#define MASK_TOGGEL_PORT 0XFF

/* Section : Macro Function Declarations */
#define HWRREG8(_X)   (*(volatile uint8 *)(_X))

#define SET_BIT(REG,BIT_POS)    (REG |= (BIT_MASK<< BIT_POS))
#define CLEAR_BIT(REG,BIT_POS)  (REG &= ~(BIT_MASK<< BIT_POS))
#define TOGGEL_BIT(REG,BIT_POS) (REG ^= (BIT_MASK<< BIT_POS))
#define READ_BIT(REG,BIT_POS)   ((REG >> BIT_POS) & BIT_MASK)


/* Section : Data Type  Declarations */
typedef enum {
    LOW,
    HIGH  
}logic_t;


typedef enum {
    GPIO_DIRECTION_OUTPUT,
    GPIO_DIRECTION_INPUT
}direction_t;


typedef enum {
    
    PIN0,
    PIN1,
    PIN2,
    PIN3, 
    PIN4,
    PIN5, 
    PIN6,
    PIN7
}pin_index_t;


typedef enum {
    
    PORTA_INDEX=0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX, 
    PORTE_INDEX,
 
}port_index_t;

typedef struct {
    
    uint8 port :3 ;       /*@ref port_index_t */
    uint8 pin  :3 ;       /*@ref pin_index_t */
    uint8 direction :1 ;  /*@ref direction_t */
    uint8 logic :1 ;      /*@ref logic_t */
    
}pin_config_t;


/* Section : Function Declarations */
/**
 * 
 * @param _pin_config
 * @return 
 */
Std_ReturnType gpio_pin_intialize(const pin_config_t * _pin_config);

/**
 * 
 * @param _pin_config
 * @return 
 */
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t * _pin_config);
/**
 * 
 * @param _pin_config
 * @param direction_status
 * @return 
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * _pin_config,direction_t *direction_status);
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t * _pin_config,logic_t logic);
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t * _pin_config,logic_t *logic);
/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t * _pin_config,logic_t logic);
/**
 * 
 * @param _pin_config
 * @return 
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * _pin_config);



/**
 * 
 * @param port
 * @param direction
 * @return 
 */
Std_ReturnType gpio_port_direction_intialize(port_index_t port,uint8 direction);
/**
 * 
 * @param port
 * @param direction_status
 * @return 
 */
Std_ReturnType gpio_port_get_direction_status(port_index_t port,uint8 * direction_status);
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
Std_ReturnType gpio_port_write_logic(port_index_t port,uint8 logic);
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
Std_ReturnType gpio_port_read_logic(port_index_t port,uint8 *logic);
/**
 * 
 * @param port
 * @return 
 */
Std_ReturnType gpio_port_toggle_logic(port_index_t port);

#endif	/* HAL_GPIO_H */

