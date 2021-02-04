#ifndef ASTAR_HEADER_FILE
#define ASTAR_HEADER_FILE

#include <iostream>
#include <memory> // make_shared, shared_ptr
#include <queue> // deque, priority_queue
#include <utility> // pair
#include <vector>

#include "heuristics.hpp"
#include "maze2d.hpp"
#include "node.hpp"
#include "solution_path.hpp"

/* astar
  
  performs an A* search to find a path through the maze from the start to the end
  
  parameters:
    maze, the maze on which to perform the A* search
    heuristic, the heuristic function to use in the A* search
  
  return,
    the path to the solution vertex from the input vertex (empty if a path cannot be found)
    the number of moves explored to reach (or fail to reach) the solution vertex
*/
template <typename func>
auto astar(const Maze2D& maze, func heuristic) -> std::pair<Path<int>, size_t> {
    
    size_t moves_explored{0}; // initialize the number of moves explored
    
    // build a list of neighbors for each vertex
    auto next{maze.list_of_neighbors()};    
    
    // create initial node based on input vertex (initial vertex)
    auto start = std::make_shared<Node<int>>(maze.start, nullptr, 0, heuristic(maze, maze.start));
    
    // custom comparator to build the special value priority queue (lowest 'f' value gets priority)
    const auto& cmp = [](const std::shared_ptr<Node<int>> lhs, const std::shared_ptr<Node<int>> rhs) {
        return lhs->f > rhs->f;
    };
    // set up a special value priority queue - priority is given to the node with the smallest 'f' value
    std::priority_queue<std::shared_ptr<Node<int>>, std::vector<std::shared_ptr<Node<int>>>, decltype(cmp)> open_(cmp);
    open_.push(start); // add the initial node to priority queue
    
    // create a list of nodes that have been visited (closed)
    // note only the vertex of these nodes is stored in the list
    std::vector<int> closed_{maze.start}; // <- close the vertex number here
    
    // A* algorithm - continue search for solution vertex as long as the open list contains unvisited nodes
    while(!open_.empty()) {
        
        // current node being inspected for a solution vertex
        auto current_node{open_.top()}; // node in the special value priority queue with the smallest 'f' value
        open_.pop(); // remove current node from open
        
        // check the current node to see if it is the end / exit node
        if (current_node->vertex == maze.end) { // if the end / exit has been found
            Path<int> path(current_node);
            return std::make_pair(path, moves_explored); // return the solution path and the number of moves explored to find it
        }
        
        // add the vertex for the current node to the list of closed vertices
        closed_.emplace_back(current_node->vertex);
        
        // add all the possible next vertices from the current node to the priority queue (they are sorted upon addition by lowest f)        
        for (const auto& next_vertex : next.at(current_node->vertex)) {
            if (!(std::find(closed_.begin(), closed_.end(), next_vertex) != closed_.end())) {
                auto new_node = std::make_shared<Node<int>>(next_vertex, current_node, current_node->g + 1, heuristic(maze, next_vertex));
                open_.push(new_node);
                closed_.emplace_back(next_vertex);
            }
        }
        
        // increment the number of moves explored
        moves_explored++;
        
    }
    
    // a solution could not be found (or does not exist)
    Path<int> path(maze.start); // create a dummy path with the initial vertex then clear it
    path.path_objects.clear();
    return std::make_pair(path, moves_explored); // return an empty solution path with the number of moves explored
}

#endif // ASTAR_HEADER_FILE