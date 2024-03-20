################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include usb/phy/subdir.mk
-include usb/device/source/ehci/subdir.mk
-include usb/device/source/subdir.mk
-include usb/device/class/hid/subdir.mk
-include usb/device/class/subdir.mk
-include startup/subdir.mk
-include source/utilities/src/subdir.mk
-include source/usb/bm_composite/subdir.mk
-include source/sbloader/src/subdir.mk
-include source/property/src/subdir.mk
-include source/packet/src/subdir.mk
-include source/memory/src/subdir.mk
-include source/drivers/usdhc/subdir.mk
-include source/drivers/trng/subdir.mk
-include source/drivers/serial_nor_eeprom/subdir.mk
-include source/drivers/semc_nor/subdir.mk
-include source/drivers/semc_nand/subdir.mk
-include source/drivers/semc/subdir.mk
-include source/drivers/sdmmc/subdir.mk
-include source/drivers/ocotp/subdir.mk
-include source/drivers/nand_ecc/subdir.mk
-include source/drivers/microseconds/subdir.mk
-include source/drivers/flexspi_nor/subdir.mk
-include source/drivers/flexspi_nand/subdir.mk
-include source/drivers/flexspi/subdir.mk
-include source/drivers/dcp/subdir.mk
-include source/crc/subdir.mk
-include source/bootloader/src/subdir.mk
-include source/autobaud/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/osa/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
-include MIMXRT1052/subdir.mk
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


BUILD_ARTIFACT_NAME := evkbimxrt1050_flashloader
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: evkbimxrt1050_flashloader.axf

# Tool invocations
evkbimxrt1050_flashloader.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker --gc-sections -Xlinker -Map=evkbimxrt1050_flashloader.map -Xlinker -Map="evkbimxrt1050_flashloader.map" -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -T MIMXRT1052_ram_flashloader.ld -L ../middleware/mcu-boot -o "evkbimxrt1050_flashloader.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) evkbimxrt1050_flashloader.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "evkbimxrt1050_flashloader.axf"; # arm-none-eabi-objcopy -v -O binary "evkbimxrt1050_flashloader.axf" "evkbimxrt1050_flashloader.bin" ; # checksum -p MIMXRT1052xxxxB -d "evkbimxrt1050_flashloader.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
