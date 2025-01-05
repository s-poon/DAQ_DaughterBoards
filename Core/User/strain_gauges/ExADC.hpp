#include "main.h"
#include "stdint.h"
#include "GPIOPin.hpp"
#include "strain_gauges.h"
#include "spi.h"
#include "ucr_common.h"


class ExADC{
    public:
        ExADC(GPIOPin startSyncPin, GPIOPin csPin, GPIOPin drdyPin, GPIOPin resetPin);
        virtual ~ExADC() = 0;
        bool StartUpRoutine();
        void ToggleReset();
        void RestoreRegisterDefaults();
        
        virtual int32_t ReadADCData(
            uint8_t* deviceStatus,
            uint8_t mode
        )= 0;

        uint8_t ReadRegister(
            uint8_t address
        );
        uint8_t ReadMultipleRegisters(
            uint8_t startAddress,
            uint8_t readCount
        );
        uint8_t WriteRegister(
            uint8_t address,
            uint8_t data
        );
        uint8_t WriteMultipleRegisters(
            uint8_t startAddress,
            uint8_t writeCount,
            uint8_t* data
        );
        uint8_t SendCommand(
            uint8_t command
        );

        GPIOPin startSyncPin;
        GPIOPin csPin;
        GPIOPin drdyPin;
        GPIOPin resetPin;


    protected:

        uint8_t registers[NUM_REGISTERS];
};
