/*
 *  @file ucr_dsp_lib.c
 *
 *  @brief  Library for Digital Signal Processing
 */

#include <stdint.h>

bool rising_edge_detect(
    bool input,
    bool prev_input);

bool falling_edge_detect(
    bool input,
    bool prev_input);

uint8_t symmetric_debounce(
    bool input,
    bool* output,
    uint8_t task_rate,
    uint16_t debounce_time,
    uint16_t* counter);