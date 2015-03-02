CC				= gcc
CFLAGS			= -std=c99 -O3 -Wall -fmessage-length=0 -pedantic -pedantic-errors
LDFLAGS			= -export-dynamic
LIBS			= $(shell pkg-config gtk+-3.0 --libs-only-l) -lzip -lxml2
SOURCES			= $(shell find . -name '*.c' -printf './%P ')
INCLUDE			= $(shell pkg-config gtk+-3.0 --cflags-only-I) -I/usr/include/libxml2/
PROGNAME		= simple-fb2-reader
OBJECTS			= $(SOURCES:.c=.o)

all: $(SOURCES) GUI_TARGET $(PROGNAME) TRANSLATE_TARGET

GUI_TARGET:
				objcopy	--input binary \
						--output elf64-x86-64 \
						--binary-architecture i386 \
						simple-fb2-reader.glade simple-fb2-reader.glade.o

OBJECTS += ./simple-fb2-reader.glade.o

TRANSLATE_TARGET:
				msgfmt intl/ru.po	--output-file=intl/locale/ru/LC_MESSAGES/$(PROGNAME).mo
				msgfmt intl/en_US.po --output-file=intl/locale/en_US/LC_MESSAGES/$(PROGNAME).mo

$(PROGNAME): $(OBJECTS) 
				$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

.c.o:
				$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
				rm  -f $(OBJECTS) $(PROGNAME)
