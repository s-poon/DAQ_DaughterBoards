################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/User/gpio/exti.c 

OBJS += \
./Core/User/gpio/exti.o 

C_DEPS += \
./Core/User/gpio/exti.d 


# Each subdirectory must supply rules for building sources it contributes
Core/User/gpio/%.o Core/User/gpio/%.su Core/User/gpio/%.cyclo: ../Core/User/gpio/%.c Core/User/gpio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Core/User/vendor_generated/can_tools -I../Core/User/vendor_generated/ti -I../Core/User -I../Core/User/ucr_common -I../Core/User/can -I../Core/User/strain_gauges -I../Core/User/gpio -I../Core/User/app -I../Core/User/aero -I../Core/User/adc -I../AZURE_RTOS/App -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m4/gnu/inc/ -I../Core/User/frequency -I../Middlewares/ST/threadx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-User-2f-gpio

clean-Core-2f-User-2f-gpio:
	-$(RM) ./Core/User/gpio/exti.cyclo ./Core/User/gpio/exti.d ./Core/User/gpio/exti.o ./Core/User/gpio/exti.su

.PHONY: clean-Core-2f-User-2f-gpio

