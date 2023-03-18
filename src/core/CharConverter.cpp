#include <iostream>
#include "cstring"
#include "CharConverter.h"

std::vector<std::string> CharConverter::read_from_ptr(char** words, int len) {
    std::vector<std::string> buffer;
    for (int i = 0; i < len; i++) {
        std::string word(words[i], strlen(words[i]));
        buffer.push_back(word);
    }
    return buffer;
}

void CharConverter::write_to_byte(const std::vector<std::string>& buffer, char** words) {
    //std::cout <<buffer.size()<<std::endl;
    for (int i = 0; i < buffer.size(); i++) {
        words[i] = new char [buffer[i].size() + 1];
        strcpy(words[i], buffer[i].c_str());
    }
}