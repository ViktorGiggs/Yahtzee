#include "Cube.h"
#include <cstdlib>
#include <vector>

Cube::Cube() {
    top = rand() % 6 + 1;
    bottom = rand() % 6 + 1;
    front = rand() % 6 + 1;
    back = rand() % 6 + 1;
    left = rand() % 6 + 1;
    right = rand() % 6 + 1;
    isBlocked = false;
}

std::vector<int> getFrontValues(Cube cubes[5]) {
    std::vector<int> frontValues;
    for (int i = 0; i < 5; i++) {
        frontValues.push_back(cubes[i].front);
    }
    return frontValues;
}

int countDroppedNumbers(Cube cubes[5]) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += cubes[i].front;
    }
    return sum;
}
