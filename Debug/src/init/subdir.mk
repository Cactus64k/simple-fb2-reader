################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/init/init_config_folder.c \
../src/init/init_dialogs.c \
../src/init/init_main_text_view.c \
../src/init/init_main_wnd.c \
../src/init/init_text_tags.c 

OBJS += \
./src/init/init_config_folder.o \
./src/init/init_dialogs.o \
./src/init/init_main_text_view.o \
./src/init/init_main_wnd.o \
./src/init/init_text_tags.o 

C_DEPS += \
./src/init/init_config_folder.d \
./src/init/init_dialogs.d \
./src/init/init_main_text_view.d \
./src/init/init_main_wnd.d \
./src/init/init_text_tags.d 


# Each subdirectory must supply rules for building sources it contributes
src/init/%.o: ../src/init/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -DDEBUG -I/usr/include/libxml2/ -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/usr/include/gtk-3.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/freetype2 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -O0 -g -Wstrict-overflow=4 -Wundef -Wshadow -Wcast-align -Wwrite-strings -pg -pedantic -pedantic-errors -Wall -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


