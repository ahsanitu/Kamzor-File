#include "FrequencyAnalyzer.h"
#include <fstream>
#include <stdexcept>

std::unordered_map<char, int> FrequencyAnalyzer::analyze(const std::string& filename) {
    std::unordered_map<char, int> freq;
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Error: Cannot open file '" + filename + "'");

    }

    char ch;
    while (file.get(ch)) {
        freq[ch]++;
    }

    if (file.bad()) {
        throw std::runtime_error("Error: File reading failed for '" + filename + "'");
    }

    file.close();
    return freq;
}
