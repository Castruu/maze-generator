#include <cstdlib>
#include "maze.h"
#include "maze-generator.h"


MazeGenerator::MazeGenerator() {
    std::srand(time(0));
}

Maze MazeGenerator::generateMaze(int columns, int rows) const {
    Maze maze(columns, rows);

    maze.generate({ 0, 0 });

    return maze;
}