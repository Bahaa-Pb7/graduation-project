/* 
 * File:   current_sensor.h
 * Author: mohamedsultan
 *
 * Created on 09 ??????, 2023, 11:49 ?
 */

#ifndef CURRENT_SENSOR_H
#define	CURRENT_SENSOR_H

#include "../../../MCAL_Layer/ADC/hal_adc.h"




typedef enum{
    CHANNEL_AN0 = 0,
    CHANNEL_AN1,
    CHANNEL_AN2,
    CHANNEL_AN3,
    CHANNEL_AN4,
    CHANNEL_AN5,
    CHANNEL_AN6,
    CHANNEL_AN7,
    CHANNEL_AN8,
    CHANNEL_AN9,
    CHANNEL_AN10,
    CHANNEL_AN11,
    CHANNEL_AN12
}channel_select_t;


Std_ReturnType currant_sensor_init(channel_select_t channal);
double Read_currant_sensor(double scale);

#endif	/* CURRENT_SENSOR_H */

