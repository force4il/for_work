#include "tree.h"

void BinaryTree::push(int value) {
    if (root == nullptr) {
        root = new Node(value);
        return;
    }
    
    Node* cur = root;
    while (true) {
        if (value == cur->data) {
            break;  //значение уже есть
        }
    
        bool left_node = (value < cur->data);
        Node*& child = left_node ? cur->left : cur->right;
        
        if (child == nullptr) {
            child = new Node(value);
            break;
        }
        
        cur = child;
    }
}
    
void BinaryTree::remove(Node* parent, Node* node) {
    Node* child = node->left ? node->left : node->right;
    
    if (!parent) {
        root = child;
    } else if (parent->left == node) {
        parent->left = child;
    } else {
        parent->right = child;
    }
    
    delete node;
}

void BinaryTree::pop(int value) {
    if (!root) {
        cout << "\nОшибка удаления. Пустое дерево" << endl;
        return;
    }

    Node* parent = nullptr;
    Node* cur = root;
        
    while (cur && cur->data != value) {
        parent = cur;
        if (value < cur->data) cur = cur->left;
        else cur = cur->right;
    }
        
    if (!cur) {
        cout << "\nЗначение для удаления не найдено" << endl;
        return;
    }
        
    if (!cur->left || !cur->right) {
        remove(parent, cur);
    } else {  
        // 2 потомка
        Node* min_p = cur;
        Node* min_node = cur->right;
        while (min_node->left) {
            min_p = min_node;
            min_node = min_node->left;
        }
        
        cur->data = min_node->data;
        
        remove(min_p, min_node);
    }
}

void BinaryTree::print(Node* node) {
    if (node == nullptr) return;

    BinaryTree::print(node->left);
    cout << node->data << " ";
    BinaryTree::print(node->right);
}

void BinaryTree::clear(Node* node) {
    if (!node) return;

    clear(node->left);
    clear(node->right);
    
    delete node;
}