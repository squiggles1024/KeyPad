################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/IC_Drivers/ILI9341.c \
../Core/Src/IC_Drivers/ILI9341_Hardware.c \
../Core/Src/IC_Drivers/MCP23017.c \
../Core/Src/IC_Drivers/MCP23017_Hardware.c 

OBJS += \
./Core/Src/IC_Drivers/ILI9341.o \
./Core/Src/IC_Drivers/ILI9341_Hardware.o \
./Core/Src/IC_Drivers/MCP23017.o \
./Core/Src/IC_Drivers/MCP23017_Hardware.o 

C_DEPS += \
./Core/Src/IC_Drivers/ILI9341.d \
./Core/Src/IC_Drivers/ILI9341_Hardware.d \
./Core/Src/IC_Drivers/MCP23017.d \
./Core/Src/IC_Drivers/MCP23017_Hardware.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/IC_Drivers/%.o Core/Src/IC_Drivers/%.su: ../Core/Src/IC_Drivers/%.c Core/Src/IC_Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Core/Inc/art_assets -I../Core/Inc/KeyPadParts -I../Core/Inc/IC_Drivers -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-IC_Drivers

clean-Core-2f-Src-2f-IC_Drivers:
	-$(RM) ./Core/Src/IC_Drivers/ILI9341.d ./Core/Src/IC_Drivers/ILI9341.o ./Core/Src/IC_Drivers/ILI9341.su ./Core/Src/IC_Drivers/ILI9341_Hardware.d ./Core/Src/IC_Drivers/ILI9341_Hardware.o ./Core/Src/IC_Drivers/ILI9341_Hardware.su ./Core/Src/IC_Drivers/MCP23017.d ./Core/Src/IC_Drivers/MCP23017.o ./Core/Src/IC_Drivers/MCP23017.su ./Core/Src/IC_Drivers/MCP23017_Hardware.d ./Core/Src/IC_Drivers/MCP23017_Hardware.o ./Core/Src/IC_Drivers/MCP23017_Hardware.su

.PHONY: clean-Core-2f-Src-2f-IC_Drivers

