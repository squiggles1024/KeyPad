################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/art_assets/art.c 

OBJS += \
./Core/Src/art_assets/art.o 

C_DEPS += \
./Core/Src/art_assets/art.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/art_assets/%.o Core/Src/art_assets/%.su: ../Core/Src/art_assets/%.c Core/Src/art_assets/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Core/Inc/art_assets -I../Core/Inc/KeyPadParts -I../Core/Inc/IC_Drivers -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-art_assets

clean-Core-2f-Src-2f-art_assets:
	-$(RM) ./Core/Src/art_assets/art.d ./Core/Src/art_assets/art.o ./Core/Src/art_assets/art.su

.PHONY: clean-Core-2f-Src-2f-art_assets

