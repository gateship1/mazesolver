#[=[ Maze generator C++ engine source code #]=]

# source list
set(GENERATOR_ENGINE_SOURCE_CODE_LIST 
    ${CMAKE_CURRENT_SOURCE_DIR}/generator2d.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generator2d.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/maze2d.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/maze2d.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tokenize.hpp    
)

# add source files to a library
add_library(maze_gen_cpp 
            STATIC
            ${GENERATOR_ENGINE_SOURCE_CODE_LIST}
)

# set the library linker language
set_target_properties(maze_gen_cpp 
                      PROPERTIES 
                      LINKER_LANGUAGE CXX
)

# pass library
target_include_directories(maze_gen_cpp 
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR} 
)
target_link_libraries(maze_gen_cpp PUBLIC)
