find_package(OpenCV REQUIRED)

add_library(semcv STATIC semcv.cpp)

target_include_directories(semcv PUBLIC ${OpenCV_INCLUDE_DIRS})

target_link_libraries(semcv PUBLIC ${OpenCV_LIBS})