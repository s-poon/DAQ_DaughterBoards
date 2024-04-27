################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/User/aero/aero_sensors.c 

OBJS += \
./Core/User/aero/aero_sensors.o 

C_DEPS += \
./Core/User/aero/aero_sensors.d 


# Each subdirectory must supply rules for building sources it contributes
Core/User/aero/%.o Core/User/aero/%.su Core/User/aero/%.cyclo: ../Core/User/aero/%.c Core/User/aero/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Core/User -I../Core/User/ucr_common -I../Core/User/can -I../Core/User/app -I../Core/User/aero -I../Core/User/adc -I../AZURE_RTOS/App -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m4/gnu/inc/ -I../Core/User/frequency -I../Middlewares/ST/threadx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-User-2f-aero

clean-Core-2f-User-2f-aero:
	-$(RM) ./Core/User/aero/aero_sensors.cyclo ./Core/User/aero/aero_sensors.d ./Core/User/aero/aero_sensors.o ./Core/User/aero/aero_sensors.su

.PHONY: clean-Core-2f-User-2f-aero

