################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/bootloader/src/bl_app_crc_check.c \
../source/bootloader/src/bl_command.c \
../source/bootloader/src/bl_context.c \
../source/bootloader/src/bl_exception_handler.c \
../source/bootloader/src/bl_keyblob.c \
../source/bootloader/src/bl_keyblob_dcp.c \
../source/bootloader/src/bl_main.c \
../source/bootloader/src/bl_misc.c \
../source/bootloader/src/bl_nor_encrypt_bee.c \
../source/bootloader/src/bl_shutdown_cleanup.c \
../source/bootloader/src/bl_tree_root.c \
../source/bootloader/src/bl_user_entry.c \
../source/bootloader/src/lpuart_peripheral_interface.c \
../source/bootloader/src/usb_hid_msc_peripheral_interface.c 

C_DEPS += \
./source/bootloader/src/bl_app_crc_check.d \
./source/bootloader/src/bl_command.d \
./source/bootloader/src/bl_context.d \
./source/bootloader/src/bl_exception_handler.d \
./source/bootloader/src/bl_keyblob.d \
./source/bootloader/src/bl_keyblob_dcp.d \
./source/bootloader/src/bl_main.d \
./source/bootloader/src/bl_misc.d \
./source/bootloader/src/bl_nor_encrypt_bee.d \
./source/bootloader/src/bl_shutdown_cleanup.d \
./source/bootloader/src/bl_tree_root.d \
./source/bootloader/src/bl_user_entry.d \
./source/bootloader/src/lpuart_peripheral_interface.d \
./source/bootloader/src/usb_hid_msc_peripheral_interface.d 

OBJS += \
./source/bootloader/src/bl_app_crc_check.o \
./source/bootloader/src/bl_command.o \
./source/bootloader/src/bl_context.o \
./source/bootloader/src/bl_exception_handler.o \
./source/bootloader/src/bl_keyblob.o \
./source/bootloader/src/bl_keyblob_dcp.o \
./source/bootloader/src/bl_main.o \
./source/bootloader/src/bl_misc.o \
./source/bootloader/src/bl_nor_encrypt_bee.o \
./source/bootloader/src/bl_shutdown_cleanup.o \
./source/bootloader/src/bl_tree_root.o \
./source/bootloader/src/bl_user_entry.o \
./source/bootloader/src/lpuart_peripheral_interface.o \
./source/bootloader/src/usb_hid_msc_peripheral_interface.o 


# Each subdirectory must supply rules for building sources it contributes
source/bootloader/src/%.o: ../source/bootloader/src/%.c source/bootloader/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DCPU_IS_ARM_CORTEX_M7=1 -D__SEMIHOST_HARDFAULT_DISABLE=1 -DBL_TARGET_RAM -DMIMXRT1052 -DUSB_STACK_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\device" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\drivers" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\usb\bm_composite" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\autobaud" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\bootloader" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\crc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\include" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\memory" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\memory\src" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\startup" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\packet" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\property" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\sbloader" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\utilities" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\dcp" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\trng" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\MIMXRT1052" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\include" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\source" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\component\osa" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\source\ehci" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\include" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\microseconds" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\flexspi" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\flexspi_nand" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\ocotp" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\CMSIS" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\component\lists" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\phy" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\flexspi_nor" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\serial_nor_eeprom" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\semc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\semc_nor" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\semc_nand" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\nand_ecc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\usdhc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\source\drivers\sdmmc" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\board" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\class\hid" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_flashloader\usb\device\class" -Os -fno-common -g -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-bootloader-2f-src

clean-source-2f-bootloader-2f-src:
	-$(RM) ./source/bootloader/src/bl_app_crc_check.d ./source/bootloader/src/bl_app_crc_check.o ./source/bootloader/src/bl_command.d ./source/bootloader/src/bl_command.o ./source/bootloader/src/bl_context.d ./source/bootloader/src/bl_context.o ./source/bootloader/src/bl_exception_handler.d ./source/bootloader/src/bl_exception_handler.o ./source/bootloader/src/bl_keyblob.d ./source/bootloader/src/bl_keyblob.o ./source/bootloader/src/bl_keyblob_dcp.d ./source/bootloader/src/bl_keyblob_dcp.o ./source/bootloader/src/bl_main.d ./source/bootloader/src/bl_main.o ./source/bootloader/src/bl_misc.d ./source/bootloader/src/bl_misc.o ./source/bootloader/src/bl_nor_encrypt_bee.d ./source/bootloader/src/bl_nor_encrypt_bee.o ./source/bootloader/src/bl_shutdown_cleanup.d ./source/bootloader/src/bl_shutdown_cleanup.o ./source/bootloader/src/bl_tree_root.d ./source/bootloader/src/bl_tree_root.o ./source/bootloader/src/bl_user_entry.d ./source/bootloader/src/bl_user_entry.o ./source/bootloader/src/lpuart_peripheral_interface.d ./source/bootloader/src/lpuart_peripheral_interface.o ./source/bootloader/src/usb_hid_msc_peripheral_interface.d ./source/bootloader/src/usb_hid_msc_peripheral_interface.o

.PHONY: clean-source-2f-bootloader-2f-src

