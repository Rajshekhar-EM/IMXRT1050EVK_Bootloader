################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MIMXRT1052/bl_clock_config_MIMXRT1052.c \
../MIMXRT1052/bl_lpuart_irq_config_MIMXRT1052.c \
../MIMXRT1052/bl_peripherals_MIMXRT1052.c \
../MIMXRT1052/external_memory_property_map_MIMXRT1052.c \
../MIMXRT1052/flexspi_nand_config_MIMXRT1052.c \
../MIMXRT1052/flexspi_nor_config_MIMXRT1052.c \
../MIMXRT1052/hardware_init_MIMXRT1052.c \
../MIMXRT1052/memory_map_MIMXRT1052.c \
../MIMXRT1052/pinmux_utility_imxrt_series.c \
../MIMXRT1052/sdmmc_config_MIMXRT1052.c \
../MIMXRT1052/semc_nand_config_MIMXRT1052.c \
../MIMXRT1052/semc_nor_config_MIMXRT1052.c 

C_DEPS += \
./MIMXRT1052/bl_clock_config_MIMXRT1052.d \
./MIMXRT1052/bl_lpuart_irq_config_MIMXRT1052.d \
./MIMXRT1052/bl_peripherals_MIMXRT1052.d \
./MIMXRT1052/external_memory_property_map_MIMXRT1052.d \
./MIMXRT1052/flexspi_nand_config_MIMXRT1052.d \
./MIMXRT1052/flexspi_nor_config_MIMXRT1052.d \
./MIMXRT1052/hardware_init_MIMXRT1052.d \
./MIMXRT1052/memory_map_MIMXRT1052.d \
./MIMXRT1052/pinmux_utility_imxrt_series.d \
./MIMXRT1052/sdmmc_config_MIMXRT1052.d \
./MIMXRT1052/semc_nand_config_MIMXRT1052.d \
./MIMXRT1052/semc_nor_config_MIMXRT1052.d 

OBJS += \
./MIMXRT1052/bl_clock_config_MIMXRT1052.o \
./MIMXRT1052/bl_lpuart_irq_config_MIMXRT1052.o \
./MIMXRT1052/bl_peripherals_MIMXRT1052.o \
./MIMXRT1052/external_memory_property_map_MIMXRT1052.o \
./MIMXRT1052/flexspi_nand_config_MIMXRT1052.o \
./MIMXRT1052/flexspi_nor_config_MIMXRT1052.o \
./MIMXRT1052/hardware_init_MIMXRT1052.o \
./MIMXRT1052/memory_map_MIMXRT1052.o \
./MIMXRT1052/pinmux_utility_imxrt_series.o \
./MIMXRT1052/sdmmc_config_MIMXRT1052.o \
./MIMXRT1052/semc_nand_config_MIMXRT1052.o \
./MIMXRT1052/semc_nor_config_MIMXRT1052.o 


# Each subdirectory must supply rules for building sources it contributes
MIMXRT1052/%.o: ../MIMXRT1052/%.c MIMXRT1052/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DCPU_IS_ARM_CORTEX_M7=1 -D__SEMIHOST_HARDFAULT_DISABLE=1 -DBL_TARGET_RAM -DMIMXRT1052 -DUSB_STACK_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\device" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\drivers" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\usb\bm_composite" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\autobaud" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\bootloader" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\crc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\include" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\memory" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\memory\src" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\startup" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\packet" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\property" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\sbloader" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\utilities" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\dcp" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\trng" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\MIMXRT1052" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\include" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\source" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\component\osa" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\source\ehci" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\include" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\microseconds" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\flexspi" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\flexspi_nand" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\ocotp" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\CMSIS" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\component\lists" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\phy" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\flexspi_nor" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\serial_nor_eeprom" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\semc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\semc_nor" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\semc_nand" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\nand_ecc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\usdhc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\sdmmc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\board" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\class\hid" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\class" -Os -fno-common -g -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MIMXRT1052

clean-MIMXRT1052:
	-$(RM) ./MIMXRT1052/bl_clock_config_MIMXRT1052.d ./MIMXRT1052/bl_clock_config_MIMXRT1052.o ./MIMXRT1052/bl_lpuart_irq_config_MIMXRT1052.d ./MIMXRT1052/bl_lpuart_irq_config_MIMXRT1052.o ./MIMXRT1052/bl_peripherals_MIMXRT1052.d ./MIMXRT1052/bl_peripherals_MIMXRT1052.o ./MIMXRT1052/external_memory_property_map_MIMXRT1052.d ./MIMXRT1052/external_memory_property_map_MIMXRT1052.o ./MIMXRT1052/flexspi_nand_config_MIMXRT1052.d ./MIMXRT1052/flexspi_nand_config_MIMXRT1052.o ./MIMXRT1052/flexspi_nor_config_MIMXRT1052.d ./MIMXRT1052/flexspi_nor_config_MIMXRT1052.o ./MIMXRT1052/hardware_init_MIMXRT1052.d ./MIMXRT1052/hardware_init_MIMXRT1052.o ./MIMXRT1052/memory_map_MIMXRT1052.d ./MIMXRT1052/memory_map_MIMXRT1052.o ./MIMXRT1052/pinmux_utility_imxrt_series.d ./MIMXRT1052/pinmux_utility_imxrt_series.o ./MIMXRT1052/sdmmc_config_MIMXRT1052.d ./MIMXRT1052/sdmmc_config_MIMXRT1052.o ./MIMXRT1052/semc_nand_config_MIMXRT1052.d ./MIMXRT1052/semc_nand_config_MIMXRT1052.o ./MIMXRT1052/semc_nor_config_MIMXRT1052.d ./MIMXRT1052/semc_nor_config_MIMXRT1052.o

.PHONY: clean-MIMXRT1052

