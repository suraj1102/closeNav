#ifndef BFS_
#define BFS_

#include <queue>
#include <vector>
#include <iostream>
#include "Grid.h"

using namespace std;

class BFS {
private:
    int R, C;
    Grid m;
    int sr, sc, er, ec;
    queue<int> rq;
    queue<int> cq;

    int moveCount;
    int nodesLeftInLayer;
    int nodesInNextLayer;

    bool reachedEnd;

    vector<vector<bool> > visited;

    static int dr[4];
    static int dc[4];

public:
    BFS() {}

    BFS(Grid grid) {
        m = grid;
        R = m.getHeight();
        C = m.getWidth();   

        sr = grid.getStartNode()->x;
        sc = grid.getStartNode()->y;

        er = grid.getEndNode()->x;
        ec = grid.getEndNode()->y;

        moveCount = 0;
        nodesLeftInLayer = 1;
        nodesInNextLayer = 0;
        reachedEnd = false;

        visited.assign(R, vector<bool>(C, false));
    }

    void exploreNeighbours(int r, int c) {
        for (int i = 0; i < 4; i++) {
            int rr = r + dr[i];
            int cc = c + dc[i];

            if (rr < 0 || cc < 0) { continue; }
            if (rr >= R || cc >= C) { continue; }

            if (visited[rr][cc]) { continue; }
            if (m[rr][cc].walkable == false) { continue; }

            rq.push(rr);
            cq.push(cc);
            visited[rr][cc] = true;
            nodesInNextLayer++;
        }
    }

    int solve() {
        rq.push(sr);
        cq.push(sc);
        visited[sr][sc] = true;

        while (rq.size() > 0)
        {
            int r = rq.front();
            int c = cq.front();
            rq.pop(); cq.pop();

            if (&m[r][c] == m.getEndNode()) {
                reachedEnd = true;
                break;
            }

            exploreNeighbours(r, c);
            nodesLeftInLayer--;
            if (nodesLeftInLayer == 0) {
                nodesLeftInLayer = nodesInNextLayer;
                nodesInNextLayer = 0;
                moveCount++;
            }
        }
        
        if (reachedEnd) {
            return moveCount;
        }

        return -1;
    }
};

int BFS::dr[4] = {-1, 1, 0, 0};
int BFS::dc[4] = {0, 0, 1, -1};

#endif