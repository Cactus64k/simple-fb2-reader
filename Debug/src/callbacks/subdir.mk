################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/callbacks/encoding_dialog_callbacks.c \
../src/callbacks/main_wnd_callbacks.c \
../src/callbacks/search_wnd_callbacks.c 

OBJS += \
./src/callbacks/encoding_dialog_callbacks.o \
./src/callbacks/main_wnd_callbacks.o \
./src/callbacks/search_wnd_callbacks.o 

C_DEPS += \
./src/callbacks/encoding_dialog_callbacks.d \
./src/callbacks/main_wnd_callbacks.d \
./src/callbacks/search_wnd_callbacks.d 


# Each subdirectory must supply rules for building sources it contributes
src/callbacks/%.o: ../src/callbacks/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -DDEBUG -I/usr/include/libxml2/ -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/usr/include/gtk-3.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/freetype2 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -O0 -g -Wstrict-overflow=4 -Wundef -Wshadow -Wcast-align -Wwrite-strings -pedantic -pedantic-errors -Wall -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


