#VERSION
cmake_minimum_required(VERSION 3.18.4)

#PROJECT NAME
project(lol)


#=================== INCLUSION OF Project Files ====================#
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/includes")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB SOURCES "${SOURCE_DIR}/*.cpp" "${INCLUDE_DIR}/*.h")

#=================== SETUP EXECTUABLE ====================#
add_executable(${PROJECT_NAME} ${SOURCES})

