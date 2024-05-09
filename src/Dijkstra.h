#ifndef DIJKSTRA
#define DIJKSTRA

#include "Grid.h"
#include "Node.h"
#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm> 

using namespace std;

class Dijkstra {
private:

    Grid* grid;
    int heightR, widthC;

    unordered_map<Node*, int> distance; //hash table
    unordered_map<Node*, Node*> previous;

    void initializeSingleSource(Node* startNode) { //setting all distances as inf
        for (int i = 0; i < heightR; ++i) {
            for (int j = 0; j < widthC; ++j) {
                Node* node = grid->getNode(i, j);
                distance[node] = numeric_limits<int>::max();
                previous[node] = nullptr;
            }
        }
        distance[startNode] = 0;
        //cout << distance;
    }

    void relax(Node* u, Node* v) {
        int weight = 1; // Assuming all edges have unit weight
        if (distance[v] > distance[u] + weight) {
            distance[v] = distance[u] + weight;
            previous[v] = u;
        }
        //cout << previous;
    }

    
public:
    // Constructor for Dijkstra's algorithm
    Dijkstra(Grid& grid) {
        this->grid = &grid; //why &??
        this->heightR = grid.getHeight();
        this->widthC = grid.getWidth();
    }

    // Function to implement Dijkstra's algorithm

    void solve() {
        Node* startNode = grid->getStartNode();
        Node* endNode = grid->getEndNode();

        if (!startNode || !endNode) {
            cerr << "Start or end node not found!" << endl;
            return;
        }

        initializeSingleSource(startNode);

        unordered_set<Node*> visited;
        
        priority_queue <pair<int, Node*>, vector< pair<int, Node*> >, greater< pair<int, Node*> > > pq;

        pq.push(make_pair(0, startNode));

        while (!pq.empty()) {
            Node* u = pq.top().second;
            pq.pop();
            if (u->isSame(endNode)) // Early exit if the destination is reached
                break;
            visited.insert(u);
            for (Node* v: grid->getNeighbours(u)) { //why is this throwing an error 
                if (v->isWalkable() == false) {
                    continue;
                }
                if (visited.find(v) == visited.end()) {
                    relax(u, v);
                    pq.push(make_pair(distance[v], v));
                }
            }
        }
      //cout << pq;  
    }
        
    
    // Function to find the minimum path and its weight
    vector<Node*> constructPath() {
        solve();
        Node* startNode = grid->getStartNode();
        Node* endNode = grid->getEndNode();

        //Node* endNode = grid->getEndNode();
        vector<Node*> path;

        if (!endNode) {
            cerr << "End node not found!" << endl;
            return path;
        }

        Node* currentNode = endNode;
        while (currentNode != nullptr) {
            path.push_back(currentNode);
            currentNode = previous[currentNode];
        }
        reverse(path.begin(), path.end());

        cout << "PATH:" << endl;
        // int weight = distance[endNode];
        // if (weight != numeric_limits<int>::max()) {
        //     for (size_t i = 0; i < path.size(); ++i) {
        //         // cout << path[i]->x << " " << path[i]->y;
        //         // if (i < path.size() - 1)
        //         //     cout << " -> ";
        //     }
        //     cout << " (weight: " << weight << ")" << endl;
        // } else {
        //     cerr << "There's no path from " << endl;
        // }

        for (Node* node: path) {
            cout << "r: " << node->x << " c: " << node->y << endl;
        }
        return path;
    }
};

#endif
