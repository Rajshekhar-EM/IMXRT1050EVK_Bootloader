################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Files_Application/KeypadStack/sourceKeypadStack.c 

C_DEPS += \
./source/Files_Application/KeypadStack/sourceKeypadStack.d 

OBJS += \
./source/Files_Application/KeypadStack/sourceKeypadStack.o 


# Each subdirectory must supply rules for building sources it contributes
source/Files_Application/KeypadStack/%.o: ../source/Files_Application/KeypadStack/%.c source/Files_Application/KeypadStack/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -D_DEBUG=1 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DUSB_STACK_BM -DPRINTF_ADVANCED_ENABLE=1 -DFSL_OSA_BM_TASK_ENABLE=0 -DFSL_OSA_BM_TIMER_CONFIG=0 -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -DSD_ENABLED -DMCUXPRESSO_SDK -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DXIP_BOOT_HEADER_DCD_ENABLE=1 -DSKIP_SYSCLK_INIT -DDATA_SECTION_IS_CACHEABLE=1 -DAPPWIZARD -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\board" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\source" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\fatfs\source\fsl_ram_disk" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\usb\host" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\usb\include" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\usb\phy" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\drivers" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\touchpanel" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\utilities" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\usb\host\class" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\fatfs\source" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\fatfs\source\fsl_sd_disk" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\sdmmc\inc" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\sdmmc\host" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\sdmmc\osa" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\sdmmc\sd" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\fatfs\source\fsl_usb_disk" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\emwin\emWin_header" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\emwin\emWin_Config" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\device" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\component\uart" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\component\lists" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\xip" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\component\osa" -I"D:\RAJASHEKHAR\Github\IMXRT1050EVK_Bootloader\BD155_P_V1_0_0\McuXpresso\VMS_Display_V0\CMSIS" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-Files_Application-2f-KeypadStack

clean-source-2f-Files_Application-2f-KeypadStack:
	-$(RM) ./source/Files_Application/KeypadStack/sourceKeypadStack.d ./source/Files_Application/KeypadStack/sourceKeypadStack.o

.PHONY: clean-source-2f-Files_Application-2f-KeypadStack

