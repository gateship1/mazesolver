#include <algorithm>
#include <utility>

#include "cmd_input.hpp"
#include "generator2d.hpp"

auto get_cmd_input() -> std::pair<int, int> {
    
    int rows{}, cols{};
    
    std::cout << "rows: ";
    std::cin >> rows;
    std::cout << "cols: ";
    std::cin >> cols;
    
    return std::make_pair(rows, cols);
};

auto check_size(const std::pair<int, int>& msize) -> bool {
    return (msize.first <= 4 || msize.second <= 4) ? false : true;
}

auto main(int argc, char **argv) -> int {
    
    // handle command line flags
    if (argc > 1) { // if flags exist
        
        // tokenize command line args
        auto args{tokenize(build_arg_str(argc, argv), ' ')};
        
        // flag variables
        auto load_maze{false};
        auto load_path{std::string()};
        auto print_maze{false};
        auto save_maze{false};
        auto save_path{std::string()};
        unsigned int seed_val{static_cast<unsigned int>(std::time(nullptr))};
        
        // set the flags
        for (size_t i{}; i < args.size(); ++i) {
            if (args[i] == "print") {
                print_maze = true;
            }
            if (args[i] == "load") {
                load_maze = true;
                load_path = args[i+1];
            }
            if (args[i] == "save") {
                save_maze = true;
                save_path = args[i+1];
            }
            if (args[i] == "seed") {
                seed_val = static_cast<unsigned int>(std::stoi(args[i+1]));
            }
        }
        
        if (load_maze) {
            Maze2D maze(Maze2D::load_maze(load_path));
            if (maze.e.empty()) return -1;
            if (print_maze) {
                Maze2D::print_maze(maze.maze_to_str());
            }
        } else {
            
            auto msize{get_cmd_input()};
            if (!check_size(msize)) {
                std::cout << "Invalid maze size\n";
                return 1;
            }
            
            Generator2D gen(msize.first, msize.second);
            Maze2D maze(gen.rbacktrack(seed_val));
            
            if (save_maze) {
                maze.save_maze(save_path);
            }
            
            if (print_maze) {
                std::cout << "\nMaze seed = " << maze.seed; 
                Maze2D::print_maze(maze.maze_to_str());
            }
        }
    } else {
        
        auto msize{get_cmd_input()};
        if (!check_size(msize)) {
            std::cout << "Invalid maze size\n";
            return 1;
        }
        
        Generator2D gen(msize.first, msize.second);        
        
        Maze2D maze(gen.rbacktrack());
        std::cout << "seed = " << maze.seed << '\n';
        Maze2D::print_maze(maze.maze_to_str());
        std::cout << "\n";
        
    }
      
    return 0;
}