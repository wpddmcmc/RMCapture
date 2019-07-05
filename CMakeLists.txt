cmake_minimum_required (VERSION 2.8)

# project name
project (inspur_cam)
# using C++11 
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -pthread")

# if u have OpenCV version more than one, set the build path which one u want to use
set(OpenCV_DIR "/home/mingcongchen/app/opencv-3.4.0/my_build_dir/")
# find opencv
find_package(OpenCV REQUIRED)
# print message of opencv
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "    libraries: ${OpenCV_LIBS}")

aux_source_directory(./src/ DIR_SRCS)

add_executable(inspur_cam  ${DIR_SRCS})

include_directories ( 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/local/include
    /usr/include 
${OpenCV_INCLUDE_DIRS})

target_link_libraries(inspur_cam
${OpenCV_LIBS}
/usr/lib
/usr/local/lib
    )
