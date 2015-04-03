prefix			= /usr/
bindir			= $(prefix)/bin
sysconfdir		= /etc

<<<<<<< HEAD
CC			= gcc
=======
CC				= gcc
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
CFLAGS			= -std=c99 -O3 -Wall -fmessage-length=0 -pedantic -pedantic-errors
LDFLAGS			= -export-dynamic
####################################################################################
LIBS			=	$(shell pkg-config gtk+-3.0 --libs-only-l)\
<<<<<<< HEAD
				$(shell pkg-config libxml-2.0 --libs-only-l)\
				$(shell pkg-config libzip --libs-only-l)
####################################################################################
INCLUDE			=	$(shell pkg-config gtk+-3.0 --cflags-only-I)\
				$(shell pkg-config libxml-2.0 --cflags-only-I)\
				$(shell pkg-config libzip --cflags-only-I)
####################################################################################
PACKAGE_NAME		= simple-fb2-reader
=======
					$(shell pkg-config libxml-2.0 --libs-only-l)\
					$(shell pkg-config libzip --libs-only-l)
####################################################################################
INCLUDE			=	$(shell pkg-config gtk+-3.0 --cflags-only-I)\
					$(shell pkg-config libxml-2.0 --cflags-only-I)\
					$(shell pkg-config libzip --cflags-only-I)
####################################################################################
PACKAGE_NAME	= simple-fb2-reader
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
SOURCES			= $(shell find . -name '*.c' -printf './%P ')
OBJECTS			= $(SOURCES:.c=.o)

all: $(SOURCES) $(PACKAGE_NAME) TRANSLATE_TARGET

TRANSLATE_TARGET:
<<<<<<< HEAD
				msgfmt intl/ru.po	--output-file=intl/ru.mo
=======
				msgfmt intl/ru.po		--output-file=intl/ru.mo
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c
				msgfmt intl/en_US.po	--output-file=intl/en_US.mo

$(PACKAGE_NAME): $(OBJECTS) 
				$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

.c.o:
				$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) -DPACKAGE_NAME=\"$(PACKAGE_NAME)\"

cppcheck_start:
				cppcheck -j`nproc` -q --inconclusive --library=gtk --enable=all --std=c99 --report-progress --max-configs=1 $(INCLUDE) ./src/

clean:
				find -name "*.o" -delete
				find -name "*.mo" -delete
				rm -f $(PACKAGE_NAME)

install:
<<<<<<< HEAD
				install $(PACKAGE_NAME)				$(DESTDIR)/$(bindir)/$(PACKAGE_NAME)
				cp intl/ru.mo					$(DESTDIR)/$(prefix)/share/locale/ru/LC_MESSAGES/$(PACKAGE_NAME).mo
				cp intl/en_US.mo				$(DESTDIR)/$(prefix)/share/locale/en_US/LC_MESSAGES/$(PACKAGE_NAME).mo
				mkdir -p					$(DESTDIR)/$(prefix)/share/simple-fb2-reader/
				cp res/$(PACKAGE_NAME).glade			$(DESTDIR)/$(prefix)/share/simple-fb2-reader/$(PACKAGE_NAME).glade
				cp res/simple-fb2-reader.desktop		$(DESTDIR)/$(prefix)/share/applications/simple-fb2-reader.desktop
				cp res/simple-fb2-reader.xml			$(DESTDIR)/$(prefix)/share/mime/packages/simple-fb2-reader.xml
				cp res/application-x-fictionbook+xml.svg	$(DESTDIR)/$(prefix)/share/icons/hicolor/scalable/mimetypes/application-x-fictionbook+xml.svg
				cp res/simple-fb2-reader.svg			$(DESTDIR)/$(prefix)/share/icons/hicolor/scalable/apps/simple-fb2-reader.svg
				cp res/simple-fb2-reader_encoding_list.cfg	$(DESTDIR)/$(sysconfdir)/simple-fb2-reader_encoding_list.cfg
=======
				install $(PACKAGE_NAME)									$(DESTDIR)/$(bindir)/$(PACKAGE_NAME)
				cp intl/ru.mo											$(DESTDIR)/$(prefix)/share/locale/ru/LC_MESSAGES/$(PACKAGE_NAME).mo
				cp intl/en_US.mo										$(DESTDIR)/$(prefix)/share/locale/en_US/LC_MESSAGES/$(PACKAGE_NAME).mo
				mkdir -p												$(DESTDIR)/$(prefix)/share/simple-fb2-reader/
				cp res/$(PACKAGE_NAME).glade							$(DESTDIR)/$(prefix)/share/simple-fb2-reader/$(PACKAGE_NAME).glade
				cp res/simple-fb2-reader.desktop						$(DESTDIR)/$(prefix)/share/applications/simple-fb2-reader.desktop
				cp res/simple-fb2-reader.xml							$(DESTDIR)/$(prefix)/share/mime/packages/simple-fb2-reader.xml
				cp res/application-x-fictionbook+xml.svg				$(DESTDIR)/$(prefix)/share/icons/hicolor/scalable/mimetypes/application-x-fictionbook+xml.svg
				cp res/simple-fb2-reader.svg							$(DESTDIR)/$(prefix)/share/icons/hicolor/scalable/apps/simple-fb2-reader.svg
				cp res/simple-fb2-reader_encoding_list.cfg				$(DESTDIR)/$(sysconfdir)/simple-fb2-reader_encoding_list.cfg
>>>>>>> d61b624dfca0b7377df2b5526c48864a0b01e95c

