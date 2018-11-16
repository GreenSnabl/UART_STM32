################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f303xc.s 

OBJS += \
./startup/startup_stm32f303xc.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"/home/snbl/HDD/Programming/STM32Projects/Timer/HAL_Driver/Inc/Legacy" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/Utilities/STM32F3-Discovery" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/Utilities/Components/lsm303dlhc" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/Utilities/Components/Common" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/Utilities/Components/l3gd20" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/inc" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/CMSIS/device" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/CMSIS/core" -I"/home/snbl/HDD/Programming/STM32Projects/Timer/HAL_Driver/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


