cmake_minimum_required(VERSION 2.8)
project(opengles_capture)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(SOURCE_FILES main.cpp capture.cpp display.cpp gles_egl_util.cpp tfdragon.cpp)
set(EXECUTABLE capture)

# add modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")

# find packages
find_package(TensorFlow REQUIRED)
find_package(Eigen REQUIRED)
find_package(Protobuf REQUIRED)

set(PROJECT_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include ${TensorFlow_INCLUDE_DIRS} ${Eigen_INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIRS})
set(PROJECT_LIBRARIES ${TensorFlow_LIBRARIES} ${PROTOBUF_LIBRARIES} libGLESv2.so.2 libEGL.so.1 X11 Xext)

include_directories(${PROJECT_INCLUDE_DIRS})
add_executable(${EXECUTABLE} ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE} ${PROJECT_LIBRARIES})
list(APPEND CMAKE_MODULE_PATH <cmake/Modules>)
# Replace <CMAKE_MODULE_DIR> with your path
# The most common path is ${PROJECT_SOURCE_DIR}/cmake/Modules
# Protobuf
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
target_link_libraries(${EXECUTABLE} ${Protobuf_LIBRARIES})