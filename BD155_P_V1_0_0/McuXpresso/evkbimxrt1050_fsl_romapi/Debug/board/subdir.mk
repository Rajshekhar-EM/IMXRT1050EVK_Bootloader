################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/dcd.c \
../board/pin_mux.c 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/dcd.d \
./board/pin_mux.d 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/dcd.o \
./board/pin_mux.o 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DMCUXPRESSO_SDK -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\RAJASHEKHAR\BOOTLOADER_RELATED\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\source" -I"D:\RAJASHEKHAR\BOOTLOADER_RELATED\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\drivers" -I"D:\RAJASHEKHAR\BOOTLOADER_RELATED\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\utilities" -I"D:\RAJASHEKHAR\BOOTLOADER_RELATED\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\device" -I"D:\RAJASHEKHAR\BOOTLOADER_RELATED\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\component\uart" -I"D:\RAJASHEKHAR\BOOTLOADER_RELATED\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\component\lists" -I"D:\RAJASHEKHAR\BOOTLOADER_RELATED\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\xip" -I"D:\RAJASHEKHAR\BOOTLOADER_RELATED\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\component\silicon_id" -I"D:\RAJASHEKHAR\BOOTLOADER_RELATED\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\CMSIS" -I"D:\RAJASHEKHAR\BOOTLOADER_RELATED\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\board" -I"D:\RAJASHEKHAR\BOOTLOADER_RELATED\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\evkbimxrt1050\driver_examples\fsl_romapi" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-board

clean-board:
	-$(RM) ./board/board.d ./board/board.o ./board/clock_config.d ./board/clock_config.o ./board/dcd.d ./board/dcd.o ./board/pin_mux.d ./board/pin_mux.o

.PHONY: clean-board

