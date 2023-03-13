//
// Created by AORUS on 2023/3/8.
//

#pragma once

#include <vector>
#include <string>

class ArgParser{
public:
    ArgParser(int argc, char* argv[], const char *pattern);

    static void parse_arg(ArgParser &parser, char &head, char &tail, char &disallowed_head, bool &enable_loop,
                          char &function, std::string &input_file);

    int next_arg();

    std::string param;
private:
    int argc;
    std::vector<char*> argv;
    std::vector<int> options;
    int argv_index;
};
