//
// Created by AORUS on 2023/3/11.
//
#include <ArgParser.h>
#include <Core.h>
#include <cstdio>
#define buffer_size 100000

using namespace std;

int get_words_from_line(int idx, const char* buf, char *words[]) {
    bool is_start = true;
    char word[buffer_size];
    int length = 0;
    int word_num = 0;
    for (int i = 0; buf[i] != '\0'; i++) {
        if (is_start) {
            if (isalpha(buf[i])) {
                word[length++] = (char) tolower(buf[i]);
                is_start = false;
            }
        } else {
            if (isalpha(buf[i])) {
                word[length++] = (char) tolower(buf[i]);
            } else {
                is_start = true;

            }
        }
    }
}

int get_words_from_file(const char *input_file_name, char *words[]) {
    FILE *input_file = fopen(input_file_name, "r");
    if (input_file != nullptr) {
        int idx = 0;
        char buf[buffer_size] = {0};
        while (fscanf(input_file, "%s", buf) != EOF) {
            idx += get_words_from_line(idx, buf, words);
        }
    } else {
        fprintf(stderr, "Count not find file %s", input_file_name);
    }
}

int main(int argc, char *argv[]) {
    return 0;
}