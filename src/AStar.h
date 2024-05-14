#ifndef AStar_h
#define AStar_h

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits> // for INT_MAX
#include <algorithm> // Add this line for using the reverse function
#include "Node.h"
#include "Grid.h"

using namespace std;


class AStarNode {
public:
    int r; // row no. - analogous to y coordinate
    int c; // col no. - analogous to x coordinate
    bool walkable;
    int cost; int heuristic;
    AStarNode* parent;

    AStarNode() { parent = nullptr; walkable = false; }
    AStarNode(int row, int col, bool walkable, int cost, int heu) : r(row), c(col), walkable(walkable),
    cost(cost), heuristic(heu)
    { parent = nullptr; }

    bool isWalkable() {
        return walkable;
    }

    AStarNode* getParent() {
        return parent;
    }
    
    bool isSame(AStarNode* other) {
        return (this->r == other->r && this->c == other->c);
    }
    // Node == Node -> Better but we're using Node* everywhere
};

// Comparator struct for comparing nodes in the priority queue based on their costs and heuristics
struct CompareNode {
    bool operator()(const AStarNode* lhs, const AStarNode* rhs) const {
        return (lhs->cost + lhs->heuristic) > (rhs->cost + rhs->heuristic);
    }
};

// AStar class implementing the A* algorithm
class AStar {
private:
    Grid* grid; // 2D vector representing the grid
    vector<vector<AStarNode*> > nodes; // 2D vector representing the nodes
    priority_queue<AStarNode*, vector<AStarNode*>, CompareNode> openList; // Priority queue for open
    
    AStarNode* startNode;
    AStarNode* endNode;
    
public:
    // Constructor to initialize the AStar instance with grid and start/end coordinates
    AStar(Grid* grid) {
        this->grid = grid; // Initialize grid
        this->startNode = (AStarNode*)this->grid->getStartNode();
        this->endNode = (AStarNode*)this->grid->getEndNode();
    }
    
    // Function to initialize nodes based on the grid
    void initializeNodes() {
        int gridHeight = grid->getHeight();
        int gridWidth = grid->getWidth();
        nodes.resize(gridHeight, vector<AStarNode*>(gridWidth)); // Resize nodes to match grid size
        for (int i = 0; i < gridHeight; ++i) {
            for (int j = 0; j < gridWidth; ++j) {
                bool walkable = grid->getNode(i, j)->isWalkable();
                nodes[i][j] = new AStarNode(i, j, walkable, INT_MAX, 0); // Initialize each node with default values
            }
        }
    }
    
    // Heuristic function (Manhattan distance) for estimating the cost to reach the goal
    int heuristic(int r, int c) const {
        return abs(r - endNode->r) + abs(c - endNode->c); // Manhattan distance heuristic
    }
    
    vector<AStarNode*> findPath() {
        initializeNodes(); // Initialize nodes
        startNode->cost = 0; // Initialize start node cost
        startNode->heuristic = heuristic(startNode->r, startNode->c); // Calculate heuristic for start node
        openList.push(startNode); // Add start node to open list
        
        vector<AStarNode*> route; // Store the route coordinates
        
        while (!openList.empty()) {
            AStarNode* current = openList.top(); // Get node with lowest total cost (f = g + h)
            openList.pop(); // Remove current node from open list
            
            if (current->isSame(endNode)) { // Reached the end node
                cout << "Path Found!" << endl;
                while (current != nullptr) {
                    route.push_back(current); // Add coordinates to route
                    current = (AStarNode*)(current->parent); // Move to parent node
                }
                reverse(route.begin(), route.end()); // Reverse to get correct order of route
                return route; // Path found, exit function
            }

            static int dx[] = {1, -1, 0, 0}; // Delta x for neighbors
            static int dy[] = {0, 0, 1, -1}; // Delta y for neighbors

            for (int i = 0; i < 4; ++i) {
                int rr = current->r + dx[i]; // Calculate new x coordinate for neighbor
                int cc = current->c + dy[i]; // Calculate new y coordinate for neighbor

                if (grid->getNode(rr, cc)->isWalkable()) { // Check if neighbor coordinates are valid
                    AStarNode* neighbor = nodes[rr][cc]; // Pointer to neighbor node
                    int newCost = current->cost + 1; // Calculate new cost for neighbor node

                    if (newCost < neighbor->cost) { // If new cost is lower than neighbor's current cost
                        neighbor->cost = newCost; // Update neighbor's cost
                        neighbor->heuristic = heuristic(rr, cc); // Update neighbor's heuristic
                        neighbor->parent = (AStarNode*)current; // Set neighbor's parent to current node
                        openList.push(neighbor); // Add neighbor to open list
                    }
                }
            }
        }
        return route;
    }
};


#endif /* AStar_h */