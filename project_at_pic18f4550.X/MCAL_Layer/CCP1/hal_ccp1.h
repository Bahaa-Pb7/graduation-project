/* 
 * File:   hal_ccp1.h
 * Author: mohamedsultan
 *
 * Created on 03 ?????, 2023, 07:33 ?
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H


/*------------------ Includs ------------------*/
#include"ccp1_cfg.h"
#include "pic18f4550.h"
#include "../mcal_std_type.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../device_config.h"
/* -------------------Macro Declarations ---------------*/
#define CCP_MODULE_DISABLE                   ((uint8)0x00)

#define  CCP_CAPTURE_MODE_1_FALLING_EDGE     ((uint8)0x04)
#define  CCP_CAPTURE_MODE_1_RISING_EDGE      ((uint8)0x05)
#define  CCP_CAPTURE_MODE_4_RISING_EDGE      ((uint8)0x06)
#define  CCP_CAPTURE_MODE_16_RISING_EDGE     ((uint8)0x07)

#define  CCP_COMPARE_MODE_SET_PIN_LOW        ((uint8)0x08)
#define  CCP_COMPARE_MODE_SET_PIN_HIGH       ((uint8)0x09)
#define  CCP_COMPARE_MODE_TOGGEL_ON_MATCH    ((uint8)0x02)
#define  CCP_COMPARE_MODE_GEN_SW_INTERRUPT   ((uint8)0x0A)
#define  CCP_COMPARE_MODE_GEN_EVENT          ((uint8)0x0B)

#define  CCP_PWM_MODE                        ((uint8)0x0C)


/* CCP Capture Mode State */
#define CCP_CAPTURE_NOT_READY               0x00
#define CCP_CAPTURE_READY                   0x01

/* CCP Compare Mode State */
#define CCP_COMPARE_NOT_READY               0x00
#define CCP_COMPARE_READY                   0x01



/* Timer2 Input Clock Post-scaler */
#define CCP_TIMER2_POSTSCALER_DIV_BY_1       1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2       2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3       3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4       4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5       5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6       6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7       7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8       8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9       9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10      10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11      11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12      12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13      13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14      14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15      15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16      16

/* Timer2 Input Clock Pre-scaler */
#define CCP_TIMER2_PRESCALER_DIV_BY_1        1
#define CCP_TIMER2_PRESCALER_DIV_BY_4        2
#define CCP_TIMER2_PRESCALER_DIV_BY_16       3




#define CCP_MASK_TOGGEL_PORT 0X0F


/* ------------------- Macro Function Declarations ------------------*/

#define CCP1_SET_MODE(_CONFIG)             (CCP1CONbits.CCP1M=_CONFIG)
#define CCP2_SET_MODE(_CONFIG)             (CCP2CONbits.CCP2M=_CONFIG)


             

#define CCP1_toggel_PWM()            (CCP1CONbits.CCP1M ^= CCP_MASK_TOGGEL_PORT)
#define CCP2_toggel_PWM()            (CCP2CONbits.CCP2M ^= CCP_MASK_TOGGEL_PORT)
/* ------------------- Data Type Declarations-------------------*/

typedef enum {
    CCP_CAPTURE_MODE_SELECTED=0,
    CCP_COMPARE_MODE_SELECTED,
    CCP_PWM_MODE_SELECTED      
    
}ccp_mode_t;



typedef enum {
   CCP1_INST,
   CCP2_INST        
    
}ccp_inst_t;


typedef enum {
  CCP1_CCP2_TIMER3=0,
CCP1_TIMER1_CCP2_TIMER2,
CCP1_CCP2_TIMER1
    
    
}ccp_capture_timer_t;

typedef union {
    
    struct{
        
        uint8 ccpr1_low;
        uint8 ccpr1_high;
    };
    
    struct{
        uint16 ccpr1_16Bit;
    };
}CCP_REG_T;

typedef struct{
    ccp_inst_t ccp_inst;
    ccp_mode_t ccp_mode;
    uint8 ccp_mode_variant;
    pin_config_t pin;
    ccp_capture_timer_t ccp_capture_timer;
#if CCP1_INTERRUPT_FEATURE_ENABLE== INTERRUPT_FEATURE_ENABLE 
    void(* CCP1_InterruptHandler)(void);
    interrupt_priority_cfg   ccp1_priority;   
#endif  
 #if CCP2_INTERRUPT_FEATURE_ENABLE== INTERRUPT_FEATURE_ENABLE 
    void(* CCP2_InterruptHandler)(void);
    interrupt_priority_cfg   ccp2_priority;   
#endif      
#if CCP_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED
    uint32 PWM_Frequency;
    uint8 timer2_postscaler_value : 4;
    uint8 timer2_prescaler_value : 2;
#endif  
    
    
}ccp_t;


/* --------------------Software Interfaces Declarations ----------------------*/


Std_ReturnType  CCP_Init(const ccp_t * _ccp_obj);
Std_ReturnType  CCP_DeInit(const ccp_t * _ccp_obj);

#if CCP1_CFG_SELECTED_MODE==CCP1_CFG_PWM_MODE_SELECTED
   
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t * _ccp_obj,const uint8 _duty);
Std_ReturnType CCP_PWM_Start(const ccp_t * _ccp_obj);
Std_ReturnType CCP_PWM_Stop(const ccp_t * _ccp_obj);
#endif  


#if CCP1_CFG_SELECTED_MODE==CCP1_CFG_COMPARE_MODE_SELECTED
Std_ReturnType CCP1_ISCompareDataReady(uint8 * _compare_status);
Std_ReturnType CCP1_Compare_Mode_Read_Value(uint16  Compare_Value);
#endif  


#if CCP1_CFG_SELECTED_MODE==CCP1_CFG_CAPTURE_MODE_SELECTED
Std_ReturnType CCP_ISCapturedDataReady(uint8 * _capture_status);
Std_ReturnType CCP_Capture_Mode_Read_Value(uint16* _capture_Value);

#endif  



#endif	/* HAL_CCP1_H */

