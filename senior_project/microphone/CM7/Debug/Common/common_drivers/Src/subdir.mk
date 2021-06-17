################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/frank/OneDrive/Documents/seniorDesign/senior_project/microphone/Common/common_drivers/Src/pdm_to_pcm.c 

OBJS += \
./Common/common_drivers/Src/pdm_to_pcm.o 

C_DEPS += \
./Common/common_drivers/Src/pdm_to_pcm.d 


# Each subdirectory must supply rules for building sources it contributes
Common/common_drivers/Src/pdm_to_pcm.o: C:/Users/frank/OneDrive/Documents/seniorDesign/senior_project/microphone/Common/common_drivers/Src/pdm_to_pcm.c Common/common_drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../PDM2PCM/App -I../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I"C:/Users/frank/OneDrive/Documents/seniorDesign/senior_project/microphone/Common/common_drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/common_drivers/Src/pdm_to_pcm.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

