#ifndef MAZE2D_HEADER_FILE
#define MAZE2D_HEADER_FILE

#include <algorithm> // std::find_if, std::sort
#include <iostream>
#include <fstream> // std::ifstream, std::ofstream
#include <string>  // std::stoi
#include <utility> // std::make_pair, std::pair
#include <vector>  // std::vector

#include "compare_pairs.hpp"
#include "tokenize.hpp"

// global maze constants
const char end_symbol{'E'};
const char path_symbol{' '};
const char start_symbol{'S'};
const char solution_symbol{'.'};
const char wall_symbol{'#'};

/* Maze2D
  
  data structure holding a 2D maze of size rows x cols
  
  - the maze generated using the Generator2D class, or it is loaded from a previously generate maze
  - the maze size (rows x cols) is stored
  - the maze is stored as a list of connected edges, e, which make up the paths through the maze
*/
struct Maze2D {
    
    Maze2D() : seed(), rows(0), cols(0), start(-1), end(-1), 
               filename(std::string{}), solution_path(std::vector<int>{}) {
    } // empty maze (error)
    
    Maze2D(const unsigned int& seed_, const int& r, const int& c, 
           const int& start_, const int& end_,
           const std::vector<std::pair<int, int>>& e_,
           const std::vector<int> solution_path_=std::vector<int>{})
        : seed (seed_), rows(r), cols(c), start(start_), end(end_),
          filename(Maze2D::build_maze_filename(r, c, seed_)), e(e_),
          solution_path(solution_path_) {
    }
    
    Maze2D(const Maze2D& maze) : seed(maze.seed), rows(maze.rows), 
        cols(maze.cols), start(maze.start), end(maze.end),
        filename(maze.filename), e(maze.e), solution_path(maze.solution_path) {
    }
    
    auto list_of_neighbors() const -> std::vector<std::vector<int>>;
    static auto load_maze(const std::string&) -> Maze2D;
    
    auto maze_to_str() const -> std::string;
    
    // print methods
    static auto print_maze(const std::string& maze_str) -> void;
    auto print_maze_size() const -> void;
    auto print_e() const -> void;
    
    auto save_maze(const std::string& save_path="./", const bool& is_solution=false) const -> void;
    
    // data members
    const unsigned int seed;
    const int rows, cols, start, end;
    const std::string filename;
    const std::vector<std::pair<int, int>> e; // edges (the maze paths)
    std::vector<int> solution_path;
    
    private:
        // build the maze file name for saving
        static auto constexpr build_maze_filename = [](const int& rows, const int& cols, 
                                                       const unsigned int& seed) {
            return ("maze_" + std::to_string(rows) + "x" + std::to_string(cols) 
                    + "_" + std::to_string(seed) + ".txt");
        };
};

#endif // MAZE_HEADER_FILE