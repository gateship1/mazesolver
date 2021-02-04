#[=[ Maze solver C++ engine source code #]=]

# source list
set(SOLVER_ENGINE_SOURCE_CODE_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/astar.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bfs.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dfs.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/heuristics.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/node.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/solution_path.hpp    
)

# add source files to a library
add_library(maze_solver_cpp 
            STATIC
            ${SOLVER_ENGINE_SOURCE_CODE_LIST}
)

# set the library linker language
set_target_properties(maze_solver_cpp 
                      PROPERTIES 
                      LINKER_LANGUAGE CXX
)

# pass library
target_include_directories(maze_solver_cpp 
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR} 
)
target_link_libraries(maze_solver_cpp PUBLIC)
