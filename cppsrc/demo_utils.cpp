#include "astar.hpp"
#include "bfs.hpp"
#include "demo_utils.hpp"
#include "dfs.hpp"

/* check_size
  
  check the size of the input maze to ensure it is "large enough"
  min size is 4 for rows and cols
  
  parameters:
    msize, the rows (first) and columns (second) for the maze input from the cmdline
  
  return:
    true if the maze rows and columns both meet the minimum size requirements
    false otherwise  
*/
auto check_size(const std::pair<int, int>& msize) -> bool {
    
    return (msize.first <= 4 || msize.second <= 4) ? false : true;
}

/* get_maze_size_from_cmdline
  
  get the maze size from the terminal input
  
  return:
    a pair representing the maze rows (first) and columns (second) from the terminal input
  
*/
auto get_maze_size_from_cmdline() -> std::pair<int, int> {
    
    int rows{}, cols{};
    
    std::cout << "rows: ";
    std::cin >> rows;
    std::cout << "cols: ";
    std::cin >> cols;
    
    return std::make_pair(rows, cols);
};

/* print_move_count
  
  display the number of moves required to find solution to the terminal
  
  parameters:
    solution, second item in the pair is the number of moves
*/
auto print_move_count(const std::pair<Path<int>, size_t>& solution) -> void {
    
    if (solution.first.path_objects.empty()) {
        std::cout << "\nSolution could not be found.\n"
                  << solution.second << " moves explored.\n";
    } else {
        std::cout << "\nSolution found!\n"
                  << solution.second << " moves explored.\n";
    }
    return;
}

/* solver
  
  solves the maze using the input method

  parameters:
    maze, the maze to solve
    method, the method to use to solve the maze (A*, BFS, DFS)
    print_maze, boolean telling the code whether or not to print the solution
    save_maze, boolean telling the code whether or not to save the solution
*/
auto solver(Maze2D& maze, const std::string& method, const bool& print_maze, const bool& save_maze) -> void {
    
    if (method.empty()) return; // return if it is not desired to solve the maze
    
    // lambda for terminal display
    auto display = [&maze, &print_maze, &save_maze](const auto& solution) {
        maze.solution_path = solution.first.path_objects;
        print_move_count(solution);
        
        if (print_maze) {
            std::cout << "\nSolution path:";
            Maze2D::print_maze(maze.maze_to_str());
        }
        if (save_maze) {
            std::cout << "Saving...  ";
            maze.save_maze("../solutions", true);
        }
    };
    
    // solve the maze
    std::cout << "\nSolving...  ";
    if (method == "astar") {
        auto solution{astar(maze, astar_heuristic)};
        display(solution);
    } else if (method == "bfs") {
        auto solution{bfs(maze)};
        display(solution);
    } else if (method == "dfs") {
        auto solution{dfs(maze)};
        display(solution);
    }
    
    return;
}