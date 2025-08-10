#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Node.h"
#include "FrequencyAnalyzer.h"
#include "HuffmanTree.h"
#include "HuffmanCompressor.h"
#include <fstream>
#include<cstdlib>

// Test Node class
TEST_CASE("Node stores character and frequency correctly") {
    Node n('x', 42);
    REQUIRE(n.ch == 'x');
    REQUIRE(n.freq == 42);
    REQUIRE(n.left == nullptr);
    REQUIRE(n.right == nullptr);
}

// Test FrequencyAnalyzer with a sample file
TEST_CASE("FrequencyAnalyzer counts characters correctly") {
    // Create a temporary file
    std::ofstream outFile("testfile.txt");
    outFile << "aabbc";
    outFile.close();

    auto freq = FrequencyAnalyzer::analyze("testfile.txt");

    REQUIRE(freq['a'] == 2);
    REQUIRE(freq['b'] == 2);
    REQUIRE(freq['c'] == 1);
    REQUIRE(freq.size() == 3);

    std::remove("testfile.txt");
}

TEST_CASE("FrequencyAnalyzer throws exception for missing file") {
    REQUIRE_THROWS_AS(FrequencyAnalyzer::analyze("nonexistent.txt"), std::runtime_error);
}

// HuffmanTree tests
TEST_CASE("HuffmanTree builds correctly from frequency map", "[HuffmanTree]") {


    std::ofstream outFile("testFile.txt");
    outFile << "aabbc";
    outFile.close();

    auto freqMap = FrequencyAnalyzer::analyze("testFile.txt");

    HuffmanTree tree;
    REQUIRE_NOTHROW(tree.build(freqMap));

    Node* root = tree.getRoot();
    REQUIRE(root != nullptr);
    REQUIRE(root->freq == 5); // total chars

    bool hasA = false, hasB = false, hasC = false;

    std::function<void(Node*)> traverse = [&](Node* node) {
        if (!node) return;
        if (!node->left && !node->right) {
            if (node->ch== 'a') hasA = true;
            if (node->ch== 'b') hasB = true;
            if (node->ch== 'c') hasC = true;
        }
        traverse(node->left);
        traverse(node->right);
    };

    traverse(root);
    REQUIRE(hasA);
    REQUIRE(hasB);
    REQUIRE(hasC);

    std::remove("testFile.txt");
}

// HuffmanCompressor
TEST_CASE("HuffmanCompressor compresses and decompresses correctly", "[HuffmanCompressor]") {
    const std::string inputFile = "original_test.txt";
    const std::string compressedFile = "compressed_test.huf";
    const std::string decompressedFile = "decompressed_test.txt";
    const std::string testData = "aabbcccddddeeeee";

    // Create the original test file
    {
        std::ofstream out(inputFile, std::ios::binary);
        REQUIRE(out.is_open());
        out << testData;
        out.close();
    }

    HuffmanCompressor compressor;

    SECTION("Compression works without throwing") {
        REQUIRE_NOTHROW(compressor.compress(inputFile, compressedFile));
        std::ifstream compressedIn(compressedFile, std::ios::binary);
        REQUIRE(compressedIn.is_open());
    }

    SECTION("Decompression restores original data") {
        compressor.compress(inputFile, compressedFile);
        REQUIRE_NOTHROW(compressor.decompress(compressedFile, decompressedFile));

        std::ifstream decompressedIn(decompressedFile, std::ios::binary);
        REQUIRE(decompressedIn.is_open());
        std::string decompressedData((std::istreambuf_iterator<char>(decompressedIn)),
                                     std::istreambuf_iterator<char>());
        REQUIRE(decompressedData == testData);
    }

    // Cleanup
    std::remove(inputFile.c_str());
    std::remove(compressedFile.c_str());
    std::remove(("MetaData" + compressedFile).c_str());
    std::remove(decompressedFile.c_str());
}