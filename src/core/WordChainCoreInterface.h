#pragma once

#include "Graph.h"
#include "WordMap.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>

namespace core
{
	class WordChainCoreInterface : public std::enable_shared_from_this<WordChainCoreInterface>
	{

    public:
        static int gen_chains_all(char* words[], int len, char* result[]); // 需求1：函数返回所有符合定义的单词链(因不要求和其他参数一起使用,故无其他参数)
    public:
        static int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char disallowed_head, bool enable_loop); // 需求2：计算最多单词数量的单词链
    public:
        static int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char disallowed_head, bool enable_loop); // 需求3 计算最多单词数量的字母链
	};
}
