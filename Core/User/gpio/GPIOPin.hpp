#include "main.h"
#include "stdint.h"

class GPIOPin{
    public:
        GPIOPin(GPIO_TypeDef* port_, uint16_t pin_);
        bool Read();
        void Set();
        void Clear();
        void Toggle();

    private:
        GPIO_TypeDef* port;
        uint16_t pin;
};
