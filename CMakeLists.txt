cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

project(SeamCarving)

file(GLOB project_SRCS src/*.cpp src/*.h)
add_executable(SeamCarving ${project_SRCS})

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_BUILD_TYPE "Debug") #to be able to reading binary symbols in ubuntu, source: https://dominoc925.blogspot.com/2015/12/no-debugging-symbols-found-in-gdb-after.html 
SET(OpenCV_DIR lib/opencv)
find_package(OpenCV 4.1 REQUIRED)
find_package(OpenCV  REQUIRED  PATHS lib/opencv)
find_package(wxWidgets REQUIRED COMPONENTS core base)

find_package(SDL2 REQUIRED)



include_directories(${SDL2_INCLUDE_DIRS} src)



include(${wxWidgets_USE_FILE})
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_definitions(${OpenCV_DEFINITIONS})


string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries( 
    SeamCarving
    ${wxWidgets_LIBRARIES}
    ${OpenCV_LIBS}
)

target_include_directories(
    SeamCarving
    PRIVATE ${wxWidgets_INCLUDE_DIRS}
    PRIVATE ${OpenCV_INCLUDE_DIRS} 
    
)
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)


INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} )