#include <iostream>
#include <vector>
#include <unordered_set>

class Node {
public:
    Node(int state, Node* parent = nullptr, int action = -1, int path_cost = 0)
        : state(state), parent(parent), action(action), path_cost(path_cost) {}
    int state;
    Node* parent;
    int action;
    int path_cost;

    std::vector<Node*> expand(Problem problem);
    Node* child_node(Problem problem, int action);
    std::vector<int> solution();
    std::vector<Node*> path();
};

class Problem {
public:
    int initial;
    int goal;
    // Define other problem-specific methods here.
};

std::vector<Node*> Node::expand(Problem problem) {
    std::vector<Node*> children;
    for (int action : problem.actions(state)) {
        Node* child = child_node(problem, action);
        children.push_back(child);
    }
    return children;
}

Node* Node::child_node(Problem problem, int action) {
    int next_state = problem.result(state, action);
    Node* child = new Node(next_state, this, action, path_cost + problem.step_cost(state, action));
    return child;
}

std::vector<int> Node::solution() {
    std::vector<int> actions;
    for (Node* node : path()) {
        if (node->action != -1) {
            actions.push_back(node->action);
        }
    }
    return actions;
}

std::vector<Node*> Node::path() {
    std::vector<Node*> path_back;
    Node* node = this;
    while (node != nullptr) {
        path_back.push_back(node);
        node = node->parent;
    }
    std::vector<Node*> path;
    for (auto it = path_back.rbegin(); it != path_back.rend(); it++) {
        path.push_back(*it);
    }
    return path;
}

Node* depth_first_search(Problem problem) {
    std::vector<Node*> frontier;
    frontier.push_back(new Node(problem.initial));
    std::unordered_set<int> explored;
    while (!frontier.empty()) {
        Node* node = frontier.back();
        frontier.pop_back();
        if (node->state == problem.goal) {
            return node;
        }
        explored.insert(node->state);
        for (Node* child : node->expand(problem)) {
            if (explored.count(child->state) == 0) {
                bool in_frontier = false;
                for (Node* n : frontier) {
                    if (n->state == child->state) {
                        in_frontier = true;
                        break;
                    }
                }
                if (!in_frontier) {
                    frontier.push_back(child);
                }
            }
        }
    }
    return nullptr;
}
