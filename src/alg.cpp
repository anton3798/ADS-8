// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>
#include <vector>
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
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
      if (ch >= 'A' && ch <= 'Z') {
        ch = ch + ('a' - 'A');
      }
      word += ch;
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }
  if (!word.empty()) {
    tree.insert(word);
  }
  file.close();
}
void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> nodes = tree.getNodesSortedByFrequency();
  std::ofstream outfile("result/freq.txt");
  if (!outfile) {
    std::cerr << "Ошибка создания result/freq.txt" << std::endl;
    return;
  }
  for (const auto& node : nodes) {
    std::cout << node.first << ": " << node.second << std::endl;
    outfile << node.first << ": " << node.second << std::endl;
  }
  outfile.close();
}
