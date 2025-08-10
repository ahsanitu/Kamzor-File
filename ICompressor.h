#ifndef ICOMPRESSOR_H
#define ICOMPRESSOR_H

#include <string>
#include <stdexcept>

/**
 * @class ICompressor
 * @brief Abstract interface class for compression and decompression algorithms.
 *
 * This interface defines the required methods for any compression class.
 * Classes inheriting from ICompressor must implement both compression
 * and decompression functions.
 */
class ICompressor {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~ICompressor() = default;

    /**
     * @brief Compresses the input file and writes the compressed output.
     *
     * @param inputFile Path to the file to be compressed.
     * @param outputFile Path where the compressed file will be saved.
     * @throws std::invalid_argument If file paths are empty.
     * @throws std::runtime_error On compression failure.
     */
    virtual void compress(const std::string& inputFile, const std::string& outputFile) = 0;

    /**
     * @brief Decompresses the input file and writes the decompressed output.
     *
     * @param inputFile Path to the compressed file.
     * @param outputFile Path where the decompressed file will be saved.
     * @throws std::invalid_argument If file paths are empty.
     * @throws std::runtime_error On decompression failure.
     */
    virtual void decompress(const std::string& inputFile, const std::string& outputFile) = 0;
};

#endif // ICOMPRESSOR_H
