#include "ExADC.hpp"

class ADS114S08: public ExADC{
    public:
        int32_t ReadADCData(
            uint8_t* deviceStatus,
            uint8_t mode
        );
};