#include "CharConverter.h"

static std::vector<std::string> ReadFromBytePtrArray(char** words, int len) {
    std::vector<std::string> buffer;
    for (int i = 0; i < len; i++) {
        std::string word;
        for (char* p = words[i]; *p != 0; p++) {
            word += *p;
        }
        buffer.push_back(word);
    }
    return buffer;
}

static void WriteToBytePtrArray(const std::vector<std::string>& buffer, char** words) {
    for (size_t i = 0; i < buffer.size(); i++) {
        char* p = words[i];
        for (char j : buffer[i]) {
            *p++ = static_cast<char>(j);
        }
        *p = 0;
    }
}