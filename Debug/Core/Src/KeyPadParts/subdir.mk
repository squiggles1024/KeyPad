################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/KeyPadParts/Button.c \
../Core/Src/KeyPadParts/Button_Hardware.c \
../Core/Src/KeyPadParts/Joystick.c \
../Core/Src/KeyPadParts/Joystick_Hardware.c \
../Core/Src/KeyPadParts/KeyFunctions.c \
../Core/Src/KeyPadParts/SerialLED.c \
../Core/Src/KeyPadParts/SerialLED_Hardware.c 

OBJS += \
./Core/Src/KeyPadParts/Button.o \
./Core/Src/KeyPadParts/Button_Hardware.o \
./Core/Src/KeyPadParts/Joystick.o \
./Core/Src/KeyPadParts/Joystick_Hardware.o \
./Core/Src/KeyPadParts/KeyFunctions.o \
./Core/Src/KeyPadParts/SerialLED.o \
./Core/Src/KeyPadParts/SerialLED_Hardware.o 

C_DEPS += \
./Core/Src/KeyPadParts/Button.d \
./Core/Src/KeyPadParts/Button_Hardware.d \
./Core/Src/KeyPadParts/Joystick.d \
./Core/Src/KeyPadParts/Joystick_Hardware.d \
./Core/Src/KeyPadParts/KeyFunctions.d \
./Core/Src/KeyPadParts/SerialLED.d \
./Core/Src/KeyPadParts/SerialLED_Hardware.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/KeyPadParts/%.o Core/Src/KeyPadParts/%.su: ../Core/Src/KeyPadParts/%.c Core/Src/KeyPadParts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Core/Inc/KeyPadParts -I../Core/Inc/IC_Drivers -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-KeyPadParts

clean-Core-2f-Src-2f-KeyPadParts:
	-$(RM) ./Core/Src/KeyPadParts/Button.d ./Core/Src/KeyPadParts/Button.o ./Core/Src/KeyPadParts/Button.su ./Core/Src/KeyPadParts/Button_Hardware.d ./Core/Src/KeyPadParts/Button_Hardware.o ./Core/Src/KeyPadParts/Button_Hardware.su ./Core/Src/KeyPadParts/Joystick.d ./Core/Src/KeyPadParts/Joystick.o ./Core/Src/KeyPadParts/Joystick.su ./Core/Src/KeyPadParts/Joystick_Hardware.d ./Core/Src/KeyPadParts/Joystick_Hardware.o ./Core/Src/KeyPadParts/Joystick_Hardware.su ./Core/Src/KeyPadParts/KeyFunctions.d ./Core/Src/KeyPadParts/KeyFunctions.o ./Core/Src/KeyPadParts/KeyFunctions.su ./Core/Src/KeyPadParts/SerialLED.d ./Core/Src/KeyPadParts/SerialLED.o ./Core/Src/KeyPadParts/SerialLED.su ./Core/Src/KeyPadParts/SerialLED_Hardware.d ./Core/Src/KeyPadParts/SerialLED_Hardware.o ./Core/Src/KeyPadParts/SerialLED_Hardware.su

.PHONY: clean-Core-2f-Src-2f-KeyPadParts

