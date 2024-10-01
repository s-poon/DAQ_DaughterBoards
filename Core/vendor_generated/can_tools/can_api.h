/*
 * can_api.h
 *
 *  Created on: Jun 2, 2024
 *      Author: Steven
 */

#ifndef VENDOR_GENERATED_CAN_TOOLS_CAN_API_H_
#define VENDOR_GENERATED_CAN_TOOLS_CAN_API_H_

#include "ucr_01.h"

#define FRONT
// #define REAR

//#ifdef FRONT
//
//#define analogPack                  ucr_01_front_analog_pack
//#define analogData_t                ucr_01_front_analog_t
//#define ANALOG_CANID                UCR_01_FRONT_ANALOG_FRAME_ID
//#define ANALOG_DATA_LENGTH          UCR_01_FRONT_ANALOG_LENGTH
//
//#define frequencyPack               ucr_01_front_frequency_pack
//#define frequencyData_t             ucr_01_front_frequency_t
//#define FREQUENCY_CANID             UCR_01_FRONT_FREQUENCY_FRAME_ID
//#define FREQUENCY_DATA_LENGTH       UCR_01_FRONT_FREQUENCY_LENGTH
//
//#define aeroPack                    ucr_01_front_aero_pack
//#define aero_t                      ucr_01_front_aero_t
//#define AERO_CANID                  UCR_01_FRONT_AERO_FRAME_ID
//#define AERO_DATA_LENGTH            UCR_01_FRONT_AERO_LENGTH
//
//#define strainGauge1                ucr_01_front_strain_gauges1_pack
//#define strainGaugeData1_t          ucr_01_front_strain_gauges1_t
//#define STRAIN_GAUGE1_CANID         UCR_01_FRONT_STRAIN_GAUGES1_FRAME_ID
//#define STRAIN_GAUGE1_DATA_LENGTH   UCR_01_FRONT_STRAIN_GAUGES1_LENGTH
//
//#define strainGauge2                ucr_01_front_strain_gauges2_pack
//#define strainGaugeData2_t          ucr_01_front_strain_gauges2_t
//#define STRAIN_GAUGE2_CANID         UCR_01_FRONT_STRAIN_GAUGES2_FRAME_ID
//#define STRAIN_GAUGE2_DATA_LENGTH   UCR_01_FRONT_STRAIN_GAUGES2_LENGTH
//
//
//#endif

#ifdef REAR

#define analogPack                  ucr_01_rear_analog_pack
#define analogData_t                ucr_01_rear_analog_t
#define ANALOG_CANID                UCR_01_REAR_ANALOG_FRAME_ID
#define ANALOG_DATA_LENGTH          UCR_01_REAR_ANALOG_LENGTH 

#define frequencyPack               ucr_01_rear_frequency_pack
#define frequencyData_t             ucr_01_rear_frequency_t
#define FREQUENCY_CANID             UCR_01_REAR_FREQUENCY_FRAME_ID
#define FREQUENCY_DATA_LENGTH       UCR_01_REAR_FREQUENCY_LENGTH

#define aeroPack                    ucr_01_rear_aero_pack
#define aero_t                      ucr_01_rear_aero_t
#define AERO_CANID                  UCR_01_REAR_AERO_FRAME_ID
#define AERO_DATA_LENGTH            UCR_01_REAR_AERO_LENGTH

#define strainGauge1                ucr_01_rear_strain_gauges1_pack
#define strainGaugeData1_t          ucr_01_rear_strain_gauges1_t
#define STRAIN_GAUGE1_CANID         UCR_01_REAR_STRAIN_GAUGES1_FRAME_ID
#define STRAIN_GAUGE1_DATA_LENGTH   UCR_01_REAR_STRAIN_GAUGES1_LENGTH

#define strainGauge2                ucr_01_rear_strain_gauges2_pack
#define strainGaugeData2_t          ucr_01_rear_strain_gauges2_t
#define STRAIN_GAUGE2_CANID         UCR_01_REAR_STRAIN_GAUGES2_FRAME_ID
#define STRAIN_GAUGE2_DATA_LENGTH   UCR_01_REAR_STRAIN_GAUGES2_LENGTH

#endif

#endif /* VENDOR_GENERATED_CAN_TOOLS_CAN_API_H_ */
