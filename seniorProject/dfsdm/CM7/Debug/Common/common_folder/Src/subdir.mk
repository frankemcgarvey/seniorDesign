################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Src/dsp.c \
C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Src/helper.c \
C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Src/localization.c 

OBJS += \
./Common/common_folder/Src/dsp.o \
./Common/common_folder/Src/helper.o \
./Common/common_folder/Src/localization.o 

C_DEPS += \
./Common/common_folder/Src/dsp.d \
./Common/common_folder/Src/helper.d \
./Common/common_folder/Src/localization.d 


# Each subdirectory must supply rules for building sources it contributes
Common/common_folder/Src/dsp.o: C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Src/dsp.c Common/common_folder/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx '-DARM_MATH_DSP=1' '-DARM_MATH_LOOPUNROLL=1' '-DCORTEX_M7=1' '-D__DSP_PRESENT=1' '-D__ARM_ARCH_7EM__=1' '-DARM_MATH_CM7 =1' '-DARM_MATH_ROUNDING=1' -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I"C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/common_folder/Src/dsp.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/common_folder/Src/helper.o: C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Src/helper.c Common/common_folder/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx '-DARM_MATH_DSP=1' '-DARM_MATH_LOOPUNROLL=1' '-DCORTEX_M7=1' '-D__DSP_PRESENT=1' '-D__ARM_ARCH_7EM__=1' '-DARM_MATH_CM7 =1' '-DARM_MATH_ROUNDING=1' -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I"C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/common_folder/Src/helper.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Common/common_folder/Src/localization.o: C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Src/localization.c Common/common_folder/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx '-DARM_MATH_DSP=1' '-DARM_MATH_LOOPUNROLL=1' '-DCORTEX_M7=1' '-D__DSP_PRESENT=1' '-D__ARM_ARCH_7EM__=1' '-DARM_MATH_CM7 =1' '-DARM_MATH_ROUNDING=1' -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -I"C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Common/common_folder/Src/localization.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

