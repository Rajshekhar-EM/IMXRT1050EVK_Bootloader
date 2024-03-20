################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/memory/src/flexspi_nor_memory.c \
../source/memory/src/memory.c \
../source/memory/src/mmc_memory.c \
../source/memory/src/normal_memory.c \
../source/memory/src/sd_memory.c \
../source/memory/src/semc_nand_memory.c \
../source/memory/src/semc_nor_memory.c \
../source/memory/src/spi_nor_eeprom_memory.c \
../source/memory/src/spinand_memory.c \
../source/memory/src/sram_init_MIMXRT1052.c 

S_UPPER_SRCS += \
../source/memory/src/pattern_fill_gcc.S 

C_DEPS += \
./source/memory/src/flexspi_nor_memory.d \
./source/memory/src/memory.d \
./source/memory/src/mmc_memory.d \
./source/memory/src/normal_memory.d \
./source/memory/src/sd_memory.d \
./source/memory/src/semc_nand_memory.d \
./source/memory/src/semc_nor_memory.d \
./source/memory/src/spi_nor_eeprom_memory.d \
./source/memory/src/spinand_memory.d \
./source/memory/src/sram_init_MIMXRT1052.d 

OBJS += \
./source/memory/src/flexspi_nor_memory.o \
./source/memory/src/memory.o \
./source/memory/src/mmc_memory.o \
./source/memory/src/normal_memory.o \
./source/memory/src/pattern_fill_gcc.o \
./source/memory/src/sd_memory.o \
./source/memory/src/semc_nand_memory.o \
./source/memory/src/semc_nor_memory.o \
./source/memory/src/spi_nor_eeprom_memory.o \
./source/memory/src/spinand_memory.o \
./source/memory/src/sram_init_MIMXRT1052.o 


# Each subdirectory must supply rules for building sources it contributes
source/memory/src/%.o: ../source/memory/src/%.c source/memory/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DCPU_IS_ARM_CORTEX_M7=1 -D__SEMIHOST_HARDFAULT_DISABLE=1 -DBL_TARGET_RAM -DMIMXRT1052 -DUSB_STACK_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\device" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\drivers" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\usb\bm_composite" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\autobaud" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\bootloader" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\crc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\include" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\memory" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\memory\src" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\startup" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\packet" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\property" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\sbloader" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\utilities" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\dcp" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\trng" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\MIMXRT1052" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\include" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\source" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\component\osa" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\source\ehci" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\include" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\microseconds" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\flexspi" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\flexspi_nand" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\ocotp" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\CMSIS" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\component\lists" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\phy" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\flexspi_nor" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\serial_nor_eeprom" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\semc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\semc_nor" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\semc_nand" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\nand_ecc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\usdhc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\sdmmc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\board" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\class\hid" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\class" -Os -fno-common -g -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/memory/src/%.o: ../source/memory/src/%.S source/memory/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__NEWLIB__ -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\startup" -g3 -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -specs=nano.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-memory-2f-src

clean-source-2f-memory-2f-src:
	-$(RM) ./source/memory/src/flexspi_nor_memory.d ./source/memory/src/flexspi_nor_memory.o ./source/memory/src/memory.d ./source/memory/src/memory.o ./source/memory/src/mmc_memory.d ./source/memory/src/mmc_memory.o ./source/memory/src/normal_memory.d ./source/memory/src/normal_memory.o ./source/memory/src/pattern_fill_gcc.o ./source/memory/src/sd_memory.d ./source/memory/src/sd_memory.o ./source/memory/src/semc_nand_memory.d ./source/memory/src/semc_nand_memory.o ./source/memory/src/semc_nor_memory.d ./source/memory/src/semc_nor_memory.o ./source/memory/src/spi_nor_eeprom_memory.d ./source/memory/src/spi_nor_eeprom_memory.o ./source/memory/src/spinand_memory.d ./source/memory/src/spinand_memory.o ./source/memory/src/sram_init_MIMXRT1052.d ./source/memory/src/sram_init_MIMXRT1052.o

.PHONY: clean-source-2f-memory-2f-src

