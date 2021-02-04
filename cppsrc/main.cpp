#include <algorithm>
#include <utility>

#include "cmd_input.hpp"
#include "demo_utils.hpp"
#include "generator2d.hpp"
#include "maze2d.hpp"
#include "tokenize.hpp"
#include "threadstopper.hpp"
#include "wheeltask.hpp"

auto main(int argc, char **argv) -> int {
    
    // handle command line flags
    if (argc > 1) { // if flags exist
        
        // tokenize command line args
        auto args{tokenize(build_arg_str(argc, argv), ' ')};
        
        // flag variables
        auto load_maze{false};
        auto load_path{std::string()};
        auto method{std::string()};
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
            if (args[i] == "astar" || args[i] == "bfs" || args[i] == "dfs") {
                method = args[i];
            }
        }
        
        if (load_maze) {
            
            // load a maze
            std::cout << "Loading maze...";
            
            WheelTask spinningwheel;
            std::thread th1([&]() {
                spinningwheel.run();
            });
                        
            std::thread th2([&]() {
                                
                Maze2D maze(Maze2D::load_maze(load_path));
                if (maze.e.empty()) {
                    spinningwheel.stop();
                    th1.join();
                    th2.join();
                    return;
                }
                
                if (print_maze) {
                    Maze2D::print_maze(maze.maze_to_str());
                }
                
                solver(maze, method, print_maze, save_maze);
                
                spinningwheel.stop();
                
            });
            
            th1.join();
            th2.join();
            
        } else {
            
            auto msize{get_maze_size_from_cmdline()};
            if (!check_size(msize)) {
                std::cout << "Invalid maze size\n";
                return 1;
            }
            
            // generate a maze
            std::cout << "Generating maze...  ";
            
            WheelTask spinningwheel;
            std::thread th1([&]() {
                spinningwheel.run();
            });
            
            std::thread th2([&]() {
                
                Generator2D gen(msize.first, msize.second);
                Maze2D maze(gen.rbacktrack(seed_val));
                
                if (save_maze) {
                    std::cout << "\nSaving...  ";
                    maze.save_maze(save_path);
                }
                                
                // solve the maze
                solver(maze, method, print_maze, save_maze);                
                spinningwheel.stop();
                
                if (method == std::string() && print_maze) {
                    std::cout << "\nMaze seed = " << maze.seed;
                    Maze2D::print_maze(maze.maze_to_str());
                }
                
            });
            
            th1.join();
            th2.join();
            
        }
    } else {
        
        auto msize{get_maze_size_from_cmdline()};
        if (!check_size(msize)) {
            std::cout << "Invalid maze size\n";
            return 1;
        }
        
        std::cout << "Generating maze...  ";
        
        WheelTask spinningwheel;
        std::thread th1([&]() {
            spinningwheel.run();
        });
        
        std::thread th2([&]() {
            
            Generator2D gen(msize.first, msize.second);
            
            Maze2D maze(gen.rbacktrack());
            
            std::cout << "\nMaze seed = " << maze.seed << '\n';
            Maze2D::print_maze(maze.maze_to_str());
            std::cout << "\n";
            
            spinningwheel.stop();
            
        });
        
        th1.join();
        th2.join();
                
    }
      
    return 0;
}