//
// Created by AORUS on 2023/3/11.
//

#ifndef WORDLIST_CORE_H
#define WORDLIST_CORE_H
class Core {
public:
    static int gen_chains_all(char *words[], int len, char* result[]);
    static int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char disallowed_head, bool enable_loop);
    static int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char disallowed_head, bool enable_loop);
};

#endif //WORDLIST_CORE_H
