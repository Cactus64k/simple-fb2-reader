################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/txt/subdir.mk
-include src/init/subdir.mk
-include src/fb2_zip/subdir.mk
-include src/fb2/description/subdir.mk
-include src/fb2/body/subdir.mk
-include src/fb2/binary/subdir.mk
-include src/fb2/attributes/subdir.mk
-include src/fb2/subdir.mk
-include src/callbacks/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: pre-build main-build

# Main-build Target
main-build: simple-fb2-reader

# Tool invocations
simple-fb2-reader: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc -export-dynamic -pg -o "simple-fb2-reader" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) simple-fb2-reader
	-@echo ' '

pre-build:
	-sh /home/cactus/Yandex.Disk/Eclipse/LINUX/simple-fb2-reader/build_gui
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: main-build pre-build

-include ../makefile.targets
