#include "ADS114S08.hpp"
#include "../../vendor_generated/ti/crc.h"

//ADS114S08::ADS114S08(GPIOPin startSyncPin, GPIOPin csPin, GPIOPin drdyPin, GPIOPin resetPin)
//    : startSyncPin(startSyncPin), csPin(csPin), drdyPin(drdyPin), resetPin(resetPin)
//{
//    RestoreRegisterDefaults();
//};

int32_t ADS114S08::ReadADCData(
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

    byteOptions = (registers[REG_ADDR_SYS] & ADS_SENDSTATUS_MASK << 1) 
                    | (registers[REG_ADDR_SYS] & ADS_CRC_MASK);

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
    csPin.Clear();
    HAL_SPI_TransmitReceive(&hspi4, txData, rxData, byteLength, 500);
    csPin.Set();

    if(statusByteEnabled && deviceStatus){
        deviceStatus[0] = rxData[dataPosition - 1];
    }

    if (rxData[dataPosition] & 0x80u ) {
    	signByte = 0xFF000000; 
    } else { 
    	signByte = 0x00000000; 
    }

    if(registers[REG_ADDR_SYS] & ADS_CRC_MASK){
        if(registers[REG_ADDR_SYS] & ADS_SENDSTATUS_MASK){
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
