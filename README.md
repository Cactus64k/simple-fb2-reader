# simple-fb2-reader
Simple tool to read FB2 books on GTK+3
=======

Features ("-" - not supported yet, "~" - partial support):
- supports fb2, fb2.zip and txt files
- color themes(black and white)
- saving reading position
- saving window state, size and position
- search text in book
- URI
- full 2.1 format support(-stylesheet, ~table)
- navigation


Depends:
- libxml2      >= 2.8.0, 
- libgtk-3-0  >= 3.4.2, 
- libglib     >= 2.33.12, 
- libzip2     >= 0.10.1


Instructions how to build ".deb" package on Debian:
$ cd ~/
$ git clone https://github.com/Cactus64k/simple-fb2-reader.git
$ cd simple-fb2-reader
$ fakeroot debian/rules binary
$ cd ..
# dpkg -i simple-fb2-reader_*.deb
