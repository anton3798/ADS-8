// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include  "bst.h"


void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File Error!" << std::endl;
        return;
    }
    std::string word;
    int ch;
    while ((ch = file.get()) != EOF) {
        if (std::isalpha(ch)) {
            word.push_back(static_cast<char>(std::tolower(ch)));
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
    std::vector<std::pair<std::string, int> > freq = tree.getAll();
    std::sort(freq.begin(), freq.end(),
              [](const std::pair<std::string, int>& a,
                 const std::pair<std::string, int>& b) { return a.second > b.second; });
    for (size_t i = 0; i < freq.size(); ++i) {
        std::cout << freq[i].first << " " << freq[i].second << std::endl;
    }
    std::ofstream out("result or freq.txt");
    if (!out) {
        std::cout << "Error Opening result or freq.txt" << std::endl;
        return;
    }
    for (size_t i = 0; i < freq.size(); ++i) {
        out << freq[i].first << " " << freq[i].second << std::endl;
    }
    out.close();
}
