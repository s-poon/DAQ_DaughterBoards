/*
 * common.h
 *
 *  Created on: Apr 20, 2024
 *      Author: Steven
 */

#ifndef USER_UCR_COMMON_UCR_COMMON_H_
#define USER_UCR_COMMON_UCR_COMMON_H_

#define UCR_OK              (0u)
#define UCR_NOT_OK          (1u)
#define UCR_NPTR            (2u)

#define TIMCLOCK			(160000000)

typedef struct{
	GPIO_TypeDef*	port;
	uint16_t		pin;
}gpio_control_t;

#endif /* USER_UCR_COMMON_UCR_COMMON_H_ */
