# bin/bash

PACKAGE_NAME=simple-fb2-reader
mkdir -p mo/ru/
mkdir -p mo/en_US/
msgfmt ru.po	--output-file=mo/ru/${PACKAGE_NAME}.mo
msgfmt en_US.po	--output-file=mo/en_US/${PACKAGE_NAME}.mo
