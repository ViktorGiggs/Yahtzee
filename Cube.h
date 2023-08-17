#ifndef CUBE_H
#define CUBE_H

#include <vector>

class Cube {
public:
    int top, bottom, front, back, left, right;
    bool isBlocked;

    Cube();
};

std::vector<int> getFrontValues(Cube cubes[5]);
int countDroppedNumbers(Cube cubes[5]);

#endif
