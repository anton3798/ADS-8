// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <algorithm>
#include <vector>
#include <utility>

template<typename T>
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
  void insert(Node*& node, const T& key) {
    if (node == nullptr) {
      node = new Node(key);
      return;
    }
    if (key < node->key) {
      insert(node->left, key);
    } else if (key > node->key) {
      insert(node->right, key);
    } else {
      node->count++;
    }
  }
  int depthHelper(Node* node) const {
    if (node == nullptr) return 0;
    int leftDepth = depthHelper(node->left);
    int rightDepth = depthHelper(node->right);
    return 1 + std::max(leftDepth, rightDepth);
  }
  int searchHelper(Node* node, const T& key) const {
    if (node == nullptr) return 0;
    if (key == node->key) return node->count;
    if (key < node->key) return searchHelper(node->left, key);
    return searchHelper(node->right, key);
  }
  void collectNodes(Node* node, std::vector<std::pair<T, int>>& nodes) const {
    if (node == nullptr) return;
    collectNodes(node->left, nodes);
    nodes.push_back({node->key, node->count});
    collectNodes(node->right, nodes);
  }

  void clear(Node* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }
  BST(const BST&);
  BST& operator=(const BST&);

 public:
  BST() : root(nullptr) {}
  ~BST() {
    clear(root);
  }

  void insert(const T& key) {
    insert(root, key);
  }
  int depth() const {
    return depthHelper(root) - 1;
  }
  int search(const T& value) const {
    return searchHelper(root, value);
  }
  std::vector<std::pair<T, int>> getNodesSortedByFrequency() const {
    std::vector<std::pair<T, int>> nodes;
    collectNodes(root, nodes);
    std::sort(nodes.begin(), nodes.end(),
        [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
          return a.second > b.second;
        });
    return nodes;
  }
};

#endif // INCLUDE_BST_H_
