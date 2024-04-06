#ifndef GRID
#define GRID

class Grid {
private:
    int height;
    int width;
    Node*** grid; // 2D array of node pointers
    Node* startNode;
    Node* endNode;

public:
    Grid() {}

    Grid(int height, int width) : height(height), width(width) {
        grid = new Node**[height];
        for (int i = 0; i < height; ++i) {
            grid[i] = new Node*[width];
            for (int j = 0; j < width; ++j) {
                grid[i][j] = new Node(i , j, false); 
            }
        }
    }

    ~Grid() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                delete grid[i][j];
            }
            delete[] grid[i];
        }
        delete[] grid;
    }

    int getHeight() {
        return height;
    }

    int getWidth() {
        return width;
    }

    void populateGrid(unsigned char* img, int channels) {
        int index = 0;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                
                // If pixel is white, set it to walkable, else not walkable
                bool walkable = (img[index] != 0 && img[index + 1] != 0 && img[index + 2] != 0);
                grid[i][j]->setWalkable(walkable);

                // If pixel is green, make that the startNode
                if (img[index] == 0 && img[index + 1] == 255 && img[index + 2] == 0) {
                    grid[i][j]->setWalkable(true);
                    startNode = grid[i][j];
                }

                // If pixel is blue, make that the endNode
                if (img[index] == 0 && img[index + 1] == 0 && img[index + 2] == 255) {
                    grid[i][j]->setWalkable(true);
                    endNode = grid[i][j];
                }                

                index += channels;
            }
        }
    }

    void printGrid() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << grid[i][j]->isWalkable() << " ";
            }
        cout << endl;
        }
    }

    void setStart(Node* node) {
        startNode = node;
    }

    void setEnd(Node* node) {
        endNode = node;
    }

    Node* operator[](int index) {
        if (index >= 0 && index < height) {
            return *grid[index];
        } else {
            return nullptr;
        }
    }

    Node* getStartNode() {
        return startNode;
    }

    Node* getEndNode() {
        return endNode;
    }

};

#endif