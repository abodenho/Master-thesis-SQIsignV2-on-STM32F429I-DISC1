################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/st7789h2/st7789h2.c 

OBJS += \
./Drivers/BSP/Components/st7789h2/st7789h2.o 

C_DEPS += \
./Drivers/BSP/Components/st7789h2/st7789h2.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/st7789h2/%.o Drivers/BSP/Components/st7789h2/%.su Drivers/BSP/Components/st7789h2/%.cyclo: ../Drivers/BSP/Components/st7789h2/%.c Drivers/BSP/Components/st7789h2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDISC -DDEBUG -DSTM32 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/abodenho/STM32CubeIDE/workspace_1.17.0/SQIsign_level1_STM32F429I-DISC1/Drivers/BSP/STM32F429I-Discovery" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-st7789h2

clean-Drivers-2f-BSP-2f-Components-2f-st7789h2:
	-$(RM) ./Drivers/BSP/Components/st7789h2/st7789h2.cyclo ./Drivers/BSP/Components/st7789h2/st7789h2.d ./Drivers/BSP/Components/st7789h2/st7789h2.o ./Drivers/BSP/Components/st7789h2/st7789h2.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-st7789h2

