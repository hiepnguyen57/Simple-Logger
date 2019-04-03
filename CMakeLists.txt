cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(logger)

#add_definitions(-DFILE_LOGGER)
#add_definitions(-DNDEBUG)

#Bring the headers, such as Student.h into the project
include_directories(include)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/main.cpp src/Level.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

find_package(Threads)
add_executable(logger ${SOURCES})
target_link_libraries( logger ${CMAKE_THREAD_LIBS_INIT} )
