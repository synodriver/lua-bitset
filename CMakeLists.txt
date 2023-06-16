cmake_minimum_required(VERSION 3.25)
project(luabitset C)

set(CMAKE_C_STANDARD 11)

# change this to your lua.h directory
include_directories(D:\\conda\\envs\\py310\\Library\\include ./cbitset/include)
# change this to your lua.lib\liblua.a directory
link_directories("D:\\conda\\envs\\py310\\Library\\lib" D:\\conda\\envs\\py310\\Library\\bin)

file(GLOB SOURCES  ./cbitset/src/*.c)
message(${SOURCES})

add_library(bitset SHARED src/lbitset.c ${SOURCES})
target_link_libraries(bitset lua)

set_target_properties(bitset PROPERTIES OUTPUT_NAME bitset PREFIX "")
