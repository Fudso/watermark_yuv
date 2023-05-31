cmake_minimum_required (VERSION 3.8)

project ("Watermark")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CPP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR})
set(H_SOURCES ${CMAKE_CURRENT_SOURCE_DIR})

set(ROOT ${CMAKE_CURRENT_SOURCE_DIR}/Watermark)  
include_directories(${ROOT})

add_subdirectory ("Watermark")

file(GLOB_RECURSE H_SOURCE_FILES Watermark/*.h)
file(GLOB_RECURSE CPP_SOURCE_FILES Watermark/*.cpp)

add_executable (Watermark ${CPP_SOURCE_FILES} ${H_SOURCE_FILES})

set(DATA_PATH ${ROOT}/Data)
set(INPUT_VIDEO ${DATA_PATH}/input420_video.yuv)
set(WATERMARK_BMP ${DATA_PATH}/watermark.bmp)
set(OUTPUT_VIDEO ${DATA_PATH}/output_video.yuv)
set(YUV_VIDEO_WIDTH 352)
set(YUV_VIDEO_HEIGHT 288)

configure_file (${ROOT}/config.h.in ${ROOT}/config.h)