#include "GPIOPin.hpp"

GPIOPin::GPIOPin(GPIO_TypeDef* port_, uint16_t pin_){
    port = port_;
    pin = pin_;
}

bool GPIOPin::Read(){
    return HAL_GPIO_ReadPin(port, pin);
}

void GPIOPin::Set(){
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
}

void GPIOPin::Clear(){
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}

void GPIOPin::Toggle(){
    HAL_GPIO_TogglePin(port, pin);
}
