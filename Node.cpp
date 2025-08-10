#include"Node.h"

Node::Node(){
    left = nullptr;
    right = nullptr;
}

Node::Node(char c, int f){
    ch = c;
    freq = f;
    left = nullptr;
    right = nullptr;
}
