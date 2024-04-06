#include <vector>
#include "Node.h"

class AStar {
private:
    void reconstructPath(Node* node, std::vector<Node*>& path)
    {
        Node* parent = static_cast<Node*>(node->getParent());
        path.push_back(node);
        while(parent != nullptr)
        {
            path.push_back(parent);
            parent = static_cast<Node*>(parent->getParent());
        }
    }

    inline float distanceBetween(Node* n1, Node* n2) const
    {
        return n1->distanceTo(n2);
    }
};