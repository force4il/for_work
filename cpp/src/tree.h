#ifndef TREE
#define TREE
#include <iostream>

using std::cout;
using std::endl;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
    Node* root {nullptr};

    void clear(Node* node);
    void remove(Node*, Node*);

public:
    BinaryTree() : root(nullptr) {}
    
    ~BinaryTree() {
        clear(root);
    }

    void push(int);
    void pop(int);
    void print(Node*);

    Node* get_root() const {
        return root;
    }
};

#endif