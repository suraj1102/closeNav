/**
 * @file BFS.h
 * @brief Implementation of breadth first search for path finding
*/

#ifndef BFS_
#define BFS_

#include <queue>
#include <vector>
#include <iostream>
#include "Grid.h"

using namespace std;

/// Implementation of Breath First Search on a Grid
/// based system.
/// Inspired by the pseudocode from William Fiest.
class BFS {
private:
    int R, C; // Height, Width
    Grid* m; // Underlying grid
    int sr, sc, er, ec; // Indices of start and end nodes
    queue<int> rq; // Queue that stores the row indices
    queue<int> cq; // Queue that stores the col indices

    int moveCount;
    
    // Exploration layer is analagous to the level or breath BFS is currently at
    int nodesLeftInLayer; // Nodes left to explore in current exploration layer
    int nodesInNextLayer; // Nodes left to explore in next exploration layer

    bool reachedEnd;

    vector<vector<bool> > visited; // 2D matrix inidicating which nodes are visited
    vector<vector<Node*> > parent; // Store parent node for each visited node

    // Direction vectors for finding neighbours
    // Defined at the end of this file
    static int dr[4];
    static int dc[4];

public:
    // Default Constructor
    BFS() {}

    // Parameterized Constructor
    BFS(Grid& grid) {
        m = &grid;
        R = m->getHeight();
        C = m->getWidth();

        sr = m->getStartNode()->r;
        sc = m->getStartNode()->c;

        er = m->getEndNode()->r;
        ec = m->getEndNode()->c;

        moveCount = 0;
        nodesLeftInLayer = 1;
        nodesInNextLayer = 0;
        reachedEnd = false;

        // Initialize visited and parent entries for startNode
        // visited = false (we'll pop it later)
        // parent = NULL (start node)
        visited.assign(R, vector<bool>(C, false));
        parent.assign(R, vector<Node*>(C, nullptr));

    }

    
    /// Checks neighbours of node at r, c and pushes their indices to rq and cq
    /// - Parameters:
    ///   - r: row index of node
    ///   - c: col index of node
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

    
    /// Run the algorithm
    int solve() {
        rq.push(sr);
        cq.push(sc);
        visited[sr][sc] = true;

        while (rq.size() > 0)
        {
            int r = rq.front();
            int c = cq.front();
            rq.pop(); cq.pop();

            Node* currentNode = m->getNode(c, r);
            Node* endNode = m->getEndNode();
            if (currentNode->r == endNode->r && currentNode->c == endNode->c) {
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

    /// Function to reconstruct path from end node to start node
    vector<Node*> reconstructPath() {
        vector<Node*> path;
        Node* currentNode = m->getEndNode();

        while (currentNode != nullptr) {
            path.push_back(currentNode);
            currentNode = parent[currentNode->r][currentNode->c]; // Move to parent node
        }

        reverse(path.begin(), path.end()); // Reverse the path to get from start to end
        return path;
    }

    
    /// Print the reconstructed path by calling reconstructPath()
    void printReconstructedPath() {
        vector<Node*> path = reconstructPath();

        if (path.empty()) {
            cout << "No path found." << endl;
            return;
        }

        cout << "Start: " << sr << ", " << sc << endl;
        for (size_t i = 1; i < path.size() - 1; ++i) {
            cout << path[i]->r << ", " << path[i]->c << endl;
        }
        cout << "End: " << er << ", " << ec << endl;
    }
};

int BFS::dr[4] = {-1, 1, 0, 0};
int BFS::dc[4] = {0, 0, 1, -1};

#endif