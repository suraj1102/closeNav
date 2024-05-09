#ifndef NODE
#define NODE

class Node {
public:
    int x;
    int y;
    bool walkable;
    Node* parent;

    Node() { parent = nullptr; }
    Node(int x, int y, bool walkable) : x(x), y(y), walkable(walkable) { parent = nullptr; } 

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
        cout << "x: " << x + 1 << " y: " << y + 1 << endl;
        return;
    }

    float distanceTo(Node* node) {
        int x1 = x, x2 = node->x;
        int y1 = y, y2 = node->y;

        float h_dist = x2 - x1;
        float v_dist = y2 - y1;

        return sqrt(h_dist * h_dist + v_dist * v_dist);
    }

    bool operator==(Node* other) {
        return (this->x == other->x && this->y == other->y);
    }

    bool isSame(Node* other) {
        return (this->x == other->x && this->y == other->y);
    }
};

#endif