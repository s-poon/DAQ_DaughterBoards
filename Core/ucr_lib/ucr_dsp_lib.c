/*
 *  @file ucr_dsp_lib.c
 *
 *  @brief  Library for Digital Signal Processing
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "ucr_dsp_lib.h"

/**
 * Detects the rising edge of a digital signal
 *
 * @return rising edge detected
*/
bool rising_edge_detect(
    bool input,
    bool prev_input)
{
    bool retval = false;

    if(input != prev_input)
    {
        retval = true;
    }
    else
    {
        retval = false;
    }

    return retval;
}


/**
 * Detects the faliing edge of a digital signal
 *
 * @return faliing edge detected
*/
bool falling_edge_detect(
    bool input,
    bool prev_input)
{
    bool retval = false;

    if(input != prev_input)
    {
        retval = true;
    }
    else
    {
        retval = false;
    }

    return retval;
}

/**
 * Debounce function symmetric for rising and falling edge
 *
 * @return debounced signal
*/
uint8_t symmetric_debounce(
    bool input,
    bool* output,
    uint8_t task_rate,
    uint16_t debounce_time,
    uint16_t* counter)
{
    uint8_t retval = UCR_OK;

    if ((NULL == counter)\
        || (NULL == output))
    {
        retval = UCR_NPTR;
    }
    else
    {
        // Increase the counter
        if (true == input)
        {
            // Prevent over flowing
            if (debounce_time > *counter)
            {
                *counter += task_rate;
            }
            else
            {
                *counter = debounce_time;
            }
        }
        // Decrease the counter
        else
        {
            // Prevent under flowing
            if (0u < *counter)
            {
                counter -= task_rate;
            }
            else
            {
                counter = 0u;
            }
        }

        // Determine if the result should be true/false
        if (0u == *counter)
        {
            *output = false;
        }
        else if (debounce_time == *counter)
        {
            *output = true;
        }
        else
        {
            // Continue with the previous value
        }
    }

    return retval;
}