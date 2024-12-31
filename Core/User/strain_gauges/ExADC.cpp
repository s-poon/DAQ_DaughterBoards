#include "ExADC.hpp"


ExADC::ExADC(GPIOPin startSyncPin, GPIOPin csPin, GPIOPin drdyPin, GPIOPin resetPin)
    : startSyncPin(startSyncPin), csPin(csPin), drdyPin(drdyPin), resetPin(resetPin)
{
    RestoreRegisterDefaults();
};

bool ExADC::StartUpRoutine(){
    uint8_t status;

    // Delay for power supply settling
    HAL_Delay(10);

    // Toggle nReset pin to reset registers
    ToggleReset();

    // Delay for post reset
    HAL_Delay(10);

    // Check if device is ready
    status = ReadRegister(REG_ADDR_STATUS);
    if(status & ADS_nRDY_MASK){
        return false;
    }

    // Restore register defaults
    RestoreRegisterDefaults();

    // Clear Power on Reset flag
    WriteRegister(REG_ADDR_STATUS, 0x00);
    
    return status;
}

void ExADC::ToggleReset(){
    resetPin.Clear();
    HAL_Delay(ADS_RESET_TIME);
    resetPin.Set();
}

uint8_t ExADC::ReadRegister(
    uint16_t address
){
	uint8_t txData[COMMAND_LENGTH + 1] = { OPCODE_RREG | (address & OPCODE_RWREG_MASK), 0, 0 };
	uint8_t rxData[COMMAND_LENGTH + 1] = {0, 0, 0};
	csPin.Clear();
	HAL_SPI_TransmitReceive(&hspi4, txData, rxData, COMMAND_LENGTH + 1, 500);
	csPin.Set();
	registers[address] = rxData[COMMAND_LENGTH];
    return rxData[COMMAND_LENGTH];
}

uint8_t ExADC::ReadMultipleRegisters(
    uint16_t startAddress,
    uint16_t readCount
){
    uint8_t retVal = UCR_OK;
    uint8_t txData[COMMAND_LENGTH + NUM_REGISTERS] = {0};
    uint8_t rxData[COMMAND_LENGTH + NUM_REGISTERS] = {0};

    txData[0] = OPCODE_RREG | (startAddress & OPCODE_RWREG_MASK);
    txData[1] = readCount - 1;

    csPin.Clear();
    HAL_SPI_TransmitReceive(&hspi4, txData, rxData, COMMAND_LENGTH + 1, 500);
    csPin.Set();
    for(int i = 0; i < readCount; i ++){
        registers[i + startAddress] = rxData[COMMAND_LENGTH + i];
    }
    return retVal;
}

uint8_t ExADC::WriteRegister(
	uint16_t address,
	uint8_t data
){
	uint8_t retVal = UCR_OK;
	uint8_t txData[COMMAND_LENGTH + 1] = { OPCODE_WREG | (address & OPCODE_RWREG_MASK), 0, data};
	uint8_t rxData[COMMAND_LENGTH + 1] = {0, 0, 0};

	csPin.Clear();
	HAL_SPI_TransmitReceive(&hspi4, txData, rxData, COMMAND_LENGTH + 1, 500);
	csPin.Set();
	registers[address] = txData[COMMAND_LENGTH];
	return retVal;
}


uint8_t ExADC::WriteMultipleRegisters(
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
        registers[i] = data[i];
    }

    csPin.Clear();
    HAL_SPI_TransmitReceive(&hspi4, txData, rxData, COMMAND_LENGTH + writeCount, 500);
    csPin.Set();
    return retVal;
}


void ExADC::RestoreRegisterDefaults(){
	/* Default register settings */
    registers[REG_ADDR_ID]       = ID_DEFAULT;
	registers[REG_ADDR_STATUS]   = STATUS_DEFAULT;
	registers[REG_ADDR_INPMUX]   = INPMUX_DEFAULT;
	registers[REG_ADDR_PGA]      = PGA_DEFAULT;
	registers[REG_ADDR_DATARATE] = DATARATE_DEFAULT;
	registers[REG_ADDR_REF]      = REF_DEFAULT;
	registers[REG_ADDR_IDACMAG]  = IDACMAG_DEFAULT;
	registers[REG_ADDR_IDACMUX]  = IDACMUX_DEFAULT;
	registers[REG_ADDR_VBIAS]    = VBIAS_DEFAULT;
	registers[REG_ADDR_SYS]      = SYS_DEFAULT;
	registers[REG_ADDR_OFCAL0]   = OFCAL0_DEFAULT;
	registers[REG_ADDR_OFCAL1]   = OFCAL1_DEFAULT;
	registers[REG_ADDR_OFCAL2]   = OFCAL2_DEFAULT;
	registers[REG_ADDR_FSCAL0]   = FSCAL0_DEFAULT;
	registers[REG_ADDR_FSCAL1]   = FSCAL1_DEFAULT;
	registers[REG_ADDR_FSCAL2]   = FSCAL2_DEFAULT;
	registers[REG_ADDR_GPIODAT]  = GPIODAT_DEFAULT;
	registers[REG_ADDR_GPIOCON]  = GPIOCON_DEFAULT;
}
