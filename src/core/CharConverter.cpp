#include <iostream>
#include "cstring"
#include "CharConverter.h"

std::vector<std::string> CharConverter::ReadFromBytePtrArray(char** words, int len) {
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

void CharConverter::WriteToBytePtrArray(const std::vector<std::string>& buffer, char** words) {

    for (int i = 0; i < buffer.size(); i++) {
        words[i] = new char [buffer[i].size()];
        strcpy(words[i], buffer[i].c_str());
    }
}