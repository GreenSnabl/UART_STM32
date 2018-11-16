################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Components/lsm303dlhc/lsm303dlhc.c 

OBJS += \
./Utilities/Components/lsm303dlhc/lsm303dlhc.o 

C_DEPS += \
./Utilities/Components/lsm303dlhc/lsm303dlhc.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Components/lsm303dlhc/%.o: ../Utilities/Components/lsm303dlhc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F3 -DSTM32F30 -DSTM32F303VCTx -DSTM32F3DISCOVERY -DDEBUG -DSTM32F303xC -DUSE_HAL_DRIVER -I"/home/snbl/HDD/Programming/STM32Projects/Timer/HAL_Driver/Inc/Legacy" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/Utilities/STM32F3-Discovery" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/Utilities/Components/lsm303dlhc" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/Utilities/Components/Common" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/Utilities/Components/l3gd20" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/inc" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/CMSIS/device" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/CMSIS/core" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


