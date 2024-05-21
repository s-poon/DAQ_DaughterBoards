/*
 * strain_gauges.c
 *
 *  Created on: May 2, 2024
 *      Author: Steven
 */


#include "strain_gauges.h"
#include "threadx.h"
#include "ucr_common.h"
#include "spi.h"


ads124S08Control_t externalADC1, externalADC2;
const uint8_t adcMuxStates[] = {
	ADS_P_AIN0 + ADS_N_AIN1,
	ADS_P_AIN2 + ADS_N_AIN3,
	ADS_P_AIN4 + ADS_N_AIN5,
	ADS_P_AIN6 + ADS_N_AIN7,
	ADS_P_AIN8 + ADS_N_AIN9,
	ADS_P_AIN10 + ADS_N_AIN11
};

uint8_t InitDevice(){
    uint8_t retVal = UCR_OK;
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
    return retVal;
}

uint8_t ReadRegister(
    ads124S08Control_t* device,
    uint16_t registerNum
){
	uint8_t txData[2];
	uint8_t rxData;

	txData[0] = REGRD_OPCODE_MASK + (registerNum & 0x1f);
	txData[1] = 0x00;

	HAL_GPIO_WritePin(device->csPinPort, device->csPin, 0);
	HAL_SPI_Transmit(&hspi4, txData, 2, 500);
	HAL_SPI_Receive(&hspi4, &rxData, 1, 500);
	HAL_GPIO_WritePin(device->csPinPort, device->csPin, 1);
	device->registers[registerNum] = rxData;
    return rxData;
}

uint8_t ReadRegisters(
    ads124S08Control_t* device,
    uint16_t registerNum,
    uint16_t readCount
){
    uint8_t retVal = UCR_OK;
    uint8_t txData[2];
    uint8_t rxData[readCount];

    txData[0] = REGRD_OPCODE_MASK + (registerNum & 0x1f);
    txData[1] = readCount - 1;

    HAL_GPIO_WritePin(device->csPinPort, device->csPin, 0);
    HAL_SPI_Transmit(&hspi4, txData, 2, 500);
    HAL_SPI_Receive(&hspi4, rxData, readCount, 500);
    HAL_GPIO_WritePin(device->csPinPort, device->csPin, 1);
    for(int i = registerNum; i < registerNum + readCount; i ++){
        device->registers[i] = rxData[i - registerNum];
    }
    return retVal;
}


uint8_t WriteRegister(
	ads124S08Control_t* device,
	uint16_t registerNum,
	uint8_t data
){
	uint8_t retVal = UCR_OK;
    uint8_t txData[3];

    txData[0] = REGWR_OPCODE_MASK + (registerNum & 0x1f);
    txData[1] = 0x00;
    txData[2] = data;

    HAL_GPIO_WritePin(device->csPinPort, device->csPin, 0);
    HAL_SPI_Transmit(&hspi4, txData, 3, 500);
    HAL_GPIO_WritePin(device->csPinPort, device->csPin, 1);
	return retVal;
}

uint8_t WriteRegisters(
    ads124S08Control_t* device,
    uint16_t registerNum,
    uint16_t writeCount,
    uint8_t* data
){
    uint8_t retVal = UCR_OK;
    uint8_t txData[writeCount + 2];

    txData[0] = REGWR_OPCODE_MASK + (registerNum & 0x1f);
    txData[1] = 0x00;
    for(int i = 2; i < writeCount; i ++){
        txData[i] = *data;
        ++data;
    }

    HAL_GPIO_WritePin(device->csPinPort, device->csPin, 0);
    HAL_SPI_Transmit(&hspi4, txData, 3, 500);
    HAL_GPIO_WritePin(device->csPinPort, device->csPin, 1);
    return retVal;
}

uint8_t SendCommand(
	ads124S08Control_t* device,
	uint8_t command
){
	uint8_t retVal = UCR_OK;
	HAL_GPIO_WritePin(device->csPinPort, device->csPin, 0);
    HAL_SPI_Transmit(&hspi4, &command, 3, 500);
    HAL_GPIO_WritePin(device->csPinPort, device->csPin, 1);
	return retVal;
}

void readWriteData(
	ads124S08Control_t* device,
	uint8_t* 
){

}

uint32_t readData(
	ads124S08Control_t* device,
	uint32_t* deviceStatus,
	uint32_t* deviceData,
	uint32_t* deviceCRC
){
    HAL_GPIO_WritePin(device->csPinPort, device->csPin, 0);
//    HAL_SPI_Transmit(&hspi4, &command, 3, 500);

	return 0;
}

void HAL_SPI_TxRxCpltCallback(
    SPI_HandleTypeDef* hspi
){
    if(1 == HAL_GPIO_ReadPin(externalADC1.csPinPort, externalADC1.csPin)){
        tx_semaphore_put(&semaphoreExADC1);
        HAL_GPIO_WritePin(externalADC1.csPinPort, externalADC1.csPin, 1);
    }else{
        tx_semaphore_put(&semaphoreExADC2);
        HAL_GPIO_WritePin(externalADC2.csPinPort, externalADC2.csPin, 1);
    }
}



