#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    int state;
    Node* parent;
    int action;

    Node(int s, Node* p, int a) {
        state = s;
        parent = p;
        action = a;
    }
};

class stackFrontier {
public:
    vector<Node*> frontier;

    stackFrontier() {}

    void add(Node* node) {
        frontier.push_back(node);
    }

    bool contains_state(int state) {
        for (Node* node : frontier) {
            if (node->state == state) {
                return true;
            }
        }
        return false;
    }

    bool empty() {
        return frontier.empty();
    }

    Node* remove() {
        if (empty()) {
            throw "empty frontier";
        } else {
            Node* node = frontier.back();
            frontier.pop_back();
            return node;
        }
    }
};

int main() {
    // Example usage
    Node* node = new Node(1, nullptr, 2);
    stackFrontier frontier = stackFrontier();
    frontier.add(node);
    cout << frontier.contains_state(1) << endl; // Outputs 1 (true)
    cout << frontier.contains_state(2) << endl; // Outputs 0 (false)
    frontier.remove();
    cout << frontier.empty() << endl; // Outputs 1 (true)
    return 0;
}
