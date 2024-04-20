################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/User/Aero/aero_sensors.c 

OBJS += \
./Core/User/Aero/aero_sensors.o 

C_DEPS += \
./Core/User/Aero/aero_sensors.d 


# Each subdirectory must supply rules for building sources it contributes
Core/User/Aero/%.o Core/User/Aero/%.su Core/User/Aero/%.cyclo: ../Core/User/Aero/%.c Core/User/Aero/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Core/User/App -I../Core/User/Aero -I../Core/User/ADC -I../AZURE_RTOS/App -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m4/gnu/inc/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-User-2f-Aero

clean-Core-2f-User-2f-Aero:
	-$(RM) ./Core/User/Aero/aero_sensors.cyclo ./Core/User/Aero/aero_sensors.d ./Core/User/Aero/aero_sensors.o ./Core/User/Aero/aero_sensors.su

.PHONY: clean-Core-2f-User-2f-Aero

