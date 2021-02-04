#ifndef BFS_HEADER_FILE
#define BFS_HEADER_FILE

#include <algorithm> // find
#include <queue> // queue
#include <utility> // pair

#include "maze2d.hpp"
#include "node.hpp"
#include "solution_path.hpp"

/* bfs
  
  performs a breadth-first search for the solution state (if it exists)
  
  parameters:
    maze, the maze on which to perform the breadth-first search
  
  return:
    the path to the solution vertex from the input vertex (empty if a path cannot be found)
    the number of moves explored to reach (or fail to reach) the solution vertex
*/
auto bfs(const Maze2D& maze) -> std::pair<Path<int>, size_t> {
    
    size_t moves_explored{0}; // initialize the number of moves explored
    
    // build a list of neighbors for each vertex
    auto next{maze.list_of_neighbors()};
    
    // create initial node based on input state (initial state)
    auto start = std::make_shared<Node<int>>(maze.start, nullptr);
    
    // set up a queue of nodes to explore
    std::queue<std::shared_ptr<Node<int>>> nqueue;
    nqueue.push(start); // add the initial node to priority queue
    
    // set up a list of nodes that have been "visited"
    // note only the vertex of these nodes is stored in the list
    std::vector<int> visited{};
    
    while(!nqueue.empty()) {
        
        auto current_node{nqueue.front()};
        nqueue.pop(); // remove current node from the queue
        
        // check the current node to see if it is the end / exit node
        if (current_node->vertex == maze.end) { // if the end / exit has been found
            Path<int> path(current_node);
            return std::make_pair(path, moves_explored);
        }
        
        // add the vertex for the current node to the list of visited states
        visited.emplace_back(current_node->vertex);
        
        for (const auto& next_vertex : next.at(current_node->vertex)) {
            if (!(std::find(visited.begin(), visited.end(), next_vertex) != visited.end())) {
                auto new_node = std::make_shared<Node<int>>(next_vertex, current_node, current_node->g + 1);
                nqueue.emplace(new_node); // put the new path on the queue
                visited.emplace_back(next_vertex);
            }
        }
        
        // increment the number of moves explored
        moves_explored++;
    }
    
    // a solution could not be found (or does not exist)
    Path<int> path(maze.start); // create a dummy path with the initial state then clear it
    path.path_objects.clear();
    return std::make_pair(path, moves_explored);
}

#endif // BFS_HEADER_FILE