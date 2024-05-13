#ifndef GRID
#define GRID
#include "Node.h"

class Grid {
private:
    int height;
    int width;
    int channels;
    vector<vector<Node*> > nodeMatrix; // 2D array of node pointers
    Node* startNode;
    Node* endNode;

public:
    Grid() : height(0), width(0), channels(0), startNode(nullptr), endNode(nullptr) {}


    Grid(int height, int width) : height(height), width(width) {
        nodeMatrix.resize(height);
        for (int r = 0; r < height; r++) {
            nodeMatrix[r].resize(width);
        }
        for (int r = 0; r < height; ++r) {
            for (int c = 0; c < width; ++c) {
                nodeMatrix[r][c] = new Node(r, c, false);
            }
        }
    }

    Grid(const Grid& other) : height(other.height), width(other.width) {
        nodeMatrix.resize(height);
        for (int r = 0; r < height; ++r) {
            nodeMatrix[r].resize(width);
            for (int c = 0; c < width; ++c) {
                nodeMatrix[r][c] = new Node(*other.nodeMatrix[r][c]);
            }
        }
    }

    ~Grid() {
        for (int r = 0; r < height; ++r) {
            for (int c = 0; c < width; ++c) {
                delete nodeMatrix[r][c];
            }
        }
    }

    int getHeight() {
        return height;
    }

    int getWidth() {
        return width;
    }

    int getChannels() {
        return channels;
    }

    void setStart(Node* node) {
        startNode = node;
    }

    void setEnd(Node* node) {
        endNode = node;
    }

    Node* getStartNode() {
        return startNode;
    }

    Node* getEndNode() {
        return endNode;
    }

    Node* getNode(int r, int c) {
        if (r >= 0 && r < height && c >= 0 && c < width) {
            return nodeMatrix[r][c];
        } else {
            // Handle error: Node coordinates out of bounds
            cout << "Node coordinates out of bounds" << endl;
            return nullptr;
        }
    }

    void populateGrid(unsigned char* img, int channels) {
        this->channels = channels;
        int index = 0;
        for (int r = 0; r < height; ++r) {
            for (int c = 0; c < width; ++c) {
                
                // If pixel is white, set it to walkable, else not walkable
                bool walkable = (img[index] != 0 && img[index + 1] != 0 && img[index + 2] != 0);
                nodeMatrix[r][c]->setWalkable(walkable);

                // If pixel is green, make that the startNode
                if (img[index] == 0 && img[index + 1] == 255 && img[index + 2] == 0) {
                    nodeMatrix[r][c]->setWalkable(true);
                    startNode = nodeMatrix[r][c];
                }

                // If pixel is blue, make that the endNode
                if (img[index] == 0 && img[index + 1] == 0 && img[index + 2] == 255) {
                    nodeMatrix[r][c]->setWalkable(true);
                    endNode = nodeMatrix[r][c];
                }

                index += channels;
            }
        }
    }

    void printGrid() {
        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                if (nodeMatrix[r][c]->isSame(getStartNode())) cout << "S ";
                else if (nodeMatrix[r][c]->isSame(getEndNode())) cout << "E ";
                else cout << nodeMatrix[r][c]->isWalkable() << " ";
            }
        cout << endl;
        }
    }

    vector<Node*> getNeighbours(Node* node) {
        vector<Node*> neighbours;
        int row = node->r;
        int col = node->c;

        // Check top neighbour
        if (row > 0) {
            neighbours.push_back(nodeMatrix[row - 1][col]);
        }

        // Check bottom neighbour
        if (row < height - 1) {
            neighbours.push_back(nodeMatrix[row + 1][col]);
        }

        // Check left neighbour
        if (col > 0) {
            neighbours.push_back(nodeMatrix[row][col - 1]);
        }

        // Check right neighbour
        if (col < width - 1) {
            neighbours.push_back(nodeMatrix[row][col + 1]);
        }

        return neighbours;
    }

};

#endif