################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/silicon_id/fsl_silicon_id.c 

C_DEPS += \
./component/silicon_id/fsl_silicon_id.d 

OBJS += \
./component/silicon_id/fsl_silicon_id.o 


# Each subdirectory must supply rules for building sources it contributes
component/silicon_id/%.o: ../component/silicon_id/%.c component/silicon_id/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MIMXRT1052DVL6B -DCPU_MIMXRT1052DVL6B_cm7 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -DMCUXPRESSO_SDK -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_iled_blinky\source" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_iled_blinky\drivers" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_iled_blinky\device" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_iled_blinky\utilities" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_iled_blinky\component\uart" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_iled_blinky\component\serial_manager" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_iled_blinky\component\lists" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_iled_blinky\xip" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_iled_blinky\component\silicon_id" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_iled_blinky\CMSIS" -I"D:\IMXRT1050EVKB_Bootloader\BD155_P_V1_0_0\McuXpresso\evkbimxrt1050_iled_blinky\board" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-silicon_id

clean-component-2f-silicon_id:
	-$(RM) ./component/silicon_id/fsl_silicon_id.d ./component/silicon_id/fsl_silicon_id.o

.PHONY: clean-component-2f-silicon_id

