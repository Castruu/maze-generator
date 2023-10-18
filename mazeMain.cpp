#include <iostream>
#include <string>
#include <stdexcept>
#include "maze-generator.h"
#include "maze-printer.h"
#include "maze.h"

int main(int argc, char* argv[]) {
    try {
        if (argc != 3 && argc != 4) {
            throw std::runtime_error("wrong argument list");
        }
        int columns = std::stoi(argv[1]);
        int rows = std::stoi(argv[2]);

        MazeGenerator generator;
        MazePrinter printer;

        if(argc == 4) {
            int randomSeed = std::stoi(argv[3]);
            generator.setRandomSeed(randomSeed);
        }
    
        Maze maze = generator.generateMaze(columns, rows);
        printer.print(maze);
    } catch(std::runtime_error e) {
        std::cerr << "An error ocurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}