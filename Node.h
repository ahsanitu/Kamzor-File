#ifndef NODE_H
#define NODE_H


class Node {
public:
  char ch;
  int freq;
  Node* left;
  Node* right;
  Node(){
    left = nullptr;
    right = nullptr;
  }
  Node(char c, int f){
    ch = c;
    freq = f;
  }
};

#endif //NODE_H
