cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

cmake_policy(VERSION 3.16)

project(ImproveTraining)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-std=c++14)
add_definitions(-Wall)

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    add_definitions(-O0)
    add_definitions(-g)
    add_definitions(-ggdb)
else( CMAKE_BUILD_TYPE STREQUAL "Release" )
    add_definitions(-O3)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -s")
    set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} -s")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -s")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Iniclue")
include_directories("/usr/include")
link_directories("/usr/lib")

#Build
set(EXE_BIN_NAME "ImproveTraining")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/CPP SOURCE_CPP_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/DataStructure SOURCE_DATA_STRUCTURE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/DesignPatterns SOURCE_DESIGN_PATTERNS_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/OperatingSystem SOURCE_OPERATING_SYSTEM_FILES)

add_executable(${EXE_BIN_NAME}
        main.cpp
        ${SOURCE_CPP_FILES}
        ${SOURCE_MGR_FILES}
        ${SOURCE_DATA_STRUCTURE_FILES}
        ${SOURCE_DESIGN_PATTERNS_FILES}
        ${SOURCE_OPERATING_SYSTEM_FILES})

#target_link_libraries(${EXE_BIN_NAME} glib)