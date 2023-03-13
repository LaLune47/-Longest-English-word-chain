//
// Created by AORUS on 2023/3/8.
//

#include "ArgParser.h"
#include "Core.h"
#define GEN_CHAINS_ALL 1
#define GEN_CHAIN_WORD 2
#define GEN_CHAIN_CHAR 3

using std::vector;
using std::string;

ArgParser::ArgParser(int argc, char **argv, char *pattern):
options(vector<int>(128, -1)), argv_index(0), argc(argc) {
    for (int i = 0; i < argc; i++) {
        this->argv.push_back(argv[i]);
    }
    for (char *c = pattern; *c; c++) {
        if (std::isalpha(*c)) {
            options[*c] = 0; // 无需向后读入
            if (*(c + 1) == ':') { // 后一位为参数
                options[*c] = 1;
                if (*(c + 2) == ':') { // 后两位为参数
                    options[*c] = 2;
                    c++;
                }
                c++;
            }
        } else {
            fprintf(stderr, "Wrong option pattern.\n");
            exit(-1);
        }
    }
}

int ArgParser::next_arg() {
    argv_index++;

    // end
    if (argv_index == argc) {
        return 0;
    }

    // 参数
    if (argv[argv_index][0] == '-') {
        char c = argv[argv_index][1];
        if (std::isalpha(c)) {
            if (options[c] == 0) {
                param = ""; // 无参数
                return c;
            }
            if (options[c] == 1) {
                if (argv[argv_index][2] == 0) {
                    argv_index++;
                    if (argv_index == argc) {
                        fprintf(stderr, "Miss option for -%c.\n", c);
                        return -1;
                    }
                    param = string(argv[argv_index]);
                } else {
                    param = string(argv[argv_index] + 2);
                }
                return c;
            }
        }
    }

    // 单词
    param = string(argv[argv_index]);
    return 1;
}

bool check_duplicate(char data) {
    return data == 0;
}

void read_file() {}

void ArgParser::parse_arg(ArgParser &parser, char &head, char &tail, char &disallowed_head, bool &enable_loop,
                          char &function, string &input_file) {
    int arg;
    while ((arg = parser.next_arg()) != 0) {
        if (arg == -1) {
            exit(-1);
        } else if (arg == 1) { // 读文件名
            input_file = parser.param;
        } else {
            switch (arg) {
                case 'n':
                case 'w':
                case 'c':
                    if (!check_duplicate(function)) {
                        fprintf(stderr, "Duplicate main function for %c %c", arg, function);
                    }
                    function = (char) arg;
                    break;
                case 'h':
                    if (!check_duplicate(head)) {
                        fprintf(stderr, "Duplicate value of -%c for new: %s old: %c", arg, parser.param.c_str(), head);
                    }
                    head = parser.param[0];
                    if (!std::isalpha(head)) {
                        fprintf(stderr, "Error value of -%c must be alpha", arg);
                    }
                    head = std::tolower(head);
                    break;
                case 't':
                    if (!check_duplicate(tail)) {
                        fprintf(stderr, "Duplicate value of -%c for new: %s old: %c", arg, parser.param.c_str(), tail);
                    }
                    tail = parser.param[0];
                    if (!std::isalpha(tail)) {
                        fprintf(stderr, "Error value of -%c must be alpha", arg);
                    }
                    tail = std::tolower(tail);
                    break;
                case 'j':
                    if (!check_duplicate(disallowed_head)) {
                        fprintf(stderr, "Duplicate value of -%c for new: %s old: %c", arg, parser.param.c_str(), disallowed_head);
                    }
                    disallowed_head = parser.param[0];
                    if (!std::isalpha(disallowed_head)) {
                        fprintf(stderr, "Error value of -%c must be alpha", arg);
                    }
                    disallowed_head = std::tolower(disallowed_head);
                    break;
                case 'r':
                    if (!enable_loop) {
                        enable_loop = true;
                    } else {
                        fprintf(stderr, "Duplicate value of -%c", arg);
                    }
                    break;
                default:
                    fprintf(stderr, "Unknown argument %c", arg);
                    break;
            }
        }
    }

    // check conflict
    switch (function) {
        case 'n':
            if (head != 0 || tail != 0 || disallowed_head != 0 || enable_loop) {
                fprintf(stderr, "argument -%c is not compatible with other argument");
            }
        case 'w':
        case 'c':
            break;
        default:
            fprintf(stderr, "You must specify a function");
    }

    // check input_file
    if (input_file.empty()) {
        fprintf(stderr, "You must specify a file");
    }
}