#ifndef MAP_H
#define MAP_H

#include <vector>

enum class Type {
    empty = 0, door = 1, wall = 2, fakeDoor = 3, keyDoor =4
};

class Map {
public:

    Map(unsigned rowSize, unsigned colSize);

    unsigned getRowSize() const;

    unsigned getColSize() const;

    void setValue(const unsigned rowNumber, const unsigned colNumber, Type value);

    Type &operator()(const unsigned rowNumber, const unsigned colNumber);

    ~Map();

private:
    unsigned rowSize;
    unsigned colSize;
    std::vector<std::vector<Type>> map;
};

#endif //MAP_H
