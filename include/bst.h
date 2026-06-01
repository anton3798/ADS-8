// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <algorithm>
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
    template<typename Func>
    void forEach(Node* node, Func f) const {
        if (node) {
            forEach(node->left, f);
            f(node->key, node->count);
            forEach(node->right, f);
        }
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
    int depth() const { return depth(root); }
    template<typename Func>
    void forEach(Func f) const {
      forEach(root, f);
    }
};

#endif
