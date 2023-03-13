//
// Created by AORUS on 2023/3/11.
//
#include <ArgParser.h>
#include <Core.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#define bufferSize 1024
#define myIsalpha(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define myTolower(c) (c <= 'Z' ? (c + 0x20) : (c))
#define maxWordsNum 10000

int get_word_from_file(std::string input_file_name, char *words[]) {
    FILE *input_file = fopen(input_file_name.c_str(), "r");
    if (input_file == nullptr) {
        fprintf(stderr, "No such file %s", input_file_name.c_str());
    }
    bool is_word_start = true;
    int word_length = 0;
    char word[bufferSize];
    char c;
    std::vector<std::string> words_vector;
    while ((c = (char) fgetc(input_file)) != EOF) {
        if (is_word_start) {
            if (myIsalpha(c)) {
                word[word_length++] = myTolower(c);
                is_word_start = false;
            }
        } else {
            if (myIsalpha(c)) {
                word[word_length++] = myTolower(c);
            } else {
                word[word_length] = '\0';
                words_vector.emplace_back(word); // 减少一次构造....
                is_word_start = true;
                word_length = 0;
            }
        }
    }

    for (int i = 0; i < words_vector.size(); i++) {
        words[i] = new char[words_vector[i].length() + 1];
        strcpy(words[i], words_vector[i].c_str());
    }

    return words_vector.size();
}

int get_word_from_file_v2(std::string input_file_name, char *words[]) {
    using namespace std;
    ifstream file(input_file_name);
    string line;
    vector<string> words_vector;

    while (getline(file, line)) {
        stringstream ss(line);

    }
    return 0;
}

int main(int argc, char *argv[]) {
    ArgParser parser(argc, argv, "nwch:t:j:r");
    char head = 0, tail = 0, disallowed_head = 0, function = 0;
    bool enable_loop;
    std::string input_file_name;

    ArgParser::parse_arg(parser, head, tail, disallowed_head, enable_loop, function, input_file_name);
    std::cout << "-h " << head << std::endl;
    std::cout << "-t " << tail << std::endl;
    std::cout << "-j " << disallowed_head << std::endl;
    std::cout << "-r " << enable_loop << std::endl;
    std::cout << "function: " << function << std::endl;
    std::cout << "input_file_name: " << input_file_name << std::endl;
    char **words = new char *[maxWordsNum];
    int word_num = get_word_from_file(input_file_name, words);
    for (int i = 0; i < word_num; ++i) {
        std::cout << words[i] << std::endl;
    }
    printf("%d\n", Core::gen_chains_all(nullptr, 10, nullptr));
}