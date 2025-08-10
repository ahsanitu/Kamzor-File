#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <queue>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "Node.h"

/**
 * @class HuffmanTree
 * @brief Builds and manages a Huffman tree for encoding and decoding.
 */
class HuffmanTree {
private:
    Node* root; ///< Root node of the Huffman tree
    std::unordered_map<char, std::string> codes; ///< Character to binary code mapping

    /**
     * @brief Recursively generates Huffman codes from the tree.
     * @param node Current node in traversal.
     * @param code Current binary code path.
     */
    void generateCodes(Node* node, const std::string& code);

    /**
     * @brief Frees memory allocated for the tree.
     * @param node Current node to delete.
     */
    void freeTree(Node* node);

public:
    /**
     * @brief Constructor initializes root to nullptr.
     */
    HuffmanTree();

    /**
     * @brief Destructor frees all dynamically allocated nodes.
     */
    ~HuffmanTree();

    /**
     * @brief Builds the Huffman tree from a frequency map.
     * @param frequencies Map of characters to their frequencies.
     * @throw std::invalid_argument If the frequency map is empty.
     */
    void build(const std::unordered_map<char, int>& frequencies);

    /**
     * @brief Gets the generated Huffman codes.
     * @return Map of characters to binary codes.
     * @throw std::runtime_error If codes are not generated.
     */
    std::unordered_map<char, std::string> getCodes() const;

    /**
     * @brief Gets the root node of the Huffman tree.
     * @return Pointer to root node.
     */
    Node* getRoot() const;

    /**
 * @brief Get the Huffman code for a single character.
 * @param ch The character whose code is required.
 * @return std::string The Huffman code for the character.
 * @throws std::runtime_error if codes have not been generated or character not found.
 */
    std::string getCode(char ch) const;

    /**
     * @brief Decode a bitstring using the Huffman Tree.
     * @param encodedStr The bitstring to decode.
     * @return Decoded text.
     */
    std::string decode(const std::string& encodedStr) const;

};

#endif // HUFFMANTREE_H
