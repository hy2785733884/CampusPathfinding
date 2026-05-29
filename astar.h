#pragma once
#include <vector>
using namespace std;

// A* 寻路算法
// 参数：起点(sx, sy)，终点(gx, gy)
// 输出：expandedNodes = 展开节点数，outExplored = 探索过的所有节点
// 返回：从起点到终点的路径节点序列（空 = 无路径）
vector<pair<int, int>> aStar(int sx, int sy, int gx, int gy,int& expandedNodes,vector<pair<int, int>>& outExplored);