cmake_minimum_required(VERSION 3.11)
project(zetget)

find_package(OpenCV REQUIRED QUIET)
include_directories(${OpenCV_INCLUDE_DIRS})

set(PROJECT_NAME "zetget")
set(PROJECT_SOURCES "src/main.cpp")
set(PROJECT_UTIL "src/manipulation.cpp" "src/util.cpp")
add_executable(${PROJECT_NAME} ${PROJECT_UTIL} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS})
