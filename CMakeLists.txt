cmake_minimum_required(VERSION 3.12)
project(Lander)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

include_directories(include)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

add_executable(lander ${SOURCES})

target_link_libraries(lander PRIVATE sfml-graphics sfml-window sfml-system)

add_custom_command(TARGET lander POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "${CMAKE_CURRENT_BINARY_DIR}/assets"
)


