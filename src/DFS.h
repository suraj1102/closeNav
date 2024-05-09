/**
 * @file BFS.h
 * @brief Implementation of breadth first search for path finding
*/

#ifndef DFS_
#define DFS_

#include <stack>
#include <vector>
#include <iostream>
#include "Grid.h"

using namespace std;

class BFS {
private:
    int R, C;
    Grid* m;
    int sr, sc, er, ec;
    stack<int> rq;
    stack<int> cq;

    int moveCount;
    int nodesLeftInLayer;
    int nodesInNextLayer;

    bool reachedEnd;

    vector<vector<bool> > visited; // 2D matrix inidicating which nodes are visited
    vector<vector<Node*> > parent; // Store parent node for each visited node

    // Direction vectors for finding neighbours
    // Defined at the end of this file
    static int dr[4]; 
    static int dc[4];

public:
    BFS() {}

    BFS(Grid& grid) {
        m = &grid;
        R = m->getHeight();
        C = m->getWidth();   

        sr = m->getStartNode()->x;
        sc = m->getStartNode()->y;

        er = m->getEndNode()->x;
        ec = m->getEndNode()->y;

        moveCount = 0;
        nodesLeftInLayer = 1;
        nodesInNextLayer = 0;
        reachedEnd = false;

        visited.assign(R, vector<bool>(C, false));
        parent.assign(R, vector<Node*>(C, nullptr)); // Initialize parent vector

    }

    void exploreNeighbours(int r, int c) {
        for (int i = 0; i < 4; i++) {
            int rr = r + dr[i];
            int cc = c + dc[i];

            if (rr < 0 || cc < 0) { continue; }
            if (rr >= R || cc >= C) { continue; }

            if (visited[rr][cc]) { continue; }
            if (m->getNode(rr, cc)->walkable == false) { continue; }

            rq.push(rr);
            cq.push(cc);
            visited[rr][cc] = true;
            parent[rr][cc] = m->getNode(r, c); // Set parent of the next node
            nodesInNextLayer++;
        }
    }

    int solve() {
        rq.push(sr);
        cq.push(sc);
        visited[sr][sc] = true;

        while (rq.size() > 0)
        {
            int r = rq.top();
            int c = cq.top();
            rq.pop(); cq.pop();

            Node* currentNode = m->getNode(r, c);
            Node* endNode = m->getEndNode();
            if (currentNode->x == endNode->x && currentNode->y == endNode->y) {
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

    // Function to reconstruct path from end node to start node
    vector<Node*> reconstructPath() {
        vector<Node*> path;
        Node* currentNode = m->getEndNode();

        while (currentNode != nullptr) {
            path.push_back(currentNode);
            currentNode = parent[currentNode->x][currentNode->y]; // Move to parent node
        }

        reverse(path.begin(), path.end()); // Reverse the path to get from start to end
        return path;
    }

    void printReconstructedPath() {
        vector<Node*> path = reconstructPath();

        if (path.empty()) {
            cout << "No path found." << endl;
            return;
        }

        cout << "Start: " << sr << ", " << sc << endl;
        for (size_t i = 1; i < path.size() - 1; ++i) {
            cout << path[i]->x << ", " << path[i]->y << endl;
        }
        cout << "End: " << er << ", " << ec << endl;
    }
};

int BFS::dr[4] = {-1, 1, 0, 0};
int BFS::dc[4] = {0, 0, 1, -1};

#endif