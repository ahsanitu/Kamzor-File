#include "HuffmanCompressor.h"
#include <fstream>
#include <stdexcept>

void HuffmanCompressor::compress(const std::string& inputFile, const std::string& outputFile) {
    // Step 1: Analyze frequency
    auto freqMap = FrequencyAnalyzer::analyze(inputFile);

    if (freqMap.empty()) {
        throw std::runtime_error("Cannot compress: input file is empty or invalid.");
    }

    // Step 2: Build Huffman tree
    HuffmanTree tree;
    tree.build(freqMap);

    // Step 3: Encode input file
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open file for reading: " + inputFile);
    }

    std::string encodedStr;
    char ch;
    auto codes = tree.getCodes();
    while (in.get(ch)) {
        encodedStr += codes.at(ch);
    }
    in.close();

    // Step 4: Save encoded data
    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + outputFile);
    }
    out << encodedStr;
    out.close();

    // Step 5: Save frequency metadata
    std::string metaFile = "MetaData_" + outputFile;
    saveFrequencyMap(metaFile, freqMap);
}

void HuffmanCompressor::decompress(const std::string& inputFile, const std::string& outputFile) {
    // Step 1: Load frequency metadata
    std::string metaFile = "MetaData_" + inputFile;
    auto freqMap = loadFrequencyMap(metaFile);

    if (freqMap.empty()) {
        throw std::runtime_error("Cannot decompress: frequency map is empty.");
    }

    // Step 2: Rebuild Huffman tree
    HuffmanTree tree;
    tree.build(freqMap);

    // Step 3: Read encoded data
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open file for reading: " + inputFile);
    }
    std::string encodedStr((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    // Step 4: Decode
    std::string decodedStr = tree.decode(encodedStr);

    // Step 5: Save decompressed data
    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + outputFile);
    }
    out << decodedStr;
    out.close();
}

void HuffmanCompressor::saveFrequencyMap(const std::string& metaFile, const std::unordered_map<char, int>& freqMap) {
    std::ofstream out(metaFile, std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open metadata file for writing: " + metaFile);
    }
    for (const auto& pair : freqMap) {
        out << pair.first << " " << pair.second << "\n";
    }
    out.close();
}

std::unordered_map<char, int> HuffmanCompressor::loadFrequencyMap(const std::string& metaFile) {
    std::unordered_map<char, int> freqMap;
    std::ifstream in(metaFile, std::ios::binary);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open metadata file for reading: " + metaFile);
    }
    char ch;
    int freq;
    while (in >> ch >> freq) {
        freqMap[ch] = freq;
    }
    in.close();
    return freqMap;
}
