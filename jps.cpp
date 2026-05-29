#include "jps.h"
#include "utils.h"
#include <queue>
#include <algorithm>

// 判断 (x, y) 在方向 (dx, dy) 上是否存在强制邻居
static bool hasForcedNeighbors(int x, int y, int dx, int dy) {
    if (dx != 0 && dy != 0) {
        if (!isWalkable(x - dx, y) && isWalkable(x - dx, y + dy)) return true;
        if (!isWalkable(x, y - dy) && isWalkable(x + dx, y - dy)) return true;
    }
    else if (dx != 0) {
        if (isWalkable(x + dx, y + 1) && !isWalkable(x, y + 1)) return true;
        if (isWalkable(x + dx, y - 1) && !isWalkable(x, y - 1)) return true;
    }
    else if (dy != 0) {
        if (isWalkable(x + 1, y + dy) && !isWalkable(x + 1, y)) return true;
        if (isWalkable(x - 1, y + dy) && !isWalkable(x - 1, y)) return true;
    }
    return false;
}

// 递归沿方向 (dx, dy) 跳跃，直到找到跳点或碰到障碍物
static pair<int, int> jump(int x, int y, int dx, int dy, int gx, int gy) {
    int nx = x + dx, ny = y + dy;
    if (!isWalkable(nx, ny)) return { -1, -1 };

    if (dx != 0 && dy != 0) {
        if (!isWalkable(x, ny) && !isWalkable(nx, y)) return { -1, -1 };
    }

    if (nx == gx && ny == gy) return { nx, ny };
    if (hasForcedNeighbors(nx, ny, dx, dy)) return { nx, ny };

    if (dx != 0 && dy != 0) {
        auto hor = jump(nx, ny, dx, 0, gx, gy);
        auto ver = jump(nx, ny, 0, dy, gx, gy);
        if (hor.first != -1 || ver.first != -1) return { nx, ny };
    }
    return jump(nx, ny, dx, dy, gx, gy);
}

vector<pair<int, int>> jps(int sx, int sy, int gx, int gy,
    int& expandedNodes,
    vector<pair<int, int>>& outExplored) {
    expandedNodes = 0;
    outExplored.clear();

    vector<vector<bool>> closed(rows, vector<bool>(cols, false));
    vector<vector<double>> gScore(rows, vector<double>(cols, 1e9));
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, { -1, -1 }));

    priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
    gScore[sx][sy] = 0.0;
    pq.push({ sx, sy, getDistance(sx, sy, gx, gy) });

    int dirs[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int cx = cur.x, cy = cur.y;

        if (closed[cx][cy]) continue;

        expandedNodes++;
        closed[cx][cy] = true;
        outExplored.push_back({ cx, cy });

        if (cx == gx && cy == gy) {
            vector<pair<int, int>> path;
            int currX = gx, currY = gy;
            while (currX != -1 && currY != -1) {
                path.push_back({ currX, currY });
                auto p = parent[currX][currY];
                currX = p.first; currY = p.second;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto& d : dirs) {
            auto jumpPoint = jump(cx, cy, d[0], d[1], gx, gy);
            if (jumpPoint.first == -1) continue;

            int nx = jumpPoint.first, ny = jumpPoint.second;
            if (closed[nx][ny]) continue;

            double tentG = gScore[cx][cy] + getDistance(cx, cy, nx, ny);

            if (tentG < gScore[nx][ny]) {
                gScore[nx][ny] = tentG;
                parent[nx][ny] = { cx, cy };
                pq.push({ nx, ny, tentG + getDistance(nx, ny, gx, gy) });
            }
        }
    }
    return {};
}