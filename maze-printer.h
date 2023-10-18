#ifndef MAZEPRINTER_H
#define MAZEPRINTER_H

#include <string>
#include "maze.h"
#include "position.h"

class MazePrinter {
public:
    void print(const Maze& maze) const;

private:    
    void printMazeVerticalBorders(const Maze& maze) const;
    std::string getCellOutput(const Maze& maze, Position pos) const;
    std::string getWallOutput(const Maze& maze, Position pos) const;
    std::string getConnectionOutput(const Maze& maze, Position pos) const;
};

#endif