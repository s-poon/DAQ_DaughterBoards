################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/User/app/threadx.c 

OBJS += \
./Core/User/app/threadx.o 

C_DEPS += \
./Core/User/app/threadx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/User/app/%.o Core/User/app/%.su Core/User/app/%.cyclo: ../Core/User/app/%.c Core/User/app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Core/User -I../Core/User/ucr_common -I../Core/User/can -I../Core/User/app -I../Core/User/aero -I../Core/User/adc -I../AZURE_RTOS/App -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m4/gnu/inc/ -I../Core/User/frequency -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-User-2f-app

clean-Core-2f-User-2f-app:
	-$(RM) ./Core/User/app/threadx.cyclo ./Core/User/app/threadx.d ./Core/User/app/threadx.o ./Core/User/app/threadx.su

.PHONY: clean-Core-2f-User-2f-app

