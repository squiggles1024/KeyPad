################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DISPLAY/Target/lcd_io.c \
../DISPLAY/Target/lcd_os.c 

OBJS += \
./DISPLAY/Target/lcd_io.o \
./DISPLAY/Target/lcd_os.o 

C_DEPS += \
./DISPLAY/Target/lcd_io.d \
./DISPLAY/Target/lcd_os.d 


# Each subdirectory must supply rules for building sources it contributes
DISPLAY/Target/%.o DISPLAY/Target/%.su: ../DISPLAY/Target/%.c DISPLAY/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Core/Inc/art_assets -I../Core/Inc/KeyPadParts -I../Core/Inc/IC_Drivers -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../DISPLAY/Target -I../Drivers/BSP/Components/ili9341 -I../Drivers/BSP/Components/Common -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DISPLAY-2f-Target

clean-DISPLAY-2f-Target:
	-$(RM) ./DISPLAY/Target/lcd_io.d ./DISPLAY/Target/lcd_io.o ./DISPLAY/Target/lcd_io.su ./DISPLAY/Target/lcd_os.d ./DISPLAY/Target/lcd_os.o ./DISPLAY/Target/lcd_os.su

.PHONY: clean-DISPLAY-2f-Target

