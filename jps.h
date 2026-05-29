#pragma once
#include <vector>
using namespace std;

// JPS (Jump Point Search) 寻路算法
// 接口与 aStar 完全一致，方便对比调用
vector<pair<int, int>> jps(int sx, int sy, int gx, int gy,int& expandedNodes,vector<pair<int, int>>& outExplored);