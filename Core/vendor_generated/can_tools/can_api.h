/*
 * threadx.c
 *
 *  Created on: Apr 20, 2024
 *      Author: Steven
 */
#ifndef USER_APP_THREADX_H_
#define USER_APP_THREADX_H_

#include "can.h"

#define FRONT   
// #define REAR

#ifdef FRONT

#define analogPack          ucr_01_front_analog_pack
#define analogData_t        ucr_01_front_analog_t
#define frequencyPack       ucr_01_front_frequency_pack
#define frequencyData_t     ucr_01_front_frequency_t
#define aeroPack            ucr_01_front_aero_pack
#define aero_t              ucr_01_front_aero_t
#define strainGauge1        ucr_01_front_strain_gauges1_pack
#define strainGaugeData1_t  ucr_01_front_strain_gauges1_t
#define strainGauge2        ucr_01_front_strain_gauges2_pack
#define strainGaugeData2_t  ucr_01_front_strain_gauges2_t

#endif

#ifdef REAR

#define analogPack      ucr_01_rear_analog_pack
#define frequencyPack   ucr_01_rear_frequency_pack
#define aeroPack        ucr_01_rear_aero_pack
#define strainGauge1    ucr_01_rear_strain_gauges1_pack
#define strainGauge2    ucr_01_rear_strain_gauges2_pack

#endif














#endif /* USER_APP_THREADX_H_ */
