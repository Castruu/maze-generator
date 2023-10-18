#ifndef POSITIONH
#define POSITIONH

#include <utility>

class Position {
public:
    Position(): row(-1), column(-1) {};
    Position(int row, int column): row(row), column(column) {};
    int getRow() const { return row; };
    int getColumn() const { return column; };
    std::pair<int, int> asPair() const { return {row, column}; };

    bool operator==(Position otherPos) { return column == otherPos.column && row == otherPos.row; }

private:
    int row;
    int column;
};

#endif