#include "visualization.h"
#include "utils.h"
#include <easyx.h>
#include <conio.h>

void drawMap(const vector<pair<int, int>>& aPath,
    const vector<pair<int, int>>& jPath,
    double aTime, double jTime,
    int aNodes, int jNodes,
    const vector<pair<int, int>>& aExplored,
    const vector<pair<int, int>>& jExplored) {

    const int cell = 26;
    initgraph(cols * cell, rows * cell + 160);
    setbkcolor(RGB(248, 248, 248));
    cleardevice();

    setfillcolor(RGB(230, 230, 230));
    solidrectangle(0, 0, cols * cell, 100);
    settextcolor(BLACK);
    settextstyle(26, 0, _T("微软雅黑"));
    outtextxy(25, 18, _T("校园道路路径规划系统 - A* vs JPS 性能对比"));

    settextstyle(16, 0, _T("微软雅黑"));
    outtextxy(25, 55, _T("图例：浅蓝区域 = A*搜索空间 | 浅红区域 = JPS搜索空间"));
    outtextxy(25, 75, _T("路径：蓝色粗线 = A*路径 | 红色细线 = JPS路径"));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int x = j * cell, y = i * cell + 100;
            if (grid[i][j] == 1) setfillcolor(RGB(80, 80, 80));
            else setfillcolor(WHITE);
            solidrectangle(x, y, x + cell, y + cell);
            setlinecolor(RGB(220, 220, 220));
            rectangle(x, y, x + cell, y + cell);
        }
    }

    for (const auto& p : aExplored) {
        int x = p.second * cell, y = p.first * cell + 100;
        setfillcolor(RGB(200, 230, 255));
        solidrectangle(x + 1, y + 1, x + cell - 1, y + cell - 1);
    }

    for (const auto& p : jExplored) {
        int x = p.second * cell, y = p.first * cell + 100;
        setfillcolor(RGB(255, 180, 180));
        solidrectangle(x + 4, y + 4, x + cell - 4, y + cell - 4);
    }

    if (!aPath.empty()) {
        setlinecolor(RGB(0, 100, 255));
        setlinestyle(PS_SOLID, 6);
        for (size_t i = 1; i < aPath.size(); i++) {
            line(aPath[i - 1].second * cell + cell / 2,
                aPath[i - 1].first * cell + cell / 2 + 100,
                aPath[i].second * cell + cell / 2,
                aPath[i].first * cell + cell / 2 + 100);
        }
    }

    if (!jPath.empty()) {
        setlinecolor(RGB(255, 0, 0));
        setlinestyle(PS_SOLID, 2);
        for (size_t i = 1; i < jPath.size(); i++) {
            line(jPath[i - 1].second * cell + cell / 2,
                jPath[i - 1].first * cell + cell / 2 + 100,
                jPath[i].second * cell + cell / 2,
                jPath[i].first * cell + cell / 2 + 100);
        }
    }

    setfillcolor(GREEN);
    solidcircle(startY * cell + cell / 2, startX * cell + cell / 2 + 100, cell / 3);
    setfillcolor(RED);
    solidcircle(goalY * cell + cell / 2, goalX * cell + cell / 2 + 100, cell / 3);

    TCHAR buf[256];
    _stprintf_s(buf, _T("A*  算法 >> 耗时: %.3f ms | 展开节点数: %d"), aTime, aNodes);
    outtextxy(25, rows * cell + 105, buf);
    _stprintf_s(buf, _T("JPS 算法 >> 耗时: %.3f ms | 展开节点数: %d (减少 %.1f%%)"),
        jTime, jNodes,
        (aNodes > 0 ? (1.0 - (double)jNodes / aNodes) * 100 : 0));
    outtextxy(25, rows * cell + 130, buf);
}