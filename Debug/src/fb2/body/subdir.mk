################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/fb2/body/book_body.c \
../src/fb2/body/cite.c \
../src/fb2/body/date.c \
../src/fb2/body/formated_text.c \
../src/fb2/body/image.c \
../src/fb2/body/link.c \
../src/fb2/body/poem.c \
../src/fb2/body/section.c 

OBJS += \
./src/fb2/body/book_body.o \
./src/fb2/body/cite.o \
./src/fb2/body/date.o \
./src/fb2/body/formated_text.o \
./src/fb2/body/image.o \
./src/fb2/body/link.o \
./src/fb2/body/poem.o \
./src/fb2/body/section.o 

C_DEPS += \
./src/fb2/body/book_body.d \
./src/fb2/body/cite.d \
./src/fb2/body/date.d \
./src/fb2/body/formated_text.d \
./src/fb2/body/image.d \
./src/fb2/body/link.d \
./src/fb2/body/poem.d \
./src/fb2/body/section.d 


# Each subdirectory must supply rules for building sources it contributes
src/fb2/body/%.o: ../src/fb2/body/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -I/usr/include/libxml2/ -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/usr/include/gtk-3.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/freetype2 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -O0 -g -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


