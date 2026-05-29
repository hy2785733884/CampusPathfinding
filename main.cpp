#include "utils.h"
#include "astar.h"
#include "jps.h"
#include "visualization.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <conio.h>
#include <easyx.h>
using namespace std;

int main() {
    // 1. 读取地图文件
    ifstream file("map.txt");
    if (!file.is_open()) {
        cerr << "无法打开 map.txt 文件！请确认该文件在 exe 同级目录下。" << endl;
        return 1;
    }

    string line;
    grid.clear();
    int maxCols = 0;
    vector<string> rawLines;

    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        rawLines.push_back(line);
        if ((int)line.size() > maxCols) maxCols = (int)line.size();
    }
    file.close();

    rows = (int)rawLines.size();
    cols = maxCols;
    grid.resize(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; i++) {
        const string& ln = rawLines[i];
        for (int j = 0; j < (int)ln.size(); j++) {
            char c = ln[j];
            if (c == 'S') { startX = i; startY = j; grid[i][j] = 0; }
            else if (c == 'G') { goalX = i; goalY = j; grid[i][j] = 0; }
            else if (c == '#') { grid[i][j] = 1; }
            else { grid[i][j] = 0; }
        }
    }

    // 2. A* 寻路 + 高精度计时
    int aNodes = 0, jNodes = 0;
    vector<pair<int, int>> aExplored, jExplored;

    auto t1 = chrono::high_resolution_clock::now();
    auto aPath = aStar(startX, startY, goalX, goalY, aNodes, aExplored);
    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> aTimeSpan = t2 - t1;
    double aTime = aTimeSpan.count();

    // 3. JPS 寻路 + 高精度计时
    auto t3 = chrono::high_resolution_clock::now();
    auto jPath = jps(startX, startY, goalX, goalY, jNodes, jExplored);
    auto t4 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> jTimeSpan = t4 - t3;
    double jTime = jTimeSpan.count();

    // 4. 可视化展示
    drawMap(aPath, jPath, aTime, jTime, aNodes, jNodes, aExplored, jExplored);

    _getch();
    closegraph();
    return 0;
}