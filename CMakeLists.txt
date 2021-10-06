cmake_minimum_required(VERSION 3.21)
project(zetget)

find_package(OpenCV REQUIRED QUIET)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(ImageMagick COMPONENTS Magick++ convert REQUIRED QUIET)
include_directories(${ImageMagick_INCLUDE_DIRS})

set(PROJECT_NAME "libzetget")
add_library(${PROJECT_NAME} SHARED "src/main.cpp" "zetget.def")
set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "src/main.hpp"
    VERSION "${PROJECT_VERSION}"
    SOVERSION "1"
    OUTPUT_NAME "zetget"
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "NONE"
)

set(PROJECT_NAME "zetget")
set(PROJECT_SOURCES "src/main.cpp")
set(PROJECT_UTIL "src/manipulation.cpp" "src/util.cpp")
add_executable(${PROJECT_NAME} ${PROJECT_UTIL} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS} ${ImageMagick_LIBRARIES})