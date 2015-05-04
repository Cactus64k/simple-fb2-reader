################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/callbacks/text_view_callback/link_tag_enevt_callback.c \
../src/callbacks/text_view_callback/motion_event_callback.c \
../src/callbacks/text_view_callback/popup_menu_callback.c \
../src/callbacks/text_view_callback/scroll_event_callback.c \
../src/callbacks/text_view_callback/tooltip_callback.c 

OBJS += \
./src/callbacks/text_view_callback/link_tag_enevt_callback.o \
./src/callbacks/text_view_callback/motion_event_callback.o \
./src/callbacks/text_view_callback/popup_menu_callback.o \
./src/callbacks/text_view_callback/scroll_event_callback.o \
./src/callbacks/text_view_callback/tooltip_callback.o 

C_DEPS += \
./src/callbacks/text_view_callback/link_tag_enevt_callback.d \
./src/callbacks/text_view_callback/motion_event_callback.d \
./src/callbacks/text_view_callback/popup_menu_callback.d \
./src/callbacks/text_view_callback/scroll_event_callback.d \
./src/callbacks/text_view_callback/tooltip_callback.d 


# Each subdirectory must supply rules for building sources it contributes
src/callbacks/text_view_callback/%.o: ../src/callbacks/text_view_callback/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -DDEBUG -I/usr/include/libxml2/ -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/usr/include/gtk-3.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/freetype2 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -O0 -g -Wstrict-overflow=4 -Wundef -Wshadow -Wcast-align -Wwrite-strings -pedantic -pedantic-errors -Wall -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


