#include "utils.h"

vector<vector<int>> grid;
int rows, cols;
int startX, startY, goalX, goalY;

double getDistance(int x1, int y1, int x2, int y2) {
    double dx = abs(x1 - x2);
    double dy = abs(y1 - y2);
    return (dx + dy) + (1.41421356 - 2.0) * min(dx, dy);
}

bool isWalkable(int x, int y) {
    if (x < 0 || x >= rows || y < 0 || y >= cols) return false;
    return grid[x][y] == 0;
}