#ifndef NODE_H
#define NODE_H

/**
 * @brief Analyzes the frequency of each character in a given file.
 */
class Node {
public:
  char ch;
  int freq;
  Node* left;
  Node* right;
  Node();
  /**
 * @brief Analyzes the character frequency in a file.
 *
 * @param filename Path to the file.
 * @return std::unordered_map<char, int> A map containing each character and its frequency.
 * @throws std::runtime_error If the file cannot be opened.
 */
  Node(char c, int f);
};

#endif //NODE_H
