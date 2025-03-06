cmake_minimum_required(VERSION 3.20)

project(image_processing)
set(CMAKE_CXX_STANDARD 20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO bin.relwithdbg)

# create result directory and transfer all vars to cpp 
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/results)
add_definitions(-DPRJ_ROOT_DIR="${CMAKE_SOURCE_DIR}")
set(RESULTS_DIR "${CMAKE_SOURCE_DIR}/results")
add_definitions(-DPRJ_RESULTS_DIR="${RESULTS_DIR}")

# create children directories with results for each lab
file(GLOB children RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/prj.lab" "${CMAKE_CURRENT_SOURCE_DIR}/prj.lab/*")
foreach(child ${children})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/prj.lab/${child}" AND child MATCHES "^lab[0-9][0-9]$")
        file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/results/${child}")
    endif()
endforeach()

find_package(OpenCV CONFIG REQUIRED)

include_directories(prj.lab)
add_subdirectory(prj.lab)