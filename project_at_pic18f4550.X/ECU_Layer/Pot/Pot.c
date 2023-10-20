
/* ************************* Includes Section Start **************** */
#include "Pot.h"
/* ************************** Includes Section End ***************** */

/* ******************** Definitions Section Start ****************** */
static adc_conf_t adc={
          
                  .adc_channel=ADC_CHANNEL_AN0,
                   .acquisition_time=ADC_12_TAD,
                  .conversion_clock=ADC_CONVERSION_CLOCK_FOSC_DIV_16,
                  .result_format=ADC_RESULT_RIGHT,
                  .voltage_reference=ADC_VOLTAGE_REFERENCE_DISABLED,
                  
};

/* ********************* Definitions Section End ******************* */



/* **************** Functions Definitions Section Start ************ */
Std_ReturnType Pot_initialization(adc_channel_select_t channal){
    Std_ReturnType ret = E_NOT_OK;
    adc.adc_channel=channal;
    ADC_Init(&adc);
}

Std_ReturnType ECU_Pot_Set( uint32 *Pot_Value,uint16 Ref_value){
    Std_ReturnType RET = E_OK;
    uint16 Pot_Reslution;
    RET= ADC_GetConversion_Blocking(&adc,adc.adc_channel,&Pot_Reslution);
    uint32 x=((uint32)(((uint32)Pot_Reslution)*(Ref_value))/1023);
    
    *Pot_Value=x;
    return RET;
}

/* ***************** Function Definitions Section End ************* */

