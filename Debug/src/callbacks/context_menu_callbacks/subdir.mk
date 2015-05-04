################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/callbacks/context_menu_callbacks/about_callback.c \
../src/callbacks/context_menu_callbacks/backward_callback.c \
../src/callbacks/context_menu_callbacks/book_search_callback.c \
../src/callbacks/context_menu_callbacks/color_theme_callback.c \
../src/callbacks/context_menu_callbacks/encode_callback.c \
../src/callbacks/context_menu_callbacks/forget_books_callback.c \
../src/callbacks/context_menu_callbacks/navigation_callback.c \
../src/callbacks/context_menu_callbacks/navigation_section_callback.c \
../src/callbacks/context_menu_callbacks/open_file_callback.c 

OBJS += \
./src/callbacks/context_menu_callbacks/about_callback.o \
./src/callbacks/context_menu_callbacks/backward_callback.o \
./src/callbacks/context_menu_callbacks/book_search_callback.o \
./src/callbacks/context_menu_callbacks/color_theme_callback.o \
./src/callbacks/context_menu_callbacks/encode_callback.o \
./src/callbacks/context_menu_callbacks/forget_books_callback.o \
./src/callbacks/context_menu_callbacks/navigation_callback.o \
./src/callbacks/context_menu_callbacks/navigation_section_callback.o \
./src/callbacks/context_menu_callbacks/open_file_callback.o 

C_DEPS += \
./src/callbacks/context_menu_callbacks/about_callback.d \
./src/callbacks/context_menu_callbacks/backward_callback.d \
./src/callbacks/context_menu_callbacks/book_search_callback.d \
./src/callbacks/context_menu_callbacks/color_theme_callback.d \
./src/callbacks/context_menu_callbacks/encode_callback.d \
./src/callbacks/context_menu_callbacks/forget_books_callback.d \
./src/callbacks/context_menu_callbacks/navigation_callback.d \
./src/callbacks/context_menu_callbacks/navigation_section_callback.d \
./src/callbacks/context_menu_callbacks/open_file_callback.d 


# Each subdirectory must supply rules for building sources it contributes
src/callbacks/context_menu_callbacks/%.o: ../src/callbacks/context_menu_callbacks/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -DDEBUG -I/usr/include/libxml2/ -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/usr/include/gtk-3.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/freetype2 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -O0 -g -Wstrict-overflow=4 -Wundef -Wshadow -Wcast-align -Wwrite-strings -pedantic -pedantic-errors -Wall -Wconversion -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


