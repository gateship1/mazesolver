#ifndef GENERATOR2D_HEADER_FILE
#define GENERATOR2D_HEADER_FILE

#include <algorithm> // std::find_if, std::sort
#include <cstdlib> // std::rand
#include <ctime>   // std::time
#include <iostream>
#include <stack>   // std::stack
#include <utility> // std::make_pair, std::pair
#include <vector> // std::vector

#include "compare_pairs.hpp"
#include "maze2d.hpp"

/* Generator
  
  a class that generates a 2D maze of size rows x cols
  
  - the maze generator is seeded and the seed is recoverable so it can be recreated
  - the default seed is the time since Epoch
  - the default seed can be overridden by providing a seed at instantiation of a new Generator object
*/
struct Generator2D {
    
    Generator2D(const int& rows_, const int& cols_) 
        : rows(rows_), cols(cols_), adj(Generator2D::build_adj(rows_, cols_)) {
    }
    
    // generator methods
    auto rbacktrack(const unsigned int& seed=std::time(nullptr)) -> Maze2D;
    
    private:
        const int rows, cols;
        const std::vector<std::vector<int>> adj; // adjacents
        
        // build the adjacency list for a new maze object
        static constexpr auto build_adj = [](const auto& rows, const auto& cols) {
            auto total_v{rows * cols};
            std::vector<std::vector<int>> adj_(rows * cols);
            for (auto v{0}; v < total_v; ++v) {
                auto up{v - cols};
                auto down{v + cols};
                auto left{v - 1};
                auto right{v + 1};
                // up
                if (up >= 0)
                    adj_.at(v).emplace_back(up);
                // right
                if ((right < total_v) && (v % cols < cols - 1))
                    adj_.at(v).emplace_back(right);
                // down
                if (down < total_v)
                    adj_.at(v).emplace_back(down);
                // left
                if ((left >= 0) && (v % cols != 0))
                    adj_.at(v).emplace_back(left);
            }
            return adj_;
        };
        
        auto set_special_vertex(const std::string&) const -> int;
};

#endif // GENERATOR2D_HEADER_FILE