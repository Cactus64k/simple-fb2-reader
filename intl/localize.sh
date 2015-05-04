# bin/bash

export PROGNAME=simple-fb2-reader

msgfmt ru.po	--output-file=./ru/$PROGNAME.mo
msgfmt en_US.po --output-file=./en_US/$PROGNAME.mo
