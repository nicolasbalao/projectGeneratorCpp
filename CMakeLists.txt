#https://github.com/VelazcoJD/Qt6CMake/blob/main/CMakeLists.txt

#VERSION    
cmake_minimum_required(VERSION 3.18.4)

#PROJECT NAME
project(projectGenerator)

#======================= INCLUSION OF Qt =======================#
set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_AUTOMOC on)
set(CMAKE_AUTOUIC on)
set(CMAKE_PREFIX_PATH "/home/tengu/Qt/6.2.0/gcc_64/lib/cmake")

#package
find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

#=================== INCLUSION OF Project Files ====================#
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/includes")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB SOURCES "${SOURCE_DIR}/*.cpp" "${INCLUDE_DIR}/*.h")

#=================== SETUP EXECTUABLE ====================#

add_executable(${PROJECT_NAME} ${SOURCES})

#===================== LINKING LIBRARIES =======================#
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
