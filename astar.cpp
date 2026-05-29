#include "astar.h"
#include "utils.h"
#include <queue>
#include <algorithm>

vector<pair<int, int>> aStar(int sx, int sy, int gx, int gy,
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

    int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

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

        for (int i = 0; i < 8; i++) {
            int nx = cx + dx[i], ny = cy + dy[i];

            if (!isWalkable(nx, ny) || closed[nx][ny]) continue;

            if (dx[i] != 0 && dy[i] != 0) {
                if (!isWalkable(cx, ny) && !isWalkable(nx, cy)) continue;
            }

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