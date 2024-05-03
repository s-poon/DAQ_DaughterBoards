/*
 * strain_gauges.c
 *
 *  Created on: May 2, 2024
 *      Author: Steven
 */


#include "strain_gauges.h"
#include "strain_gauges_datatypes.h"
#include "ucr_common.h"
#include <stdint.h>

ads124S08Control_t externalADC1, externalADC2;

uint8_t InitDevice(){
	externalADC1.registers[ID_ADDR_MASK] = 0x08;
	externalADC1.registers[STATUS_ADDR_MASK] = 0x80;
	externalADC1.registers[INPMUX_ADDR_MASK]= 0x01;
	externalADC1.registers[PGA_ADDR_MASK] = 0x00;
	externalADC1.registers[DATARATE_ADDR_MASK] = 0x14;
	externalADC1.registers[REF_ADDR_MASK] = 0x10;
	externalADC1.registers[IDACMAG_ADDR_MASK] = 0x00;
	externalADC1.registers[IDACMUX_ADDR_MASK] = 0xFF;
	externalADC1.registers[VBIAS_ADDR_MASK] = 0x00;
	externalADC1.registers[SYS_ADDR_MASK] = 0x10;
	externalADC1.registers[OFCAL0_ADDR_MASK] = 0x00;
	externalADC1.registers[OFCAL1_ADDR_MASK] = 0x00;
	externalADC1.registers[OFCAL2_ADDR_MASK] = 0x00;
	externalADC1.registers[FSCAL0_ADDR_MASK] = 0x00;
	externalADC1.registers[FSCAL1_ADDR_MASK] = 0x00;
	externalADC1.registers[FSCAL2_ADDR_MASK] = 0x40;
	externalADC1.registers[GPIODAT_ADDR_MASK] = 0x00;
	externalADC1.registers[GPIOCON_ADDR_MASK] = 0x00;

    externalADC1.csPinPort = CS1_GPIO_Port;
    externalADC1.csPin = CS1_Pin;
    externalADC1.startSyncPinPort = STARTSYNC_1_GPIO_Port;
    externalADC1.startSyncPin = STARTSYNC_1_Pin;
    externalADC1.resetPinPort = RESET1_GPIO_Port;
    externalADC1.resetPin = RESET1_Pin;
    externalADC1.drdyPinPort = DRDY1_GPIO_Port;
    externalADC1.drdyPin = DRDY1_Pin;
    
	externalADC2.registers[ID_ADDR_MASK] = 0x08;
	externalADC2.registers[STATUS_ADDR_MASK] = 0x80;
	externalADC2.registers[INPMUX_ADDR_MASK]= 0x01;
	externalADC2.registers[PGA_ADDR_MASK] = 0x00;
	externalADC2.registers[DATARATE_ADDR_MASK] = 0x14;
	externalADC2.registers[REF_ADDR_MASK] = 0x10;
	externalADC2.registers[IDACMAG_ADDR_MASK] = 0x00;
	externalADC2.registers[IDACMUX_ADDR_MASK] = 0xFF;
	externalADC2.registers[VBIAS_ADDR_MASK] = 0x00;
	externalADC2.registers[SYS_ADDR_MASK] = 0x10;
	externalADC2.registers[OFCAL0_ADDR_MASK] = 0x00;
	externalADC2.registers[OFCAL1_ADDR_MASK] = 0x00;
	externalADC2.registers[OFCAL2_ADDR_MASK] = 0x00;
	externalADC2.registers[FSCAL0_ADDR_MASK] = 0x00;
	externalADC2.registers[FSCAL1_ADDR_MASK] = 0x00;
	externalADC2.registers[FSCAL2_ADDR_MASK] = 0x40;
	externalADC2.registers[GPIODAT_ADDR_MASK] = 0x00;
	externalADC2.registers[GPIOCON_ADDR_MASK] = 0x00;

    externalADC2.csPinPort = CS2_GPIO_Port;
    externalADC2.csPin = CS2_Pin;
    externalADC2.startSyncPinPort = STARTSYNC_2_GPIO_Port;
    externalADC2.startSyncPin = STARTSYNC_2_Pin;
    externalADC2.resetPinPort = RESET2_GPIO_Port;
    externalADC2.resetPin = RESET2_Pin;
    externalADC2.drdyPinPort = DRDY2_GPIO_Port;
    externalADC2.drdyPin = DRDY2_Pin;
}

uint8_t readRegister(
    ads124S08Control_t device,
    uint16_t registerNum,
    uint16_t readCount,
    uint8_t* data
){
    uint8_t retVal = UCR_OK;

    return retVal;
}


