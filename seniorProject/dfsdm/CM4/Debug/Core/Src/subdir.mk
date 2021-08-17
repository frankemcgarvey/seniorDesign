################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/main.c \
../Core/Src/stm32h7xx_hal_msp.c \
../Core/Src/stm32h7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c 

OBJS += \
./Core/Src/main.o \
./Core/Src/stm32h7xx_hal_msp.o \
./Core/Src/stm32h7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o 

C_DEPS += \
./Core/Src/main.d \
./Core/Src/stm32h7xx_hal_msp.d \
./Core/Src/stm32h7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/main.o: ../Core/Src/main.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H755xx '-DARM_MATH_DSP=1' '-DARM_MATH_LOOPUNROLL=1' '-DCORTEX_M4=1' '-D__DSP_PRESENT=1' '-D__ARM_ARCH_7EM__=1' '-DARM_MATH_CM7=1' '-DARM_MATH_ROUNDING=1' -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Inc" -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32h7xx_hal_msp.o: ../Core/Src/stm32h7xx_hal_msp.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H755xx '-DARM_MATH_DSP=1' '-DARM_MATH_LOOPUNROLL=1' '-DCORTEX_M4=1' '-D__DSP_PRESENT=1' '-D__ARM_ARCH_7EM__=1' '-DARM_MATH_CM7=1' '-DARM_MATH_ROUNDING=1' -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Inc" -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32h7xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32h7xx_it.o: ../Core/Src/stm32h7xx_it.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H755xx '-DARM_MATH_DSP=1' '-DARM_MATH_LOOPUNROLL=1' '-DCORTEX_M4=1' '-D__DSP_PRESENT=1' '-D__ARM_ARCH_7EM__=1' '-DARM_MATH_CM7=1' '-DARM_MATH_ROUNDING=1' -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Inc" -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32h7xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H755xx '-DARM_MATH_DSP=1' '-DARM_MATH_LOOPUNROLL=1' '-DCORTEX_M4=1' '-D__DSP_PRESENT=1' '-D__ARM_ARCH_7EM__=1' '-DARM_MATH_CM7=1' '-DARM_MATH_ROUNDING=1' -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Inc" -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H755xx '-DARM_MATH_DSP=1' '-DARM_MATH_LOOPUNROLL=1' '-DCORTEX_M4=1' '-D__DSP_PRESENT=1' '-D__ARM_ARCH_7EM__=1' '-DARM_MATH_CM7=1' '-DARM_MATH_ROUNDING=1' -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/frank/OneDrive/Documents/seniorDesign/seniorProject/dfsdm/Common/common_folder/Inc" -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

