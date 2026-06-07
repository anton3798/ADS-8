// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия: " << filename << std::endl;
        return;
    }
        std::string word;
    char ch;
    while (file.get(ch)) {
        unsigned char uch = static_cast<unsigned char>(ch);
        if (std::isalpha(uch)) {
            word += std::tolower(uch);
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
    auto entries = tree.getEntries();
    std::sort(entries.begin(), entries.end(),
        [](const auto& a, const auto& b) {
            if (a.second != b.second)
                return a.second > b.second;
            return a.first < b.first;
        });
    for (const auto& p : entries) {
        std::cout << p.first << " : " << p.second << '\n';
    }
    std::ofstream out("result/freq.txt");
    if (!out) {
        return;
    }
    for (const auto& p : entries) {
        out << p.first << " : " << p.second << '\n';
    }
    out.close();
}
