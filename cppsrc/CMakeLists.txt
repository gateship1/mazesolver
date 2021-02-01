#[=[ Maze generator and solver C++ engine source code #]=]

add_subdirectory(generator)

# source list
set(DEMO_SOURCE_CODE_LIST 
    ${CMAKE_CURRENT_SOURCE_DIR}/cmd_input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cmd_input.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# build executable
add_executable(maze_gen.x ${DEMO_SOURCE_CODE_LIST})
target_link_libraries(maze_gen.x PUBLIC maze_gen_cpp)