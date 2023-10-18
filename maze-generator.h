#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include "maze.h"
#include "random"
#include <vector>

class MazeGenerator {
public:
    MazeGenerator();
    void setRandomSeed(int randomSeed) { std::srand(randomSeed); };
    Maze generateMaze(int columns, int rows) const;
};

#endif