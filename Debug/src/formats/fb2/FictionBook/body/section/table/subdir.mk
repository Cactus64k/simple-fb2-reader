################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/formats/fb2/FictionBook/body/section/table/table.c \
../src/formats/fb2/FictionBook/body/section/table/table_put_line.c \
../src/formats/fb2/FictionBook/body/section/table/table_size.c \
../src/formats/fb2/FictionBook/body/section/table/table_tr_next.c 

OBJS += \
./src/formats/fb2/FictionBook/body/section/table/table.o \
./src/formats/fb2/FictionBook/body/section/table/table_put_line.o \
./src/formats/fb2/FictionBook/body/section/table/table_size.o \
./src/formats/fb2/FictionBook/body/section/table/table_tr_next.o 

C_DEPS += \
./src/formats/fb2/FictionBook/body/section/table/table.d \
./src/formats/fb2/FictionBook/body/section/table/table_put_line.d \
./src/formats/fb2/FictionBook/body/section/table/table_size.d \
./src/formats/fb2/FictionBook/body/section/table/table_tr_next.d 


# Each subdirectory must supply rules for building sources it contributes
src/formats/fb2/FictionBook/body/section/table/%.o: ../src/formats/fb2/FictionBook/body/section/table/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -DDEBUG -I/usr/include/libxml2/ -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/usr/include/gtk-3.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/freetype2 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -O0 -g -Wstrict-overflow=4 -Wundef -Wshadow -Wcast-align -Wwrite-strings -pedantic -pedantic-errors -Wall -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


