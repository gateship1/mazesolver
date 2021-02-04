# SOLUTION FILES

Solution files for mazes are text files. The file name is of the format
```console
maze_<rows>x<cols>_<seed>_solution.txt
```
where ```<rows>``` are the number of rows in the maze, ```<cols>``` are the number of columns in the maze and ```<seed>``` is the seed used for the random number generator ```std::rand()``` used in the maze generation routine.

An example solution is
```console
maze_10x20_1612147230_solution.txt

###################################S#####
#   #         #   #     #         #.#...#
# # ##### ### ### # ### # # ##### #.#.#.#
# #   #   # #   # # # #   # #   # #.#.#.#
# ### # ### ### # # # ##### ### # #.#.#.#
# #   # #   #   #     #   #   # # #...#.#
# ### # # ### ####### # # ### # # # ###.#
#   #   #     #   #   # #     #   # #...#
### ######### # # ### # ####### ### #.# #
# #         #   #   # # # #     #   #.# #
# ######### ####### ### # # ##### ###.###
#     #     # #         #   #   # # #...#
# # # # ##### # ######### ### ### # ###.#
# # # #     #     #   #   #   #     #...#
# # ####### ####### ### ### ### #####.# #
# # #.....#         #   #       #.....# #
### #.###.########### ###########.##### #
#   #...#.......#     #.........#.#   # #
# #####.#######.# #####.#######.#.# # # #
#      .......#.........#      ...# #   #
#############E###########################
```

In a solution file ```'#'``` represents a wall ```' '``` represents a path, ```'S'``` represents the maze start (or entrance), ```'E'``` represents the maze end (or exit) and ```'.'``` represents a vertex in the solution path.