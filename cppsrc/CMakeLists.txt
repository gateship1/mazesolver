#[=[ Maze generator and solver C++ engine source code #]=]

add_subdirectory(generator)
add_subdirectory(solvers)

# source list
set(DEMO_SOURCE_CODE_LIST 
    ${CMAKE_CURRENT_SOURCE_DIR}/cmd_input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cmd_input.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/demo_utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/demo_utils.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/threadstopper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/threadstopper.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheeltask.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheeltask.hpp
)

# build executable
add_executable(maze.x ${DEMO_SOURCE_CODE_LIST})
target_link_libraries(maze.x PUBLIC maze_gen_cpp maze_solver_cpp)