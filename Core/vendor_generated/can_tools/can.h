/*
 * can.h
 *
 *  Created on: Apr 23, 2024
 *      Author: Steven
 */

#ifndef VENDOR_GENERATED_CAN_TOOLS_CAN_H_
#define VENDOR_GENERATED_CAN_TOOLS_CAN_H_

/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018-2019 Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * This file was generated by cantools version 39.4.1 Tue May  7 01:13:46 2024.
 */

#ifndef UCR_01_H
#define UCR_01_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef EINVAL
#    define EINVAL 22
#endif

/* Frame ids. */
#define UCR_01_FRONT_ANALOG_FRAME_ID            (0x103u)
#define UCR_01_FRONT_FREQUENCY_FRAME_ID         (0x101u)
#define UCR_01_FRONT_AERO_FRAME_ID              (0x600u)
#define UCR_01_FRONT_STRAIN_GAUGES1_FRAME_ID    (0x610u)
#define UCR_01_FRONT_STRAIN_GAUGES2_FRAME_ID    (0x611u)

/* Frame lengths in bytes. */
#define UCR_01_FRONT_ANALOG_LENGTH          (16u)
#define UCR_01_FRONT_FREQUENCY_LENGTH       (16u)
#define UCR_01_FRONT_AERO_LENGTH            (16u)
#define UCR_01_FRONT_STRAIN_GAUGES1_LENGTH  (20u)
#define UCR_01_FRONT_STRAIN_GAUGES2_LENGTH  (20u)

/* Extended or standard frame types. */
#define UCR_01_FRONT_ANALOG_IS_EXTENDED (0)
#define UCR_01_FRONT_FREQUENCY_IS_EXTENDED (0)
#define UCR_01_FRONT_AERO_IS_EXTENDED (0)
#define UCR_01_FRONT_STRAIN_GAUGES1_IS_EXTENDED (0)
#define UCR_01_FRONT_STRAIN_GAUGES2_IS_EXTENDED (0)

/* Frame cycle times in milliseconds. */


/* Signal choices. */


/* Frame Names. */
#define UCR_01_FRONT_ANALOG_NAME "FrontAnalog"
#define UCR_01_FRONT_FREQUENCY_NAME "FrontFrequency"
#define UCR_01_FRONT_AERO_NAME "FrontAero"
#define UCR_01_FRONT_STRAIN_GAUGES1_NAME "FrontStrainGauges1"
#define UCR_01_FRONT_STRAIN_GAUGES2_NAME "FrontStrainGauges2"

/* Signal Names. */
#define UCR_01_FRONT_ANALOG_ANALOG1_NAME "Analog1"
#define UCR_01_FRONT_ANALOG_ANALOG2_NAME "Analog2"
#define UCR_01_FRONT_ANALOG_ANALOG3_NAME "Analog3"
#define UCR_01_FRONT_ANALOG_ANALOG4_NAME "Analog4"
#define UCR_01_FRONT_ANALOG_ANALOG5_NAME "Analog5"
#define UCR_01_FRONT_ANALOG_ANALOG6_NAME "Analog6"
#define UCR_01_FRONT_ANALOG_ANALOG7_NAME "Analog7"
#define UCR_01_FRONT_ANALOG_ANALOG8_NAME "Analog8"
#define UCR_01_FRONT_FREQUENCY_FREQUENCY1_NAME "Frequency1"
#define UCR_01_FRONT_FREQUENCY_FREQUENCY2_NAME "Frequency2"
#define UCR_01_FRONT_FREQUENCY_FREQUENCY3_NAME "Frequency3"
#define UCR_01_FRONT_FREQUENCY_FREQUENCY4_NAME "Frequency4"
#define UCR_01_FRONT_AERO_PRESSURE1_NAME "Pressure1"
#define UCR_01_FRONT_AERO_PRESSURE2_NAME "Pressure2"
#define UCR_01_FRONT_AERO_PRESSURE3_NAME "Pressure3"
#define UCR_01_FRONT_AERO_TEMPERATURE1_NAME "Temperature1"
#define UCR_01_FRONT_AERO_TEMPERATURE2_NAME "Temperature2"
#define UCR_01_FRONT_AERO_TEMPERATURE3_NAME "Temperature3"
#define UCR_01_FRONT_STRAIN_GAUGES1_GAUGE1_NAME "Gauge1"
#define UCR_01_FRONT_STRAIN_GAUGES1_GAUGE2_NAME "Gauge2"
#define UCR_01_FRONT_STRAIN_GAUGES1_GAUGE3_NAME "Gauge3"
#define UCR_01_FRONT_STRAIN_GAUGES1_GAUGE4_NAME "Gauge4"
#define UCR_01_FRONT_STRAIN_GAUGES1_GAUGE5_NAME "Gauge5"
#define UCR_01_FRONT_STRAIN_GAUGES1_GAUGE6_NAME "Gauge6"
#define UCR_01_FRONT_STRAIN_GAUGES2_GAUGE1_NAME "Gauge1"
#define UCR_01_FRONT_STRAIN_GAUGES2_GAUGE2_NAME "Gauge2"
#define UCR_01_FRONT_STRAIN_GAUGES2_GAUGE3_NAME "Gauge3"
#define UCR_01_FRONT_STRAIN_GAUGES2_GAUGE4_NAME "Gauge4"
#define UCR_01_FRONT_STRAIN_GAUGES2_GAUGE5_NAME "Gauge5"
#define UCR_01_FRONT_STRAIN_GAUGES2_GAUGE6_NAME "Gauge6"

/**
 * Signals in message FrontAnalog.
 *
 * All signal values are as on the CAN bus.
 */
struct ucr_01_front_analog_t {
    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint16_t analog1;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint16_t analog2;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint16_t analog3;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint16_t analog4;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint16_t analog5;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint16_t analog6;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint16_t analog7;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint16_t analog8;
};

/**
 * Signals in message FrontFrequency.
 *
 * All signal values are as on the CAN bus.
 */
struct ucr_01_front_frequency_t {
    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t frequency1;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t frequency2;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t frequency3;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t frequency4;
};

/**
 * Signals in message FrontAero.
 *
 * All signal values are as on the CAN bus.
 */
struct ucr_01_front_aero_t {
    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int32_t pressure1;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int32_t pressure2;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int32_t pressure3;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t temperature1;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t temperature2;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    int16_t temperature3;
};

/**
 * Signals in message FrontStrainGauges1.
 *
 * All signal values are as on the CAN bus.
 */
struct ucr_01_front_strain_gauges1_t {
    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t gauge1;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t gauge2;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t gauge3;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t gauge4;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t gauge5;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t gauge6;
};

/**
 * Signals in message FrontStrainGauges2.
 *
 * All signal values are as on the CAN bus.
 */
struct ucr_01_front_strain_gauges2_t {
    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t gauge1;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t gauge2;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t gauge3;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t gauge4;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t gauge5;

    /**
     * Range: -
     * Scale: 1
     * Offset: 0
     */
    uint32_t gauge6;
};

/**
 * Pack message FrontAnalog.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int ucr_01_front_analog_pack(
    uint8_t *dst_p,
    const struct ucr_01_front_analog_t *src_p,
    size_t size);

/**
 * Unpack message FrontAnalog.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int ucr_01_front_analog_unpack(
    struct ucr_01_front_analog_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Init message fields to default values from FrontAnalog.
 *
 * @param[in] msg_p Message to init.
 *
 * @return zero(0) on success or (-1) in case of nullptr argument.
 */
int ucr_01_front_analog_init(struct ucr_01_front_analog_t *msg_p);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t ucr_01_front_analog_analog1_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_analog_analog1_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_analog_analog1_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t ucr_01_front_analog_analog2_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_analog_analog2_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_analog_analog2_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t ucr_01_front_analog_analog3_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_analog_analog3_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_analog_analog3_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t ucr_01_front_analog_analog4_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_analog_analog4_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_analog_analog4_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t ucr_01_front_analog_analog5_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_analog_analog5_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_analog_analog5_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t ucr_01_front_analog_analog6_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_analog_analog6_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_analog_analog6_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t ucr_01_front_analog_analog7_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_analog_analog7_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_analog_analog7_is_in_range(uint16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint16_t ucr_01_front_analog_analog8_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_analog_analog8_decode(uint16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_analog_analog8_is_in_range(uint16_t value);


/**
 * Pack message FrontFrequency.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int ucr_01_front_frequency_pack(
    uint8_t *dst_p,
    const struct ucr_01_front_frequency_t *src_p,
    size_t size);

/**
 * Unpack message FrontFrequency.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int ucr_01_front_frequency_unpack(
    struct ucr_01_front_frequency_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Init message fields to default values from FrontFrequency.
 *
 * @param[in] msg_p Message to init.
 *
 * @return zero(0) on success or (-1) in case of nullptr argument.
 */
int ucr_01_front_frequency_init(struct ucr_01_front_frequency_t *msg_p);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_frequency_frequency1_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_frequency_frequency1_decode(uint32_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_frequency_frequency1_is_in_range(uint32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_frequency_frequency2_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_frequency_frequency2_decode(uint32_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_frequency_frequency2_is_in_range(uint32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_frequency_frequency3_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_frequency_frequency3_decode(uint32_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_frequency_frequency3_is_in_range(uint32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_frequency_frequency4_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_frequency_frequency4_decode(uint32_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_frequency_frequency4_is_in_range(uint32_t value);

/**
 * Pack message FrontAero.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int ucr_01_front_aero_pack(
    uint8_t *dst_p,
    const struct ucr_01_front_aero_t *src_p,
    size_t size);

/**
 * Unpack message FrontAero.
 *
 * @param[out] dst_p Object to unpack the message into.
 * @param[in] src_p Message to unpack.
 * @param[in] size Size of src_p.
 *
 * @return zero(0) or negative error code.
 */
int ucr_01_front_aero_unpack(
    struct ucr_01_front_aero_t *dst_p,
    const uint8_t *src_p,
    size_t size);

/**
 * Init message fields to default values from FrontAero.
 *
 * @param[in] msg_p Message to init.
 *
 * @return zero(0) on success or (-1) in case of nullptr argument.
 */
int ucr_01_front_aero_init(struct ucr_01_front_aero_t *msg_p);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int32_t ucr_01_front_aero_pressure1_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_aero_pressure1_decode(int32_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_aero_pressure1_is_in_range(int32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int32_t ucr_01_front_aero_pressure2_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_aero_pressure2_decode(int32_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_aero_pressure2_is_in_range(int32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int32_t ucr_01_front_aero_pressure3_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_aero_pressure3_decode(int32_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_aero_pressure3_is_in_range(int32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t ucr_01_front_aero_temperature1_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_aero_temperature1_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_aero_temperature1_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t ucr_01_front_aero_temperature2_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_aero_temperature2_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_aero_temperature2_is_in_range(int16_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
int16_t ucr_01_front_aero_temperature3_encode(double value);

/**
 * Decode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to decode.
 *
 * @return Decoded signal.
 */
double ucr_01_front_aero_temperature3_decode(int16_t value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_aero_temperature3_is_in_range(int16_t value);

/**
 * Pack message FrontStrainGauges1.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int ucr_01_front_strain_gauges1_pack(
    uint8_t *dst_p,
    const struct ucr_01_front_strain_gauges1_t *src_p,
    size_t size);

/**
 * Init message fields to default values from FrontStrainGauges1.
 *
 * @param[in] msg_p Message to init.
 *
 * @return zero(0) on success or (-1) in case of nullptr argument.
 */
int ucr_01_front_strain_gauges1_init(struct ucr_01_front_strain_gauges1_t *msg_p);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_strain_gauges1_gauge1_encode(double value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_strain_gauges1_gauge1_is_in_range(uint32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_strain_gauges1_gauge2_encode(double value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_strain_gauges1_gauge2_is_in_range(uint32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_strain_gauges1_gauge3_encode(double value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_strain_gauges1_gauge3_is_in_range(uint32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_strain_gauges1_gauge4_encode(double value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_strain_gauges1_gauge4_is_in_range(uint32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_strain_gauges1_gauge5_encode(double value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_strain_gauges1_gauge5_is_in_range(uint32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_strain_gauges1_gauge6_encode(double value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_strain_gauges1_gauge6_is_in_range(uint32_t value);

/**
 * Pack message FrontStrainGauges2.
 *
 * @param[out] dst_p Buffer to pack the message into.
 * @param[in] src_p Data to pack.
 * @param[in] size Size of dst_p.
 *
 * @return Size of packed data, or negative error code.
 */
int ucr_01_front_strain_gauges2_pack(
    uint8_t *dst_p,
    const struct ucr_01_front_strain_gauges2_t *src_p,
    size_t size);

/**
 * Init message fields to default values from FrontStrainGauges2.
 *
 * @param[in] msg_p Message to init.
 *
 * @return zero(0) on success or (-1) in case of nullptr argument.
 */
int ucr_01_front_strain_gauges2_init(struct ucr_01_front_strain_gauges2_t *msg_p);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_strain_gauges2_gauge1_encode(double value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_strain_gauges2_gauge1_is_in_range(uint32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_strain_gauges2_gauge2_encode(double value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_strain_gauges2_gauge2_is_in_range(uint32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_strain_gauges2_gauge3_encode(double value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_strain_gauges2_gauge3_is_in_range(uint32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_strain_gauges2_gauge4_encode(double value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_strain_gauges2_gauge4_is_in_range(uint32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_strain_gauges2_gauge5_encode(double value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_strain_gauges2_gauge5_is_in_range(uint32_t value);

/**
 * Encode given signal by applying scaling and offset.
 *
 * @param[in] value Signal to encode.
 *
 * @return Encoded signal.
 */
uint32_t ucr_01_front_strain_gauges2_gauge6_encode(double value);

/**
 * Check that given signal is in allowed range.
 *
 * @param[in] value Signal to check.
 *
 * @return true if in range, false otherwise.
 */
bool ucr_01_front_strain_gauges2_gauge6_is_in_range(uint32_t value);



#ifdef __cplusplus
}
#endif

#endif




#endif /* VENDOR_GENERATED_CAN_TOOLS_CAN_H_ */
