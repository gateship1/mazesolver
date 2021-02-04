# MAZE MADNESS

Welcome! This repository is for a C++17 implementation of a 2D Maze Generator and Solver.

This code is implemented to run in the terminal using text files and terminal output.

The source code has been developed for fun, i.e. to generate mazes and explore various solution algorithms and modern C++ containers in the STL. [CMake](https://cmake.org/) files are provided to assist building the code. Currently, it is setup for a Linux build, but this can be simply extended to Windows or Mac, if desired. It is provided as free & open-source software.

## Table of Contents

* [Prerequisites](#prerequisites)
* [Build and Run Maze Generator](#build-and-run-maze-generator)
* [Build a Maze](#build-a-maze)
* [Solve a Maze](#solve-a-maze)
* [Additional Notes](#additional-notes)

## Prerequisites

* A compiler that supports C++17
* [CMake](https://cmake.org/) Version 3.13.4 (or later)

## Build and Run Maze Generator

### Linux Build

In the parent directory containing the *CMakeLists.txt* file:
```console
mkdir build
cd build
```

The directory structure is now:
```console
mazesolver/
├── build/
├── cppsrc/
│   ├── generator/
│   │   └── CMakeLists.txt
│   └── CMakeLists.txt
├── mazes/
│   └── README.md
├── solutions/
│   └── README.md
├── .gitignore
├── CMakeLists.txt
├── LICENSE
└── README.md
```

In the ```build/``` directory
```console
cmake .. && make
```

### Build a Maze

When building a maze, a number of optional commands are available:
* ```seed```
* ```print```
* ```save```

These commands can be used individually or in any combination. The order of the commands does not matter. The commands are expanded upon in the following.

#### Build a Randomly Seeded Maze
The maze generator uses a recursive back-tracker algorithm to randomly generate mazes. A maze can be generated from the ```build/``` directory using the following command:

```console
./cppsrc/maze.x
```
A maze built in this manner will be randomly seeded (using the time since Epoch). When a maze is built, the code will ask for the number of rows and the number of columns as input from the terminal.

#### Build a Maze with a Provided Seed
A maze can be manually seeded using the ```seed``` command, followed by a seed. For example, from the ```build/``` directory,
```console
./cppsrc/maze.x seed <seed>
```
will build a maze using the seed ```<seed>```.

#### Print a Maze to the Terminal
A maze can be printed to the  terminal using the ```print``` command. For example, from the ```build/``` directory,
```console
./cppsrc/maze.x print
```

#### Save a Generated Maze
A maze can be saved once it is generated printed to the using the ```save``` command. For example, from the ```build/``` directory,
```console
./cppsrc/maze.x save <save_path>
```
where ```<save_path>``` is the relative path from the current directory OR the absolute system path to the directory in which to save the maze. It is recommended to save mazes to the provided ```mazes/``` directory; however, this is not a requirement of the code. When a maze is saved, it is saved with the format:
```console
maze_<rows>x<cols>_<seed>.txt
```
This file format provides the size of the maze as well as the seed used to generate the maze. This allows for reproduceability.

### Load a Maze

A pre-generated maze can be loaded by the code, granted it is in the format output by the Maze Generator (see [Build a Maze](#build-a-maze)). A maze can be loaded using the following command from the ```build/``` directory,
```console
./cppsrc/maze.x load <path_to_maze_file>
```
where ```<path_to_maze_file>``` is the relative path from the current directory OR the absolute system path to the directory in which the maze to load is saved. Note this includes the maze file name, which must be in the format described in [Save a Generated Maze](#save-a-generated-maze). 

### Solve a Maze

Three search algorithms are provided:
* A* search
* Breadth-first search
* Depth-first search

The search algorithms can be combined with the ```load```, ```save``` and ```print``` commands.

#### astar

The ```astar``` command performs an A* search for a solution. It will either find a solution, print the number of moves it explored whilst searching for the solution, OR it will fail to find a solution and print the number of moves it explored whilst searching for the solution. An example of an A* run using a sample board is
```console
./cppsrc/maze.x astar
```
The heuristic used in the A* search is a combination of the manhattan distance and the Euclidean distance between the leading vertex in the search path and the end / exit of the maze.

#### bfs

The ```bfs``` command performs a breadth-first search for a solution. It will either find a solution, print the number of moves it explored whilst searching for the solution, OR it will fail to find a solution and print the number of moves it explored whilst searching for the solution. An example of an A* run using a sample board is
```console
./cppsrc/maze.x bfs
```

#### dfs

The ```dfs``` command performs a depth-first search for a solution. It will either find a solution, print the number of moves it explored whilst searching for the solution, OR it will fail to find a solution and print the number of moves it explored whilst searching for the solution. An example of an A* run using a sample board is
```console
./cppsrc/maze.x dfs
```

## Additional Notes

This code is provided free and open source for educational purposes. The code is optimized for learning and not necessarily for efficiency or compactness. It is solely the work of the author.
