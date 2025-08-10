#include "HuffmanTree.h"

HuffmanTree::HuffmanTree() : root(nullptr) {}

HuffmanTree::~HuffmanTree() {
    freeTree(root);
}

void HuffmanTree::freeTree(Node* node) {
    if (node) {
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }
}

void HuffmanTree::build(const std::unordered_map<char, int>& frequencies) {
    if (frequencies.empty()) {
        throw std::invalid_argument("Frequency map is empty. Cannot build Huffman tree.");
    }

    auto cmp = [](Node* a, Node* b) {
        if (a->freq == b->freq) {
            // If both are leaf nodes, break tie by character
            if (!a->left && !a->right && !b->left && !b->right) {
                return a->ch > b->ch; // smaller char gets higher priority
            }
        }
        return a->freq > b->freq; // smaller frequency gets higher priority
    };

    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> pq(cmp);

    for (const auto& pair : frequencies) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    root = pq.top();
    generateCodes(root, "");
}

void HuffmanTree::generateCodes(Node* node, const std::string& code) {
    if (!node) return;

    if (!node->left && !node->right) {
        codes[node->ch] = code;
    }

    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

std::unordered_map<char, std::string> HuffmanTree::getCodes() const {
    if (codes.empty()) {
        throw std::runtime_error("Huffman codes not generated. Build the tree first.");
    }
    return codes;
}

Node* HuffmanTree::getRoot() const {
    return root;
}

std::string HuffmanTree::getCode(char ch) const {
    if (root == nullptr) {
        throw std::runtime_error("Huffman Tree not built.");
    }

    auto codes = getCodes();
    auto it = codes.find(ch);
    if (it == codes.end()) {
        throw std::runtime_error("Character not found in Huffman codes.");
    }
    return it->second;
}

std::string HuffmanTree::decode(const std::string& encodedStr) const {
    if (root == nullptr) {
        throw std::runtime_error("Huffman Tree not built.");
    }

    std::string decoded;
    Node* current = root;
    for (char bit : encodedStr) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        } else {
            throw std::runtime_error("Invalid bit in encoded string.");
        }

        if (!current->left && !current->right) {
            decoded += current->ch;
            current = root;
        }
    }
    return decoded;
}

