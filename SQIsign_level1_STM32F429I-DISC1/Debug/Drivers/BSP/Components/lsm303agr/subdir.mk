################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/lsm303agr/lsm303agr.c 

OBJS += \
./Drivers/BSP/Components/lsm303agr/lsm303agr.o 

C_DEPS += \
./Drivers/BSP/Components/lsm303agr/lsm303agr.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/lsm303agr/%.o Drivers/BSP/Components/lsm303agr/%.su Drivers/BSP/Components/lsm303agr/%.cyclo: ../Drivers/BSP/Components/lsm303agr/%.c Drivers/BSP/Components/lsm303agr/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDISC -DDEBUG -DSTM32 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/abodenho/STM32CubeIDE/workspace_1.17.0/SQIsign_level1_STM32F429I-DISC1/Drivers/BSP/STM32F429I-Discovery" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-lsm303agr

clean-Drivers-2f-BSP-2f-Components-2f-lsm303agr:
	-$(RM) ./Drivers/BSP/Components/lsm303agr/lsm303agr.cyclo ./Drivers/BSP/Components/lsm303agr/lsm303agr.d ./Drivers/BSP/Components/lsm303agr/lsm303agr.o ./Drivers/BSP/Components/lsm303agr/lsm303agr.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-lsm303agr

