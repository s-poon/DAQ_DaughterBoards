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
#include "../../vendor_generated/ti/crc.h"


ads124S08Control_t externalADC1, externalADC2;
const uint8_t adcMuxStates[] = {
	ADS_P_AIN0 + ADS_N_AIN1,
	ADS_P_AIN2 + ADS_N_AIN3,
	ADS_P_AIN4 + ADS_N_AIN5,
	ADS_P_AIN6 + ADS_N_AIN7,
	ADS_P_AIN8 + ADS_N_AIN9,
	ADS_P_AIN10 + ADS_N_AIN11
};

const uint8_t registerStates[] = {
    0x00

};

bool StartUpRoutine(ads124S08Control_t* device){
    uint8_t initRegisterMap[NUM_REGISTERS] = {0};
    uint8_t status, i;

    // Delay for power supply settling
    HAL_Delay(10);

    // Toggle nReset pin to reset registers
    ToggleReset(device);

    // Delay for post reset
    HAL_Delay(10);

    // Check if device is ready
    status = ReadRegister(device, REG_ADDR_STATUS);
    if(status & ADS_nRDY_MASK){
        return false;
    }

    // 
    RestoreRegisterDefaults(device);

    // Clear Power on Reset flag
    WriteRegister(device, REG_ADDR_STATUS, 0x00);



    
    return status;
}

void ToggleReset(ads124S08Control_t* device){
    HAL_GPIO_WritePin(device->resetPinPort, device->resetPin, RESET);
    HAL_Delay(ADS_RESET_TIME);
    HAL_GPIO_WritePin(device->resetPinPort, device->resetPin, SET);
}

uint8_t ReadRegister(
    ads124S08Control_t* device,
    uint16_t address
){
	uint8_t txData[COMMAND_LENGTH + 1] = { OPCODE_RREG | (address & OPCODE_RWREG_MASK), 0, 0 };
	uint8_t rxData[COMMAND_LENGTH + 1] = {0, 0, 0};
	HAL_StatusTypeDef thing;
	HAL_GPIO_WritePin(device->csPinPort, device->csPin, 0);
	thing = HAL_SPI_TransmitReceive(&hspi4, txData, rxData, COMMAND_LENGTH + 1, 500);
	HAL_GPIO_WritePin(device->csPinPort, device->csPin, 1);
	device->registers[address] = rxData[COMMAND_LENGTH];
    return rxData[COMMAND_LENGTH];
}

uint8_t ReadMultipleRegisters(
    ads124S08Control_t* device,
    uint16_t startAddress,
    uint16_t readCount
){
    uint8_t retVal = UCR_OK;
    uint8_t txData[COMMAND_LENGTH + NUM_REGISTERS] = {0};
    uint8_t rxData[COMMAND_LENGTH + NUM_REGISTERS] = {0};

    txData[0] = OPCODE_RREG | (startAddress & OPCODE_RWREG_MASK);
    txData[1] = readCount - 1;

    HAL_GPIO_WritePin(device->csPinPort, device->csPin, 0);
    HAL_SPI_TransmitReceive(&hspi4, txData, rxData, COMMAND_LENGTH + 1, 500);
    HAL_GPIO_WritePin(device->csPinPort, device->csPin, 1);
    for(int i = 0; i < readCount; i ++){
        device->registers[i + startAddress] = rxData[COMMAND_LENGTH + i];
    }
    return retVal;
}


uint8_t WriteRegister(
	ads124S08Control_t* device,
	uint16_t address,
	uint8_t data
){
	uint8_t retVal = UCR_OK;
	uint8_t txData[COMMAND_LENGTH + 1] = { OPCODE_WREG | (address & OPCODE_RWREG_MASK), 0, data};
	uint8_t rxData[COMMAND_LENGTH + 1] = {0, 0, 0};

	HAL_GPIO_WritePin(device->csPinPort, device->csPin, 0);
	HAL_SPI_TransmitReceive(&hspi4, txData, rxData, COMMAND_LENGTH + 1, 500);
	HAL_GPIO_WritePin(device->csPinPort, device->csPin, 1);
	device->registers[address] = txData[COMMAND_LENGTH];
	return retVal;
}

uint8_t WriteMultipleRegisters(
    ads124S08Control_t* device,
    uint16_t startAddress,
    uint16_t writeCount,
    uint8_t* data
){
    uint8_t retVal = UCR_OK;
    uint8_t txData[COMMAND_LENGTH + NUM_REGISTERS] = { 0 };
    uint8_t rxData[COMMAND_LENGTH + NUM_REGISTERS] = { 0 };
    uint8_t j = 0;

    txData[0] = OPCODE_WREG | (startAddress & OPCODE_RWREG_MASK);
    txData[1] = writeCount - 1;
    for(int i = startAddress; i < startAddress + writeCount; i ++){
        txData[COMMAND_LENGTH + j++] = data[i];
        device->registers[i] = data[i];
    }

    HAL_GPIO_WritePin(device->csPinPort, device->csPin, 0);
    HAL_SPI_TransmitReceive(&hspi4, txData, rxData, COMMAND_LENGTH + writeCount, 500);
    HAL_GPIO_WritePin(device->csPinPort, device->csPin, 1);
    return retVal;
}

uint8_t SendCommand(
	ads124S08Control_t* device,
	uint8_t command
){
	uint8_t retVal = UCR_OK;
	HAL_GPIO_WritePin(device->csPinPort, device->csPin, 0);
    HAL_SPI_Transmit(&hspi4, &command, 1, 500);
    HAL_GPIO_WritePin(device->csPinPort, device->csPin, 1);
	return retVal;
}

//void readWriteData(
//	ads124S08Control_t* device,
//	uint8_t*
//){
//
//}

int32_t ReadADCData(
	ads124S08Control_t* device,
	uint8_t* deviceStatus,
	uint8_t mode
){
    uint8_t txData[RDATA_COMMAND_LENGTH + STATUS_LENGTH + DATA_LENGTH + CRC_LENGTH] = {0};
    uint8_t rxData[RDATA_COMMAND_LENGTH + STATUS_LENGTH + DATA_LENGTH + CRC_LENGTH] = {0};
    uint8_t byteLength;
    uint8_t dataPosition;
    uint8_t byteOptions;
    uint8_t data[5];
    bool statusByteEnabled = false;
    int32_t signByte, upperByte, middleByte, lowerByte;

    byteOptions = (device->registers[REG_ADDR_SYS] & ADS_SENDSTATUS_MASK << 1) 
                    | (device->registers[REG_ADDR_SYS] & ADS_CRC_MASK);

    switch(byteOptions){
        case 0:
            byteLength = DATA_LENGTH;
            dataPosition = 0;
            break;
        case 1: 
            byteLength = DATA_LENGTH + CRC_LENGTH;
            dataPosition = 0;
            break;
        case 2:
            byteLength = STATUS_LENGTH + DATA_LENGTH;
            dataPosition = 1;
            statusByteEnabled = true;
            break;
        case 3:
            byteLength = STATUS_LENGTH + DATA_LENGTH + CRC_LENGTH;
            dataPosition = 1;
            statusByteEnabled = true;
            break;
    }
    if(mode == COMMAND){
        txData[0] = OPCODE_RDATA;
        byteLength ++;
        dataPosition ++;
    }
    HAL_GPIO_WritePin(device->csPinPort, device->csPin, RESET);
    HAL_SPI_TransmitReceive(&hspi4, txData, rxData, byteLength, 500);
    HAL_GPIO_WritePin(device->csPinPort, device->csPin, SET);

    if(statusByteEnabled && deviceStatus){
        deviceStatus[0] = rxData[dataPosition - 1];
    }

    if (rxData[dataPosition] & 0x80u ) {
    	signByte = 0xFF000000; 
    } else { 
    	signByte = 0x00000000; 
    }

    if(device->registers[REG_ADDR_SYS] & ADS_CRC_MASK){
        if(device->registers[REG_ADDR_SYS] & ADS_SENDSTATUS_MASK){
            data[0] = rxData[dataPosition - 1];
            data[1] = rxData[dataPosition];
            data[2] = rxData[dataPosition + 1];
            data[3] = rxData[dataPosition + 2];
            data[4] = rxData[dataPosition + 3];

            bool error = (bool) getCRC(data, 5, CRC_INITIAL_SEED);
            if ( error ) {
                // if error, report and handle the error
                while (1);
            }
        }else{
            data[0] = rxData[dataPosition];
            data[1] = rxData[dataPosition + 1];
            data[2] = rxData[dataPosition + 2];
            data[3] = rxData[dataPosition + 3];
            bool error = (bool) getCRC(data, 4, CRC_INITIAL_SEED);

            if(error){
                while(1);
            }
        }
    }
    upperByte = ((uint32_t) rxData[dataPosition] & 0xFF) << 16;
    middleByte = ((uint32_t) rxData[dataPosition + 1] & 0xFF) << 8;
    lowerByte = ((uint32_t) rxData[dataPosition + 2] & 0xFF);

	return (signByte + upperByte + middleByte + lowerByte);
}

void RestoreRegisterDefaults(
    ads124S08Control_t* device
){
	/* Default register settings */
    device->registers[REG_ADDR_ID]       = ID_DEFAULT;
	device->registers[REG_ADDR_STATUS]   = STATUS_DEFAULT;
	device->registers[REG_ADDR_INPMUX]   = INPMUX_DEFAULT;
	device->registers[REG_ADDR_PGA]      = PGA_DEFAULT;
	device->registers[REG_ADDR_DATARATE] = DATARATE_DEFAULT;
	device->registers[REG_ADDR_REF]      = REF_DEFAULT;
	device->registers[REG_ADDR_IDACMAG]  = IDACMAG_DEFAULT;
	device->registers[REG_ADDR_IDACMUX]  = IDACMUX_DEFAULT;
	device->registers[REG_ADDR_VBIAS]    = VBIAS_DEFAULT;
	device->registers[REG_ADDR_SYS]      = SYS_DEFAULT;
	device->registers[REG_ADDR_OFCAL0]   = OFCAL0_DEFAULT;
	device->registers[REG_ADDR_OFCAL1]   = OFCAL1_DEFAULT;
	device->registers[REG_ADDR_OFCAL2]   = OFCAL2_DEFAULT;
	device->registers[REG_ADDR_FSCAL0]   = FSCAL0_DEFAULT;
	device->registers[REG_ADDR_FSCAL1]   = FSCAL1_DEFAULT;
	device->registers[REG_ADDR_FSCAL2]   = FSCAL2_DEFAULT;
	device->registers[REG_ADDR_GPIODAT]  = GPIODAT_DEFAULT;
	device->registers[REG_ADDR_GPIOCON]  = GPIOCON_DEFAULT;
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



