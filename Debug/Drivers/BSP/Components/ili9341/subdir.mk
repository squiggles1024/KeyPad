################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/ili9341/ili9341.c \
../Drivers/BSP/Components/ili9341/ili9341_reg.c 

OBJS += \
./Drivers/BSP/Components/ili9341/ili9341.o \
./Drivers/BSP/Components/ili9341/ili9341_reg.o 

C_DEPS += \
./Drivers/BSP/Components/ili9341/ili9341.d \
./Drivers/BSP/Components/ili9341/ili9341_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/ili9341/%.o Drivers/BSP/Components/ili9341/%.su: ../Drivers/BSP/Components/ili9341/%.c Drivers/BSP/Components/ili9341/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Core/Inc/art_assets -I../Core/Inc/KeyPadParts -I../Core/Inc/IC_Drivers -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../DISPLAY/Target -I../Drivers/BSP/Components/ili9341 -I../Drivers/BSP/Components/Common -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-ili9341

clean-Drivers-2f-BSP-2f-Components-2f-ili9341:
	-$(RM) ./Drivers/BSP/Components/ili9341/ili9341.d ./Drivers/BSP/Components/ili9341/ili9341.o ./Drivers/BSP/Components/ili9341/ili9341.su ./Drivers/BSP/Components/ili9341/ili9341_reg.d ./Drivers/BSP/Components/ili9341/ili9341_reg.o ./Drivers/BSP/Components/ili9341/ili9341_reg.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-ili9341

