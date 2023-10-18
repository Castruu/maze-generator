#include <iostream>
#include <string>
#include "celltype.h"
#include "maze-printer.h"

void MazePrinter::print(const Maze& maze) const {
    printMazeVerticalBorders(maze);

    for (int i = 0; i < maze.getMaze().size(); i++) {
        std::string externalWall = i % 2 == 0 ? "|" : "+";
        std::cout << externalWall;
        for (int j = 0; j < maze.getMaze().at(i).size(); j++) {
            Position pos(i, j);
            std::cout << getCellOutput(maze, pos);
        }
        std::cout << externalWall << std::endl;
    }

    printMazeVerticalBorders(maze);
}

void MazePrinter::printMazeVerticalBorders(const Maze& maze) const {
    for (int i = 0; i < maze.getMaze().back().size() + 2; i++) {
        std::string output = i % 2 == 0 ? "+" : "---";
        std::cout << output;
    }
    std::cout << std::endl;
}

std::string MazePrinter::getCellOutput(const Maze& maze, Position pos) const {
    CellType cellType = maze.getCellType(pos);
    switch (cellType) {
    case WALL: {
        return getWallOutput(maze, pos);
    }
    case CONNECTION: {
        return getConnectionOutput(maze, pos);
    }
    case BLANK:
        return "   ";
    case PATH:
    case END:
    case START:
        return " . ";
    default:
        return "";
    }
}

std::string MazePrinter::getWallOutput(const Maze& maze, Position pos) const {
    if (pos.getRow() % 2 != 0 && pos.getColumn() % 2 != 0) return "+";

    std::pair<CellType, CellType> horizontalNeighbours = maze.getHorizontalNeighbours(pos);
    bool isHorizontal = false;
    if (horizontalNeighbours.first != CellType::OFFBOUNDS) {
        isHorizontal = horizontalNeighbours.first == CellType::WALL;
    }
    if (horizontalNeighbours.second != CellType::OFFBOUNDS) {
        isHorizontal = isHorizontal || horizontalNeighbours.second == CellType::WALL;
    }

    return isHorizontal ? "---" : "|";
}

std::string MazePrinter::getConnectionOutput(const Maze& maze, Position pos) const {
    std::pair<CellType, CellType> horizontalNeighbours = maze.getHorizontalNeighbours(pos);
    bool isSpaceNeeded = true;

    if (horizontalNeighbours.first != CellType::OFFBOUNDS) {
        isSpaceNeeded = horizontalNeighbours.first != CellType::BLANK && horizontalNeighbours.first != CellType::PATH;
    }

    if (horizontalNeighbours.second != CellType::OFFBOUNDS) {
        isSpaceNeeded = isSpaceNeeded && horizontalNeighbours.second != CellType::BLANK && horizontalNeighbours.second != CellType::PATH;
    }

    return isSpaceNeeded ? "   " : " ";
}