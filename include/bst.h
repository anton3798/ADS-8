// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <utility>
#include <vector>

template <typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;
    void insert(Node*& node, const T& value) {
        if (!node) {
            node = new Node(value);
        } else if (value < node->key) {
            insert(node->left, value);
        } else if (value > node->key) {
            insert(node->right, value);
        } else {
            node->count++;
        }
    }

    Node* search(Node* node, const T& value) const {
        if (!node) return nullptr;
        if (value < node->key)
            return search(node->left, value);
        else if (value > node->key)
            return search(node->right, value);
        else
            return node;
    }
    int depth(Node* node) const {
        if (!node) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void traverseInOrder(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (!node) return;
        traverseInOrder(node->left, result);
        result.push_back({ node->key, node->count });
        traverseInOrder(node->right, result);
    }

 public:
    BST() : root(nullptr) {}
    ~BST() {
        clear(root);
    }
    void insert(const T& value) {
        insert(root, value);
    }
    bool search(const T& value) const {
        return search(root, value) != nullptr;
    }
    int getCount(const T& value) const {
        Node* node = search(root, value);
        return node ? node->count : 0;
    }
    int depth() const {
        return depth(root);
    }
    std::vector<std::pair<T, int>> getEntries() const {
        std::vector<std::pair<T, int>> entries;
        traverseInOrder(root, entries);
        return entries;
    }
};

#endif // INCLUDE_BST_H_
