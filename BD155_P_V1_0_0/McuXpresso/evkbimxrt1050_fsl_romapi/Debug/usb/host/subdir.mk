################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usb/host/usb_host_devices.c \
../usb/host/usb_host_ehci.c \
../usb/host/usb_host_framework.c \
../usb/host/usb_host_hci.c 

C_DEPS += \
./usb/host/usb_host_devices.d \
./usb/host/usb_host_ehci.d \
./usb/host/usb_host_framework.d \
./usb/host/usb_host_hci.d 

OBJS += \
./usb/host/usb_host_devices.o \
./usb/host/usb_host_ehci.o \
./usb/host/usb_host_framework.o \
./usb/host/usb_host_hci.o 


# Each subdirectory must supply rules for building sources it contributes
usb/host/%.o: ../usb/host/%.c usb/host/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DUSB_STACK_BM -DMCUXPRESSO_SDK -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\source" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\fatfs\source\fsl_ram_disk" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\usb\host" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\usb\include" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\usb\phy" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\drivers" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\utilities" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\usb\host\class" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\fatfs\source" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\fatfs\source\fsl_usb_disk" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\device" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\xip" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\component\uart" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\component\lists" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\component\osa" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\component\silicon_id" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\CMSIS" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\board" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_fsl_romapi\evkbimxrt1050\driver_examples\fsl_romapi" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-usb-2f-host

clean-usb-2f-host:
	-$(RM) ./usb/host/usb_host_devices.d ./usb/host/usb_host_devices.o ./usb/host/usb_host_ehci.d ./usb/host/usb_host_ehci.o ./usb/host/usb_host_framework.d ./usb/host/usb_host_framework.o ./usb/host/usb_host_hci.d ./usb/host/usb_host_hci.o

.PHONY: clean-usb-2f-host

