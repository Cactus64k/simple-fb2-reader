cmake_minimum_required (VERSION 3.0.2) 
 
set (PROJECT simple-fb2-reader) 
 
project (${PROJECT} C) 
 
set (HEADERS src/chunks.h)

set (SOURCES 
	src/machine.c
	src/machine_file_copy.c
	src/machine_file_exec.c
	src/machine_hndl.c
	src/machine_job.c
	src/machine_list.c
	src/machine_print_status.c
	src/machine_start_job.c
	src/main.c) 

set (LIBRARIES
	ssh
	pthread)
	
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
 
add_executable (${PROJECT} ${HEADERS} ${SOURCES})
target_link_libraries (${PROJECT} ${LIBRARIES})

install (TARGETS ${PROJECT} RUNTIME DESTINATION /usr/bin)
