################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/reader/subdir.mk
-include src/init/subdir.mk
-include src/formats/txt/subdir.mk
-include src/formats/fb2_zip/subdir.mk
-include src/formats/fb2/FictionBook/description/subdir.mk
-include src/formats/fb2/FictionBook/body/section/table/subdir.mk
-include src/formats/fb2/FictionBook/body/section/p/subdir.mk
-include src/formats/fb2/FictionBook/body/section/subdir.mk
-include src/formats/fb2/FictionBook/body/subdir.mk
-include src/formats/fb2/FictionBook/binary/subdir.mk
-include src/formats/fb2/FictionBook/attributes/subdir.mk
-include src/formats/fb2/subdir.mk
-include src/callbacks/text_view_callback/subdir.mk
-include src/callbacks/context_menu_callbacks/subdir.mk
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
all: simple-fb2-reader

# Tool invocations
simple-fb2-reader: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc -export-dynamic  -o "simple-fb2-reader" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) simple-fb2-reader
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
