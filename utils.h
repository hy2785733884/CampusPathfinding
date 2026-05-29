#pragma once
#include <vector>
#include <cmath>
using namespace std;

// 优先队列节点，用于A*和JPS的openlist表
struct PQNode {
    int x, y;
    double f;                         // f = g + h，总代价估计
    bool operator>(const PQNode& other) const {
        return f > other.f;          
    }
};

extern vector<vector<int>> grid;
extern int rows, cols;
extern int startX, startY, goalX, goalY;

// Octile 距离：允许八方向移动时的最优启发函数
double getDistance(int x1, int y1, int x2, int y2);

// 判断 (x, y) 是否可通行（在网格内且值为 0）
bool isWalkable(int x, int y);