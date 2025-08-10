/**
* @file main.cpp
 * @brief Entry point for the Huffman Compressor/Decompressor application.
 *
 * This program demonstrates the usage of HuffmanCompressor to compress
 * and decompress files. It reads command-line arguments to determine
 * the mode (compress or decompress), input file, and output file.
 */

#include <iostream>
#include <string>
#include "HuffmanCompressor.h"

/**
 * @brief Application entry point.
 *
 * @param argc Argument count.
 * @param argv Argument values.
 * @return int Exit status code.
 *
 * Usage:
 *   ./huffman_app compress input.txt output.huff
 *   ./huffman_app decompress output.huff restored.txt
 */
int main(int argc, char* argv[]) {
    try {
        if (argc != 4) {
            std::cerr << "Usage:\n"
                      << "  " << argv[0] << " compress <inputFile> <outputFile>\n"
                      << "  " << argv[0] << " decompress <inputFile> <outputFile>\n";
            return 1;
        }

        std::string mode = argv[1];
        std::string inputFile = argv[2];
        std::string outputFile = argv[3];

        HuffmanCompressor compressor;

        if (mode == "compress") {
            compressor.compress(inputFile, outputFile);
            std::cout << "Compression complete. Output file: " << outputFile << "\n";
        }
        else if (mode == "decompress") {
            compressor.decompress(inputFile, outputFile);
            std::cout << "Decompression complete. Output file: " << outputFile << "\n";
        }
        else {
            std::cerr << "Invalid mode: " << mode << "\n";
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
