#include "ExADC.hpp"

class ADS124S08: public ExADC{
    public:
        ADS124S08(GPIOPin startSyncPin, GPIOPin csPin, GPIOPin drdyPin, GPIOPin resetPin);
        int32_t ReadADCData(
            uint8_t* deviceStatus,
            uint8_t mode
        );
};
