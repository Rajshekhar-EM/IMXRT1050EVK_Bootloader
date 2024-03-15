################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include xip/subdir.mk
-include utilities/subdir.mk
-include usb/phy/subdir.mk
-include usb/host/class/subdir.mk
-include usb/host/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include fatfs/source/fsl_usb_disk/subdir.mk
-include fatfs/source/fsl_ram_disk/subdir.mk
-include fatfs/source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/osa/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := evkbimxrt1050_host_msd_fatfs_bm
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: evkbimxrt1050_host_msd_fatfs_bm.axf

# Tool invocations
evkbimxrt1050_host_msd_fatfs_bm.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="evkbimxrt1050_host_msd_fatfs_bm.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -T evkbimxrt1050_host_msd_fatfs_bm_Debug.ld -o "evkbimxrt1050_host_msd_fatfs_bm.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) evkbimxrt1050_host_msd_fatfs_bm.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "evkbimxrt1050_host_msd_fatfs_bm.axf"; # arm-none-eabi-objcopy -v -O binary "evkbimxrt1050_host_msd_fatfs_bm.axf" "evkbimxrt1050_host_msd_fatfs_bm.bin" ; # checksum -p MIMXRT1052xxxxB -d "evkbimxrt1050_host_msd_fatfs_bm.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
