#pragma once
#include <vector>
using namespace std;
// 使用 EasyX 绘制地图、两条路径和性能对比统计
void drawMap(const vector<pair<int, int>>& aPath,const vector<pair<int, int>>& jPath,double aTime, double jTime,int aNodes, int jNodes,const vector<pair<int, int>>& aExplored,const vector<pair<int, int>>& jExplored);