#ifndef NODE
#define NODE

using namespace std;

class Node {
public:
    int c; // col no. - analogous to x coordinate
    int r; // row no. - analogous to y coordinate
    bool walkable;
    Node* parent;

    Node() { parent = nullptr; walkable = false; }
    Node(int row, int col, bool walkable) : r(row), c(col), walkable(walkable) { parent = nullptr; }

    bool isWalkable() {
        return walkable;
    }

    void setWalkable(bool option) {
        walkable = option;
        return;
    }

    Node* getParent() {
        return parent;
    }

    void printLocation() {
        cout << "row: " << r + 1 << " col: " << c + 1 << endl;
        return;
    }

    float distanceTo(Node* node) {
        int x1 = this->c, x2 = node->c;
        int y1 = this->r, y2 = node->r;

        float h_dist = x2 - x1;
        float v_dist = y2 - y1;

        return sqrt(h_dist * h_dist + v_dist * v_dist);
    }
    
    bool isSame(Node* other) {
        return (this->r == other->r && this->c == other->c);
    }
};

#endif