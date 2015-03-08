CC				= gcc
CFLAGS			= -std=c99 -O3 -Wall -fmessage-length=0 -pedantic -pedantic-errors
LDFLAGS			= -export-dynamic
####################################################################################
LIBS			=	$(shell pkg-config gtk+-3.0 --libs-only-l)\
					$(shell pkg-config libxml-2.0 --libs-only-l)\
					$(shell pkg-config libzip --libs-only-l)
####################################################################################
INCLUDE			=	$(shell pkg-config gtk+-3.0 --cflags-only-I)\
					$(shell pkg-config libxml-2.0 --cflags-only-I)\
					$(shell pkg-config libzip --cflags-only-I)
####################################################################################
PROGNAME		= simple-fb2-reader
SOURCES			= $(shell find . -name '*.c' -printf './%P ')
OBJECTS			= $(SOURCES:.c=.o)

all: $(SOURCES) GUI_TARGET $(PROGNAME) TRANSLATE_TARGET

GUI_TARGET:
				objcopy	--input binary \
						--output elf64-x86-64 \
						--binary-architecture i386 \
						$(PROGNAME).glade $(PROGNAME).glade.o

OBJECTS += ./$(PROGNAME).glade.o

TRANSLATE_TARGET:
				msgfmt intl/ru.po	--output-file=intl/ru/$(PROGNAME).mo
				msgfmt intl/en_US.po --output-file=intl/en_US/$(PROGNAME).mo

$(PROGNAME): $(OBJECTS) 
				$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

.c.o:
				$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
				find -name "*.o" -delete
				find -name "*.mo" -delete
				rm -f $(PROGNAME)
