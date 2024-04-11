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
        for (int i = 0; i < height; i++) {
            nodeMatrix[i].resize(width);
        }
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                nodeMatrix[i][j] = new Node(i, j, false);
            }
        }
    }

    Grid(const Grid& other) : height(other.height), width(other.width) {
        nodeMatrix.resize(height);
        for (int i = 0; i < height; ++i) {
            nodeMatrix[i].resize(width);
            for (int j = 0; j < width; ++j) {
                nodeMatrix[i][j] = new Node(*other.nodeMatrix[i][j]);
            }
        }
    }

    ~Grid() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                delete nodeMatrix[i][j];
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

    Node* getNode(int i, int j) {
        if (i >= 0 && i < height && j >= 0 && j < width) {
            return nodeMatrix[i][j];
        } else {
            // Handle error: Node coordinates out of bounds
            cout << "Node coordinates out of bounds" << endl;
            return nullptr;
        }
    }

    void populateGrid(unsigned char* img, int channels) {
        this->channels = channels;
        int index = 0;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                
                // If pixel is white, set it to walkable, else not walkable
                bool walkable = (img[index] != 0 && img[index + 1] != 0 && img[index + 2] != 0);
                nodeMatrix[i][j]->setWalkable(walkable);

                // If pixel is green, make that the startNode
                if (img[index] == 0 && img[index + 1] == 255 && img[index + 2] == 0) {
                    nodeMatrix[i][j]->setWalkable(true);
                    startNode = nodeMatrix[i][j];
                }

                // If pixel is blue, make that the endNode
                if (img[index] == 0 && img[index + 1] == 0 && img[index + 2] == 255) {
                    nodeMatrix[i][j]->setWalkable(true);
                    endNode = nodeMatrix[i][j];
                }

                index += channels;
            }
        }
    }

    void printGrid() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << nodeMatrix[i][j]->isWalkable() << " ";
            }
        cout << endl;
        }
    }

};

#endif