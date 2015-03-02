# bin/bash

export PROGNAME=simple-fb2-reader

msgfmt ru.po	--output-file=./locale/ru/LC_MESSAGES/$PROGNAME.mo
msgfmt en_US.po --output-file=./locale/en_US/LC_MESSAGES/$PROGNAME.mo
