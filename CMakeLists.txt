cmake_minimum_required(VERSION 3.10)
project(My_game)
set(CMAKE_CXX_STANDARD 17)

macro(recursive_add_source_files starting_dir return_value)
    file(GLOB_RECURSE ${return_value} ${starting_dir}/*.cpp ${starting_dir}/*.c)
endmacro()

recursive_add_source_files(src SOURCES)
recursive_add_source_files(libs/glad/src GLAD_SOURCES)

add_executable(My_game ${SOURCES} ${GLAD_SOURCES})

target_include_directories(My_game PRIVATE libs/glad/include libs/stb src)

find_package(glfw3)
find_package(assimp)

target_link_libraries(My_game assimp glfw)
