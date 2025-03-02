cmake_minimum_required(VERSION 3.20)

project(image_processing)
set(CMAKE_CXX_STANDARD 20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO bin.relwithdbg)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/results)

add_definitions(-DPRJ_ROOT_DIR="${CMAKE_SOURCE_DIR}")
add_definitions(-DPRJ_RESULTS_DIR="${CMAKE_SOURCE_DIR}/results")

find_package(OpenCV CONFIG REQUIRED)

add_executable(main main.cpp)
include_directories(${CMAKE_SOURCE_DIR}/prj.lab)

target_link_libraries(main semcv)

include_directories(prj.lab)
add_subdirectory(prj.lab)