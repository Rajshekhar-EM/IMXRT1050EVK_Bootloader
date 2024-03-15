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
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DDATA_SECTION_IS_CACHEABLE=0 -D_DEBUG=1 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DUSB_STACK_BM -DPRINTF_ADVANCED_ENABLE=1 -DFSL_OSA_BM_TASK_ENABLE=0 -DFSL_OSA_BM_TIMER_CONFIG=0 -DMCUXPRESSO_SDK -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\source" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\fatfs\source\fsl_ram_disk" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\usb\host" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\usb\include" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\usb\phy" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\drivers" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\utilities" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\usb\host\class" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\fatfs\source" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\fatfs\source\fsl_usb_disk" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\device" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\xip" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\component\uart" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\component\lists" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\component\osa" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\CMSIS" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_host_msd_fatfs_bm\board" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-board

clean-board:
	-$(RM) ./board/board.d ./board/board.o ./board/clock_config.d ./board/clock_config.o ./board/dcd.d ./board/dcd.o ./board/pin_mux.d ./board/pin_mux.o

.PHONY: clean-board

