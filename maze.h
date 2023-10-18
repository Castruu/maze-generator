#ifndef MAZE_H
#define MAZE_H

#include<vector>
#include <utility>
#include "celltype.h"
#include "position.h"

class Maze {
public:
    Maze(int rows, int columns);

    CellType getCellType(Position pos) const;
    std::pair<CellType, CellType> getHorizontalNeighbours(Position pos) const;
    std::pair<CellType, CellType> getVerticalNeighbours(Position pos) const;

    std::vector<std::vector<CellType> > getMaze() const;

    bool generate(Position startPosition);

private:
    std::vector<std::vector<CellType> > maze;
    int rows;
    int columns;

    bool checkMoveValidity(Position movePosition);
    bool isLastSquare(Position position) { return position.getRow() == (maze.size() - 1) && position.getColumn() == (maze.back().size() - 1); };

    std::vector<std::pair<int, int> > randomizeMoves();

    int RANDOMIZATION_FACTOR = 50;
    const std::vector<std::pair<int, int> > POSSIBLE_MOVES = { {0, 2}, {2, 0}, {0, -2}, {-2, 0} };
};

#endif