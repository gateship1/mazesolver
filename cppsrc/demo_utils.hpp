#ifndef DEMO_UTILS_HEADER_FILE
#define DEMO_UTILS_HEADER_FILE

#include <iostream>
#include <unistd.h> // sleep
#include <utility> // std::pair

#include "maze2d.hpp"
#include "solution_path.hpp"

auto check_size(const std::pair<int, int>&) -> bool;
auto get_maze_size_from_cmdline() -> std::pair<int, int>;
auto print_move_count(const std::pair<Path<int>, size_t>&) -> void;
auto solver(Maze2D&, const std::string&, const bool&, const bool&) -> void;

#endif // DEMO_UTILS_HEADER_FILE