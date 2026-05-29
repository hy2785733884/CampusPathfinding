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
#include <io.h>       
using namespace std;

int main(int argc, char* argv[]) {
    string filepath;
    if (argc >= 2) {
        // 方式A：命令行参数指定
        filepath = argv[1];
    }
    else {
        // 方式B：扫描 maps 文件夹列出所有.txt
        vector<string> mapFiles;
        string mapsDir = "maps";

        string searchPattern = mapsDir + "\\*.txt";
        _finddata_t fileInfo;
        intptr_t handle = _findfirst(searchPattern.c_str(), &fileInfo);

        if (handle != -1) {
            do {
 
                if (!(fileInfo.attrib & _A_SUBDIR)) {
                    mapFiles.push_back(fileInfo.name);
                }
            } while (_findnext(handle, &fileInfo) == 0);
            _findclose(handle);
        }

        if (mapFiles.empty()) {
            cerr << "maps 文件夹中没有找到 .txt 地图文件！" << endl;
            return 1;
        }

        cout << "可用的地图文件：" << endl;
        for (size_t i = 0; i < mapFiles.size(); i++) {
            cout << "  " << (i + 1) << ". " << mapFiles[i] << endl;
        }

        cout << "请输入编号选择地图（默认 1）：";
        string input;
        getline(cin, input);

        int choice = 1;
        if (!input.empty()) {
            choice = stoi(input);
        }
        if (choice < 1 || choice >(int)mapFiles.size()) {
            choice = 1;
        }

        filepath = mapsDir + "/" + mapFiles[choice - 1];
        cout << "已选择：" << filepath << endl;
    }


    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "无法打开地图文件：" << filepath << endl;
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

 
    int aNodes = 0, jNodes = 0;
    vector<pair<int, int>> aExplored, jExplored;

    auto t1 = chrono::high_resolution_clock::now();
    auto aPath = aStar(startX, startY, goalX, goalY, aNodes, aExplored);
    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> aTimeSpan = t2 - t1;
    double aTime = aTimeSpan.count();

  
    auto t3 = chrono::high_resolution_clock::now();
    auto jPath = jps(startX, startY, goalX, goalY, jNodes, jExplored);
    auto t4 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> jTimeSpan = t4 - t3;
    double jTime = jTimeSpan.count();

    
    drawMap(aPath, jPath, aTime, jTime, aNodes, jNodes, aExplored, jExplored);

    _getch();
    closegraph();
    return 0;
}