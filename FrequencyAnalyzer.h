#ifndef FREQUENCY_ANALYZER_H
#define FREQUENCY_ANALYZER_H

#include <unordered_map>
#include <string>

/**
 * @brief Analyzes the frequency of each character in a given file.
 */
class FrequencyAnalyzer {
public:
    /**
     * @brief Analyzes the character frequency in a file.
     *
     * @param filename Path to the file.
     * @return std::unordered_map<char, int> A map containing each character and its frequency.
     * @throws std::runtime_error If the file cannot be opened.
     */
    static std::unordered_map<char, int> analyze(const std::string& filename);
};

#endif
