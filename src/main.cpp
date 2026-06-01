// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <string>

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> tree;
    makeTree(tree, "src/war_peace.txt");
    std::cout << "Tree depth: " << tree.depth() << std::endl;
    std::cout << "Word 'war' is " << (tree.search("war") ? "" : "not ") << "found.\n\n";
    printFreq(tree);
    return 0;
}
