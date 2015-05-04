################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/reader/reader_book_config.c \
../src/reader/reader_close_app.c \
../src/reader/reader_close_book.c \
../src/reader/reader_color_theme.c \
../src/reader/reader_open_book.c \
../src/reader/reader_scroll.c 

OBJS += \
./src/reader/reader_book_config.o \
./src/reader/reader_close_app.o \
./src/reader/reader_close_book.o \
./src/reader/reader_color_theme.o \
./src/reader/reader_open_book.o \
./src/reader/reader_scroll.o 

C_DEPS += \
./src/reader/reader_book_config.d \
./src/reader/reader_close_app.d \
./src/reader/reader_close_book.d \
./src/reader/reader_color_theme.d \
./src/reader/reader_open_book.d \
./src/reader/reader_scroll.d 


# Each subdirectory must supply rules for building sources it contributes
src/reader/%.o: ../src/reader/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -DDEBUG -I/usr/include/libxml2/ -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/usr/include/gtk-3.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/freetype2 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -O0 -g -Wstrict-overflow=4 -Wundef -Wshadow -Wcast-align -Wwrite-strings -pedantic -pedantic-errors -Wall -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


