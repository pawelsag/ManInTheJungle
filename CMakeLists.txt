cmake_minimum_required(VERSION 3.10)
project("MAN_IN_THE_JUNGLE")

include_directories("include")

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
file(GLOB JUNGLE_SRC src/*.cpp)

add_executable(jungle_game ${JUNGLE_SRC})

target_link_libraries(jungle_game ${SDL2_LIBRARIES} SDL2_image pthread)