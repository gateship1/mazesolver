#include "generator2d.hpp"

/* rbacktrack
  
  recursive backtracking algorithm used to carve out a unique maze path
*/
auto Generator2D::rbacktrack(const unsigned int& seed) -> Maze2D {
    
    std::srand(seed); // seed the random number generator
    
    std::vector<bool> visited(this->adj.size(), false); // maze vertices
    std::vector<std::pair<int, int>> mpath; // maze path
    
    // create a stack of vertices and choose a random vertex to start
    std::stack<int> vertices;
    const int start_vertex{std::rand() % static_cast<int>(visited.size())};
    vertices.push(start_vertex); // put the start vertex on the stack
    visited.at(start_vertex) = true; // make it as visited
    size_t visited_vertices_count{1}; // number of visited vertices
    
    // recursive backtracking
    while (visited_vertices_count < static_cast<size_t>(this->adj.size())) {
        
        std::vector<int> neighbors; // get all neighbors of the current vertex from its adjacency list
        for (const auto& neighbor : this->adj.at(vertices.top())) {
            if (visited.at(neighbor)) continue; // skip neighbor if it has already been visited
            else neighbors.emplace_back(neighbor); // otherwise add it to the list of unvisited neighbors
        }
        if (neighbors.empty()) { // if there are no unvisited neighbors for the current vertex, backtrack
            vertices.pop();
            continue;
        }
        // pick a random neighbor from the list of current vertex neighbors
        auto neighbor{neighbors.at(std::rand() % neighbors.size())};
        // add the current vertex and its neighbor to the carved maze path
        mpath.emplace_back(std::make_pair(vertices.top(), neighbor));
        
        vertices.push(neighbor); // add the neighbor to the top of the stack (it is now the current vertex)
        visited.at(neighbor) = true; // mark the neighbor as visited
        visited_vertices_count++; // increment the number of visited vertices
    }
    
    return Maze2D(seed, this->rows, this->cols, this->set_special_vertex("start"), this->set_special_vertex("end"), mpath);
}

/* set_special_vertex
  
  randomly assign the starting / ending of the maze
    - the maze start can be on the left wall or top wall of the 2D maze, note if a seed is provided
      to the maze generator, then the start is reproduced for that seed for the given maze    
    - the maze end can be on the right wall or bottom wall of the 2D maze, note if a seed is provided
      to the maze generator, then the end is reproduced for that seed for the given maze
  
  parameters:
    the string toggle for the "start" or "end" of the maze
  
  return:
    the vertex number of the start or end of the maze, depengin on the passed string
*/
auto Generator2D::set_special_vertex(const std::string& vtype) const -> int {
    
    auto rrow{std::rand() % this->rows};
    auto rcol{std::rand() % this->cols};
    auto r_or_c{std::rand() % 2};
    if (vtype == "start")
        return (
            [this](const auto& row, const auto& col, const auto& r_or_c){ 
                return r_or_c == 0 ? row * this->cols // puts start on the left wall
                                 : col; // puts start on the top wall
                }(rrow, rcol, r_or_c)
        );
    else if (vtype == "end")
        return (
            [this](const auto& row, const auto& col, const auto& r_or_c){ 
                return r_or_c == 0 ? (this->rows - 1) * this->cols + col // puts end on the bottom wall
                                 : (this->cols - 1) + row * (this->cols); // puts end on the right wall
                }(rrow, rcol, r_or_c)
        );
    else
        return -1; // invalid string passed in
}