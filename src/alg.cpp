// Copyright 2021 NNTU-CS
#include  "bst.h"
#include  <iostream>
#include  <fstream>
#include <string>
#include <vector>
#include  <cstdlib>


void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File Error!" << std::endl;
        return;
    }
    std::string word;
    while (!file.eof()) {
        int ch = file.get();
        if (ch == EOF) break;
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            if (ch >= 'A' && ch <= 'Z')
                ch += ('a' - 'A');
            word.push_back(static_cast<char>(ch));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) {
        tree.insert(word);
    }
    file.close();
}
void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int> > all = tree.getAll();
    std::sort(freq.begin(), freq.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    for (const auto& p : freq) {
        std::cout << p.first << " " << p.second << std::endl;
    }
    std::ofstream out("result or freq.txt");
    if (!out) {
        std::cout << "Error Opening result or freq.txt" << std::endl;
        return;
    }
    for (const auto& p : freq) {
        out << p.first << " " << p.second << std::endl;
    }
    out.close();
}
