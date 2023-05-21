cmake_minimum_required(VERSION 3.8.0)
project(Auto_Battle)

include(CTest)
enable_testing()
# set(OpenCV_DIR "D:/05_Porgram/opencvgcc/x64/mingw/lib")
find_package(OpenCV REQUIRED)

file(GLOB_RECURSE app_src 
			"source/*.cpp"
           )

file(GLOB_RECURSE HEADERS 
            "source/*.h"
           )

if(OpenCV_FOUND)
    message(STATUS "Found OpenCV")
    message(STATUS "Opencv Version:${OpenCV_VERSION}")
    message(STATUS "OpenCV Library: ${OpenCV_LIBS}")
    message(STATUS "Include path: ${OpenCV_INCLUDE_DIRS}")
else()
    message(FATAL_ERROT "Could not find OpenCV library")
endif()
# add_definitions(-D OPENCV_GENERATE_PKGCONFIG=YES)

add_executable(${PROJECT_NAME} ${app_src} ${HEADERS})

include_directories(${OpenCV_INCLUDE_DIRS} ) 
target_link_libraries(${PROJECT_NAME}  -static gcc stdc++ winpthread )
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

set(CPACK_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PTROJECT_VERSION})
include(CPack)