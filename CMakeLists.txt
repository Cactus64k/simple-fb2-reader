cmake_minimum_required (VERSION 3.0.2) 

include (GNUInstallDirs)
include (FindPkgConfig)
 
set (PROJECT simple-fb2-reader)
set (VERSION 1.1.1)
set (CMAKE_INSTALL_PREFIX /usr)
 
project (${PROJECT} C)

file (GLOB_RECURSE SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "src/*.c")
file (GLOB_RECURSE HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "src/*.h")

pkg_search_module (GTK3 REQUIRED gtk+-3.0)
pkg_search_module (LIBZIP REQUIRED libzip)
pkg_search_module (SQLITE3 REQUIRED sqlite3)
pkg_search_module (LIBXML2 REQUIRED libxml-2.0)
pkg_search_module (GLIB REQUIRED glib-2.0)

set (LIBRARIES
	${GTK3_LIBRARIES}
	${LIBZIP_LIBRARIES}
	${SQLITE3_LIBRARIES}
	${LIBXML2_LIBRARIES}
	${GLIB_LIBRARIES})


set (INCLUDES
	${GTK3_INCLUDE_DIRS}
	${LIBZIP_INCLUDE_DIRS}
	${SQLITE3_INCLUDE_DIRS}
	${LIBXML2_INCLUDE_DIRS}
	${GLIB_INCLUDE_DIRS})


#BUILD
	
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -export-dynamic")

add_definitions (-DGUI_CONSTRUCT_PATH="${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT}/${PROJECT}.glade")
add_definitions (-DPACKAGE_VERSION="${VERSION}")
add_definitions (-DPACKAGE_NAME="${PROJECT}")

include_directories (${INCLUDES})
add_executable (${PROJECT} ${HEADERS} ${SOURCES})
target_link_libraries (${PROJECT} ${LIBRARIES})


#INSTALL

install (TARGETS ${PROJECT} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install (FILES res/${PROJECT}.glade DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT}/)

install (FILES intl/mo/en_US/${PROJECT}.mo DESTINATION ${CMAKE_INSTALL_LOCALEDIR}/en_US/LC_MESSAGES/)
install (FILES intl/mo/ru/${PROJECT}.mo DESTINATION ${CMAKE_INSTALL_LOCALEDIR}/ru/LC_MESSAGES/)

install (FILES res/${PROJECT}.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications/)
install (FILES res/${PROJECT}.svg DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps/)

install (FILES res/${PROJECT}.xml DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/mime/packages/)
install (FILES res/application-x-fictionbook+xml.svg DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/mimetypes/)


