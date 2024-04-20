################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/User/ADC/analog_control.c 

OBJS += \
./Core/User/ADC/analog_control.o 

C_DEPS += \
./Core/User/ADC/analog_control.d 


# Each subdirectory must supply rules for building sources it contributes
Core/User/ADC/%.o Core/User/ADC/%.su Core/User/ADC/%.cyclo: ../Core/User/ADC/%.c Core/User/ADC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Core/User/App -I../Core/User/Aero -I../Core/User/ADC -I../AZURE_RTOS/App -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m4/gnu/inc/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-User-2f-ADC

clean-Core-2f-User-2f-ADC:
	-$(RM) ./Core/User/ADC/analog_control.cyclo ./Core/User/ADC/analog_control.d ./Core/User/ADC/analog_control.o ./Core/User/ADC/analog_control.su

.PHONY: clean-Core-2f-User-2f-ADC

