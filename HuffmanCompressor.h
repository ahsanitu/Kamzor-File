#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H

#include <string>
#include <unordered_map>
#include "ICompressor.h"
#include "FrequencyAnalyzer.h"
#include "HuffmanTree.h"

/**
 * @brief HuffmanCompressor is responsible for managing the compression
 *        and decompression process using Huffman coding.
 */
class HuffmanCompressor : public ICompressor {
public:
    /**
     * @brief Compresses a file using Huffman coding and stores frequency metadata.
     * @param inputFile Path to the input file.
     * @param outputFile Path to store the compressed file.
     */
    void compress(const std::string& inputFile, const std::string& outputFile) override;

    /**
     * @brief Decompresses a file using Huffman coding and frequency metadata.
     * @param inputFile Path to the compressed file.
     * @param outputFile Path to store the decompressed file.
     */
    void decompress(const std::string& inputFile, const std::string& outputFile) override;

private:
    void saveFrequencyMap(const std::string& metaFile, const std::unordered_map<char, int>& freqMap);
    std::unordered_map<char, int> loadFrequencyMap(const std::string& metaFile);
};

#endif // HUFFMAN_COMPRESSOR_H
