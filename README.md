# Huffman File Compressor & Decompressor

## Overview
This project implements a Huffman coding based file compressor and decompressor in C++. It uses object-oriented principles including inheritance and exception handling to provide a modular and extendable design.

---

## Features
- Compress any file using Huffman encoding.
- Decompress files compressed by this tool.
- Saves and loads frequency metadata for accurate decompression.
- Command line interface for easy usage.
- Unit tests using Catch2 framework to ensure correctness.

---

## Project Structure
- `Node.cpp/h`: Defines the tree node used in Huffman coding.
- `FrequencyAnalyzer.cpp/h`: Analyzes frequency of characters in a file.
- `HuffmanTree.cpp/h`: Builds the Huffman tree and encodes/decodes data.
- `HuffmanCompressor.cpp/h`: Manager class implementing compress and decompress functions.
- `main.cpp`: CLI application to compress and decompress files.
- `test.cpp`: Unit tests validating core functionality.
- `Makefile`: Build instructions for the project.

---

## Requirements
- C++17 compatible compiler (e.g., `g++` 7+)
- Catch2 testing framework header (`catch.hpp`) included in the project directory.

---

## Build Instructions
Run the following commands in your terminal:

```bash
make         # Builds both the CLI app and the test binary
make run_test  # Runs all unit tests
make run_main ARGS="compress input.txt output.huff"   # Compress a file
make run_main ARGS="decompress output.huff restored.txt"  # Decompress a file
make clean    # Remove all build artifacts
