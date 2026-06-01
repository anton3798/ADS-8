// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
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
        explicit Node(const T& k) {
          left = nullptr;
          right = nullptr;
          count = 1;
          key = k;
        }
    };
    Node* root;
    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    Node* insert(Node* node, const T& key) {
        if (!node) {
            return new Node(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            node->count++;
        }
        return node;
    }
    bool search(Node* node, const T& key) const {
        if (!node) return false;
        if (key < node->key) return search(node->left, key);
        if (key > node->key) return search(node->right, key);
        return true;
    }
    int depth(Node* node) const {
        if (!node)
          return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }
    void collect(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (!node) return;
    collect(node->left, result);
    result.push_back(std::make_pair(node->key, node->count));
    collect(node->right, result);
}

 public:
    BST() {
      root = nullptr;
    }
    ~BST() {
      destroyTree(root);
    }
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;
    void insert(const T& key) {
      root = insert(root, key);
    }
    bool search(const T& key) const {
      return search(root, key);
    }
    int depth() const {
    return depth(root);
    }
    std::vector<std::pair<T, int>> getAll() const {
    std::vector<std::pair<T, int>> result;
    collect(root, result);
    return result;
    }
};

#endif // INCLUDE_BST_H_
