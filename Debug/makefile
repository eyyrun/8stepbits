################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
8stepbits.lss \

FLASH_IMAGE += \
8stepbits.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: 8stepbits.elf secondary-outputs

# Tool invocations
8stepbits.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,8stepbits.map -mmcu=atmega328p -o "8stepbits.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

8stepbits.lss: 8stepbits.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 8stepbits.elf  >"8stepbits.lss"
	@echo 'Finished building: $@'
	@echo ' '

8stepbits.hex: 8stepbits.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 8stepbits.elf  "8stepbits.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 8stepbits.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p 8stepbits.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 8stepbits.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
