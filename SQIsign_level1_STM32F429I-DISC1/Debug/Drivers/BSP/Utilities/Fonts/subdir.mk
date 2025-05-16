################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Utilities/Fonts/font12.c \
../Drivers/BSP/Utilities/Fonts/font16.c \
../Drivers/BSP/Utilities/Fonts/font20.c \
../Drivers/BSP/Utilities/Fonts/font24.c \
../Drivers/BSP/Utilities/Fonts/font8.c 

OBJS += \
./Drivers/BSP/Utilities/Fonts/font12.o \
./Drivers/BSP/Utilities/Fonts/font16.o \
./Drivers/BSP/Utilities/Fonts/font20.o \
./Drivers/BSP/Utilities/Fonts/font24.o \
./Drivers/BSP/Utilities/Fonts/font8.o 

C_DEPS += \
./Drivers/BSP/Utilities/Fonts/font12.d \
./Drivers/BSP/Utilities/Fonts/font16.d \
./Drivers/BSP/Utilities/Fonts/font20.d \
./Drivers/BSP/Utilities/Fonts/font24.d \
./Drivers/BSP/Utilities/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Utilities/Fonts/%.o Drivers/BSP/Utilities/Fonts/%.su Drivers/BSP/Utilities/Fonts/%.cyclo: ../Drivers/BSP/Utilities/Fonts/%.c Drivers/BSP/Utilities/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDISC -DDEBUG -DSTM32 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/abodenho/STM32CubeIDE/workspace_1.17.0/SQIsign_level1_STM32F429I-DISC1/Drivers/BSP/STM32F429I-Discovery" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Utilities-2f-Fonts

clean-Drivers-2f-BSP-2f-Utilities-2f-Fonts:
	-$(RM) ./Drivers/BSP/Utilities/Fonts/font12.cyclo ./Drivers/BSP/Utilities/Fonts/font12.d ./Drivers/BSP/Utilities/Fonts/font12.o ./Drivers/BSP/Utilities/Fonts/font12.su ./Drivers/BSP/Utilities/Fonts/font16.cyclo ./Drivers/BSP/Utilities/Fonts/font16.d ./Drivers/BSP/Utilities/Fonts/font16.o ./Drivers/BSP/Utilities/Fonts/font16.su ./Drivers/BSP/Utilities/Fonts/font20.cyclo ./Drivers/BSP/Utilities/Fonts/font20.d ./Drivers/BSP/Utilities/Fonts/font20.o ./Drivers/BSP/Utilities/Fonts/font20.su ./Drivers/BSP/Utilities/Fonts/font24.cyclo ./Drivers/BSP/Utilities/Fonts/font24.d ./Drivers/BSP/Utilities/Fonts/font24.o ./Drivers/BSP/Utilities/Fonts/font24.su ./Drivers/BSP/Utilities/Fonts/font8.cyclo ./Drivers/BSP/Utilities/Fonts/font8.d ./Drivers/BSP/Utilities/Fonts/font8.o ./Drivers/BSP/Utilities/Fonts/font8.su

.PHONY: clean-Drivers-2f-BSP-2f-Utilities-2f-Fonts

