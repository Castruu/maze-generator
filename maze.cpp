#include <vector>
#include <iostream>
#include <cstdlib>
#include "celltype.h"
#include "position.h"
#include "maze.h"

Maze::Maze(int rows, int columns) : rows(2 * rows - 1), columns(2 * columns - 1) {
    maze = std::vector<std::vector<CellType> >(this->rows, std::vector<CellType>(this->columns, CellType::WALL));
    maze.at(0).at(0) = CellType::START;
}

std::vector<std::vector<CellType> > Maze::getMaze() const {
    return maze;
}

bool Maze::generate(Position startPosition) {
    std::vector<std::pair<int, int> > moves = randomizeMoves();

    if (isLastSquare(startPosition)) {
        return true;
    };

    for (int i = 0; i < moves.size(); i++) {
        int finalRow = startPosition.getRow() + moves.at(i).first;
        int finalColumn = startPosition.getColumn() + moves.at(i).second;
        Position destination = Position(finalRow, finalColumn);
        if (!checkMoveValidity(destination)) {
            continue;
        }

        maze.at(finalRow).at(finalColumn) = isLastSquare(destination) ? CellType::END : CellType::BLANK;
        maze.at(startPosition.getRow() + (moves.at(i).first / 2)).at(startPosition.getColumn() + (moves.at(i).second / 2)) = CellType::CONNECTION;

        if (generate({ destination })) {
            maze.at(startPosition.getRow()).at(startPosition.getColumn()) = CellType::PATH;
        }
    }

    return getCellType(startPosition) == CellType::PATH;
}

CellType Maze::getCellType(Position pos) const {
    return maze.at(pos.getRow()).at(pos.getColumn());
}

bool Maze::checkMoveValidity(Position position) {
    int row = position.getRow();
    int column = position.getColumn();
    return row < rows && row >= 0 && column < columns && column >= 0 && (getCellType(position) == CellType::WALL);
}

std::vector<std::pair<int, int> > Maze::randomizeMoves() {
    std::vector<std::pair<int, int> > moves = POSSIBLE_MOVES;
    for (int i = 0; i < RANDOMIZATION_FACTOR; i++) {
        int firstRandom = std::rand() % 4;
        int secondRandom = std::rand() % 4;
        std::swap(moves.at(firstRandom), moves.at(secondRandom));
    }
    return moves;
}

std::pair<CellType, CellType> Maze::getHorizontalNeighbours(Position pos) const {
    Position left(pos.getRow(), pos.getColumn() - 1);
    Position right(pos.getRow(), pos.getColumn() + 1);
    if (columns == 1) {
        return { CellType::OFFBOUNDS, CellType::OFFBOUNDS };
    }
    if (pos.getColumn() == columns - 1) {
        return { getCellType(left), CellType::OFFBOUNDS };
    }
    if (pos.getColumn() == 0) {
        return { CellType::OFFBOUNDS,  getCellType(right) };
    }

    return { getCellType(left), getCellType(right) };
};

std::pair<CellType, CellType> Maze::getVerticalNeighbours(Position pos) const {
    Position top(pos.getRow() + 1, pos.getColumn());
    Position bottom(pos.getRow() - 1, pos.getColumn());
    if(rows == 1) {
        return { CellType::OFFBOUNDS, CellType::OFFBOUNDS };
    }

    if (pos.getRow() == 0) {
        return { getCellType(top), CellType::OFFBOUNDS };
    }
    if (pos.getRow() == rows - 1) {
        return { CellType::OFFBOUNDS, getCellType(bottom) };
    }

    return { getCellType(top), getCellType(bottom) };
};