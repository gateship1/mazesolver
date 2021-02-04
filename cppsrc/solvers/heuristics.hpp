#ifndef HEURISTICS_HEADER_FILE
#define HEURISTICS_HEADER_FILE

#include <cmath>

#include "maze2d.hpp"

/* heuristic0
  
  returns '0' as the heuristic (so A* can be used as a BFS - mainly for demo purposes)
  
  parameter:
    maze, the maze object to be solved - irrelevant as it will always return 0
    vertex, the current leading vertex - irrelevant as it will always return 0
  
  return:
    0
*/
auto heuristic0 = [](const Maze2D& maze, const int& vertex) {
    
    return 0;
};

/* vertex_coordinates_2D
  
  return the 2D Cartesian coordinates of a vertex in a maze
*/
auto vertex_coordinates_2D = [](const Maze2D& maze, const int& v){
    
    auto r{v / maze.cols};
    auto c{v - (r *maze.cols)};
    
    return std::make_pair(r, c);
};

/* manhattan_distance_2D
  
  calculate the manhattan distance between the goal location and the leading vertex in the current solution path
  
  parameter:
    maze, the maze object to be solved
    vertex, the current leading vertex
  
  return:
    the calculated manhattan distance
*/
auto manhattan_distance_2D = [](const Maze2D& maze, const int& vertex) {
  
  auto goal{vertex_coordinates_2D(maze, maze.end)};
  auto v{vertex_coordinates_2D(maze, vertex)};
  
  auto delta_row{v.first - goal.first};
  auto delta_col{v.second - goal.second};

  return (delta_row + delta_col);
};

/* euclidean_distance_2D
  
  calculate the Euclidean distance between the goal location and the leading vertex in the current solution path
  
  parameter:
    maze, the maze object to be solved
    vertex, the current leading vertex
  
  return:
    the calculated Euclidean distance
*/
auto euclidean_distance_2D = [](const Maze2D &maze, const int &vertex) {
  
  auto goal{vertex_coordinates_2D(maze, maze.end)};
  auto v{vertex_coordinates_2D(maze, vertex)};

  return (sqrt(pow(goal.first - v.first, 2) + pow(goal.second - v.second, 2)));
};


/* astar_heuristic
  
  a heuristic that combines the manhattan distance and Euclidean distance between the current vertex and
  the goal (end / exit) vertex for use in the A* algorithm
  
  parameter:
    maze, the maze to be solved
    vertex, the current vertex in the solution path
  
  return:
    the manhattan distance + the Euclidean distance
*/
auto astar_heuristic = [](const Maze2D& maze, const int& vertex) {
  
  return (manhattan_distance_2D(maze, vertex) + euclidean_distance_2D(maze, vertex));
};

#endif // HEURISTICS_HEADER_FILE