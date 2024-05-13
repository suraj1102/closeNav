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

/// Class implementing the Dijkstra Algorithm for pathfinding
class Dijkstra {
private:

    // Store grid and height and width of grid
    Grid* grid;
    int heightR, widthC;
    
    // Hash Tables which keep track of distance and previous node
    unordered_map<Node*, int> distance;
    unordered_map<Node*, Node*> previous;
    
    
    /// Initialize Distances as infinity and previous as NULL
    /// - Parameter startNode: start node of the grid
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

    
    /// Updates distance of node v from node u
    /// - Parameters:
    ///   - u: current node
    ///   - v: u's neighbour whose distance and prev we want to compute
    void relax(Node* u, Node* v) {
        int weight = 1; // Assuming all edges have unit weight
        if (distance[v] > distance[u] + weight) {
            distance[v] = distance[u] + weight;
            previous[v] = u;
        }
    }

    
public:
    
    // Constructor
    Dijkstra(Grid& grid) {
        this->grid = &grid; //why & - becuase grid* is a pointer
        this->heightR = grid.getHeight();
        this->widthC = grid.getWidth();
    }
    
    /// Function to run Dijkstra's algorithm
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
            for (Node* v: grid->getNeighbours(u)) {
                if (v->isWalkable() == false) {
                    continue;
                }
                if (visited.find(v) == visited.end()) {
                    relax(u, v);
                    pq.push(make_pair(distance[v], v));
                }
            }
        }
    }
        
    
    
    /// Reconstruct the path using the previous map
    vector<Node*> constructPath() {
        solve();
    
        Node* endNode = grid->getEndNode();

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

        for (Node* node: path) {
            cout << "r: " << node->r << " c: " << node->c << endl;
        }
        return path;
    }
};

#endif
