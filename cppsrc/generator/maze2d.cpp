#include "maze2d.hpp"

/* list_of_neighbors
  
  generates a list of all the neighbor vertices for each vertex in the maze
  
  return:
    a list of each vertex in the maze and all its neighboring vertices

*/
auto Maze2D::list_of_neighbors() const -> std::vector<std::vector<int>> {
    
    std::vector<std::vector<int>> neighbors(this->rows * this->cols); // note, the index represents a vertex
    for (const auto& edge : this->e) {
        neighbors.at(edge.first).emplace_back(edge.second);
        neighbors.at(edge.second).emplace_back(edge.first);
    }
    return neighbors;
}

/* load_maze
  
  loads a pregenerated maze from a text file and creates a maze object
  
  parameters:
    input_file, the text file to load into a maze object
      NOTE: this text file must be in the format from the Generator2D class
  
  return:
    a new maze object
*/
auto Maze2D::load_maze(const std::string& input_file) -> Maze2D {
    
    // tokenize the maze file / path string
    auto maze_tokens{tokenize(input_file, '_')};
    
    // get the maze size (rows x cols) from the tokenized file
    auto maze_size_data{tokenize(maze_tokens.at(1), 'x')};
    std::stringstream row_str(maze_size_data.at(0));
    int maze_rows{0};
    row_str >> maze_rows;
    std::stringstream col_str(maze_size_data.at(1));
    int maze_cols{0};
    col_str >> maze_cols;
    
    // retrieve the maze seed from the tokenized file
    std::stringstream seed_str{*(tokenize(maze_tokens.back(), '.').begin())};
    unsigned int maze_seed{0};
    seed_str >> maze_seed;
    
    std::vector<std::pair<int, int>> mpath; // maze paths
    int start{-1}, end{-1}; // start and end vertices for the maze, respectively
    
    std::vector<int> spath; // list of vertices forming a solution path
    
    // read the maze file line by line
    std::fstream mazefile;
    mazefile.open(input_file, std::ios::in);
    if (mazefile.is_open()){
        std::string line;
        int row_count{0}, vertex{0};
        while(std::getline(mazefile, line)){
            if (row_count == 0) { // first line
                int col_count{0};
                for (const char& c : line) {
                    if (c == start_symbol) {
                        start = col_count / 2; // start vertex
                        break;
                    }
                    col_count++;
                }
            } else if (row_count == 2 * maze_rows) { // last line
                int col_count{0};
                for (const char& c : line) {
                    if (c == end_symbol) {
                        end = vertex - maze_cols + col_count / 2; // end vertex
                        break;
                    }
                    col_count++;
                }
            } else { // not the first line or last line
                int col_count{0};
                // read each row character by character to build the maze in memory
                if ((row_count) % 2 != 0) { // odd numbered rows (recall first row (row 0) is border)
                    for (const char& c : line) {
                        if (c == start_symbol) start = vertex; // start vertex
                        else if (c == end_symbol) end = vertex - 1; // end vertex
                        if (col_count != 0 && col_count != 2 * maze_cols) { // skip the first col and last col
                            if ((col_count) % 2 != 0) { // vertices
                                vertex++;
                            } else { // artificial cell designating path or no path between row vetices
                                if (c == path_symbol) { // this is a path, add it to the maze edges (path)
                                    mpath.emplace_back(std::make_pair(vertex - 1, vertex));
                                } else if (c == solution_symbol) {
                                    // if the character is a solution_symbol character, then add the vertex
                                    // and its partner to the maze solution path
                                    // note that these are both first checked for uniqueness in the solution path
                                    // to avoid duplication
                                    if (std::find(spath.begin(), spath.end(), vertex - 1) == spath.end()) {
                                        spath.emplace_back(vertex - 1);
                                    }
                                    if (std::find(spath.begin(), spath.end(), vertex) == spath.end()) {
                                        spath.emplace_back(vertex);
                                    } 
                                    // also add this vertex and its partner to the maze path
                                    mpath.emplace_back(std::make_pair(vertex - 1, vertex));
                                }
                            }
                        }            
                        col_count++;
                    }
                } else { // even - this is the row 'between' rows (it is present to allow a maze to be correctly rendered in the terminal)
                    int rowv{vertex}; // keep track of vertices in between row
                    for (const char& c : line) {
                        if (col_count != 0 && col_count != 2 * maze_cols) { // skip the first col and last col
                            if ((col_count) % 2 != 0) { // aligned w/ a vertex
                                if (c == path_symbol) {
                                    mpath.emplace_back(std::make_pair(rowv, rowv - maze_cols));
                                } else if (c == solution_symbol) {
                                    // if the character is a solution_symbol character, then add the vertex
                                    // and its partner to the maze solution path
                                    // note that these are both first checked for uniqueness in the solution path
                                    // to avoid duplication
                                    if (std::find(spath.begin(), spath.end(), rowv) == spath.end()) {
                                        spath.emplace_back(rowv);
                                    }
                                    if (std::find(spath.begin(), spath.end(), rowv - maze_cols) == spath.end()) {
                                        spath.emplace_back(rowv - maze_cols);
                                    }
                                    // also add this vertex and its partner to the maze path
                                    mpath.emplace_back(std::make_pair(rowv, rowv - maze_cols));
                                }
                                rowv++;
                            }
                        }
                        col_count++;
                    }
                }
            }
            row_count++;
        }        
        mazefile.close();
    } else {
        std::cout << "maze file cannot be opened for loading - check path\n";
        return Maze2D();
    }
    
    // sort the edges in the maze path (for use in solving)
    std::sort(mpath.begin(), mpath.end(), compare_pairs<int>);
    
    return Maze2D(maze_seed, maze_rows, maze_cols, start, end, mpath, spath);
}

/* maze_to_str
  
  NOTE: (for the future to remember) -> a vertex v is the vertex is the maze row * col, not the bloated
        vertex count for printing.
  
  return a list of strings that represents the maze for terminal printing or saving to a text file
*/
auto Maze2D::maze_to_str() const -> std::string {
    
    std::string maze_str{}; // stores the maze as a string for terminal output / saving to a text file
    auto start_str_pos{this->start}; // index of the start position (need to adjust to printed vertice)
    auto end_str_pos{this->end}; // index of the end position (need to adjust to printed vertice)
    
    /* path_or_solution
      
      lambda used in printing a solution
      
      parameters:
        solution_path, the list of vertices in the solution path for the maze object
        v, the vertex to check for in the solution path list
      
      return:
        if the vertex, v, is in the solution path the solution_symbol is returned
          otherwise, the path_symbol is returned (since all vertices are in the path)
        special case is when the solution path is empty, then the path_symbol is always returned
    */
    auto path_or_solution = [](const auto& solution_path, const auto& v) {
        
        if (solution_path.empty()) // check if a solution exists
            return path_symbol;
        return (std::find(solution_path.begin(), solution_path.end(), v) != solution_path.end()) 
               ? solution_symbol : path_symbol;
    };
    
    /* path_or_solution_pair
      
      lambda used in printing a solution
      
      parameters:
        solution_path, the list of vertices in the solution path for the maze object
        vpair, a pair of vertices to check for in the solution path list
      
      return:
        if BOTH vertices in the pair of vertices, vpair, are in the solution path the solution_symbol is returned
          otherwise, the path_symbol is returned
        special case is when the solution path is empty, then the path_symbol is always returned
    */
    auto path_or_solution_pair = [](const auto& solution_path, const auto& vpair) {
        
        if (solution_path.empty()) // check if a solution exists
            return path_symbol;
        return ((std::find(solution_path.begin(), solution_path.end(), vpair.first) != solution_path.end()) &&
                (std::find(solution_path.begin(), solution_path.end(), vpair.second) != solution_path.end()))
               ? solution_symbol : path_symbol;
    };
    
    // upper border
    for (int w{0}; w < 2 * this->cols + 1; ++w) {
        maze_str += wall_symbol;
    }
    maze_str += "\n";
    maze_str += wall_symbol; // initial left border in first maze row
    
    for (int v{0}; v < this->rows * this->cols; ++v) {
        
        // find 'special' vertices
        if (v == this->start) { // start position
            if (v == 0) { // upper right corner
                std::srand(this->seed); // randomly put the start on the top or left
                if (std::rand() % 2 == 0) start_str_pos = 2 * v + 1;
                else start_str_pos = maze_str.size() - 1;
            } else if (v < this->cols) { // special position along top row
                start_str_pos = 2 * v + 1;
            } else if (v % this->cols == 0) { // special position along left column
                start_str_pos = maze_str.size() - 1;
            }
        } else if (v == this->end) { // end position
            if (v == this->rows * this->cols - 1) { // lower left corner
                std::srand(this->seed); // randomly put the end on the right or bottom
                if (std::rand() % 2 == 0)  end_str_pos = maze_str.size() + 1;
                else end_str_pos = maze_str.size() + 2 * (this->cols + 1);
            } else if ((v + 1) % (this->cols) == 0) { // special position on right column
                end_str_pos = maze_str.size() + 1;
            } else if (v >= (this->rows - 1) * this->cols) { // special position along bottom row
                end_str_pos = maze_str.size() + 2 * (this->cols + 1);
            }
        }
        
        // every vertex is part of a path
        maze_str += path_or_solution(this->solution_path, v);
        
        // if a pair of vertices are in the maze path, they are connected
        // the maze path is an undirected graph, therefore pairs are checked in both directions
        if (std::find(this->e.begin(), this->e.end(), std::make_pair(v, v + 1)) != this->e.end()) {
            maze_str += path_or_solution_pair(this->solution_path, std::make_pair(v, v + 1));
        } else if (std::find(this->e.begin(), this->e.end(), std::make_pair(v + 1, v)) != this->e.end()) {
            maze_str += path_or_solution_pair(this->solution_path, std::make_pair(v + 1, v));
        }
        else {
            // check if need to move to the next row (like a typewriter)
            if ((v + 1) % this->cols == 0) {
                maze_str += wall_symbol; // right border
                maze_str += '\n'; // add row string to the maze strings list
                maze_str += wall_symbol; // left border
                
                // this is the row 'between' rows (it is present to allow a maze to be correctly rendered in the terminal)
                for (int vc{v + 1}; vc < (v + 1) + this->cols; ++vc) {
                    // like above, if a pair of vertices are in the maze path, they are connected
                    // the maze path is an undirected graph, therefore pairs are checked in both directions
                    if (std::find(this->e.begin(), this->e.end(), std::make_pair(vc, vc - this->cols)) != this->e.end())
                        maze_str += path_or_solution_pair(this->solution_path, std::make_pair(vc, vc - this->cols));
                    else if (std::find(this->e.begin(), this->e.end(), std::make_pair(vc - this->cols, vc)) != this->e.end())
                        maze_str += path_or_solution_pair(this->solution_path, std::make_pair(vc - this->cols, vc));
                    else // if not a path, it is a wall
                        maze_str += wall_symbol;
                    
                    maze_str += wall_symbol; // walls always exist at the intersection of 4 vertices.
                }
                
                // move to the next line after checking for vertical paths in the 'between' row
                if (v == this->rows * this->cols - 1) // end of the board
                    continue;
                else {
                    maze_str += '\n'; // next line
                    maze_str += wall_symbol; // left border
                }
            } else {
                maze_str += wall_symbol; // not a path - then it is a wall
            }
        }
    }
    
    // special vertices
    maze_str.at(start_str_pos) = start_symbol;
    maze_str.at(end_str_pos) = end_symbol;
    
    return maze_str;
}

auto Maze2D::print_maze(const std::string& maze_str) -> void {
    
    std::cout << '\n' << maze_str << '\n';
    return;
}

auto Maze2D::print_maze_size() const -> void {
    
    std::cout << this->rows << "x" << this->cols << " maze.\n";
    return;
}

auto Maze2D::print_e() const -> void {
    
    std::cout << "Edges : \n{";
    for (int p{0}; p < static_cast<int>(this->e.size()); ++p) {
        std::cout << "(" << e.at(p).first << ", " << e.at(p).second << ")";
        if (p != static_cast<int>(this->e.size()) - 1) std::cout << ", ";
        if ((p+1) % 10 == 0 && p != static_cast<int>(this->e.size()) -1) std::cout << "\n";
    }
    std::cout << "}\n";
    return;
}

/* save_maze
  
  save the maze to a text file
    - the file name is in the format maze_<rows>x<cols>_seed.txt
  
  parameters:
    save_path, the location for where the maze is to be saved
*/
auto Maze2D::save_maze(const std::string& save_path, const bool& is_solution) const -> void {
    
    std::ofstream file;
    auto build_filename = [&is_solution, this](){
        std::string fname{"maze_" + std::to_string(rows) + "x" 
        + std::to_string(cols) + "_" + std::to_string(seed)};
        return (is_solution) ? fname + "_solution.txt" : fname + ".txt";
    };
    const std::string filename{build_filename()};
    auto maze_file{save_path + "/" + filename};
    file.open(maze_file);
    if (!file.is_open()) {
        std::cout << "maze file cannot be opened for saving - check path\n";
        return;
    }
    
    // write maze to file
    auto maze_str{this->maze_to_str()};
    file << maze_str;
    
    file.close();
    
    std::cout << "\nmaze saved to: " << maze_file << "\n";
    
    return;
}
