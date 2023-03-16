#include <iostream>
#include "WordChainCoreInterface.h"
#include "CharConverter.h"

namespace core
{
    Graph BuildWordGraph(WordMap wordMap,
                         const std::function<int(const std::string&)>& calcWeight) {
        Graph graph;
        std::unordered_map<char, std::vector<std::string>> headMap;
        for (char ch = 'a'; ch <= 'z'; ch++) {
            headMap[ch] = {};
        }

        for (const auto& word : wordMap.GetAllWords()) {
            char head = word.front();
            headMap[head].push_back(word);
            graph.AddNode(wordMap.GetId(word), calcWeight(word));
        }

        for (const auto& fromWord : wordMap.GetAllWords()) {
            char tail = fromWord.back();
            int fromWordId = wordMap.GetId(fromWord);

            for (const auto& toWord : headMap[tail]) {
                int toWordId = wordMap.GetId(toWord);
                if (fromWordId != toWordId) {
                    graph.AddEdge(fromWordId, toWordId);
                }
            }
        }
        return graph;
    }

    std::pair<int, std::vector<std::string>> GenChainsAll(
            std::vector<std::string> &words) {
        auto wordMap = WordMap::Build(words);
        auto graph = BuildWordGraph(wordMap, [](const auto&) { return 1; });
        std::cout << "here";
        std::cout << std::endl;

        if (graph.HasCircle()) {
            // todo
        }

        auto allChains = graph.FindAllChains();

        std::vector<std::string> wordChains;
        for (const auto& chain : allChains) {
            std::string wordChain;
            for (int wordId : chain) {
                if (!wordChain.empty()) {
                    wordChain += ' ';
                }
                wordChain += wordMap.GetWord(wordId);
            }
            wordChains.push_back(wordChain);
        }
        return {static_cast<int>(wordChains.size()), wordChains};
    }

    std::pair<int, std::vector<std::string>> GenChainMaxLength(std::vector<std::string>& words,
            char head, char tail, char disallowed_head, bool enableLoop,
            const std::function<int(const std::string&)>& calcWeight) {
        auto wordMap = WordMap::Build(words);
        auto graph = BuildWordGraph(wordMap, calcWeight);
        if (!enableLoop && graph.HasCircle()) {
            // todo
        }

        auto headLimit = [head, &wordMap, disallowed_head](int i) {
            return wordMap.GetWord(i).front() != disallowed_head
            && (head == 0 || wordMap.GetWord(i).front() == head);
        };
        auto tailLimit = [tail, &wordMap](int i) {
            return tail == 0 || wordMap.GetWord(i).back() == tail;
        };

        auto longestChain = !enableLoop
                            ? graph.DagFindLongestChain(headLimit, tailLimit)
                            : graph.FindLongestChainRecursive(headLimit, tailLimit);

        std::vector<std::string> wordChain;
        for (auto id : longestChain) {
            wordChain.push_back(wordMap.GetWord(id));
        }
        return {wordChain.size(), wordChain};
    }

    std::pair<int, std::vector<std::string>> GenChainWord(std::vector<std::string>& words,
            char head, char tail, char disallowed_head, bool enableLoop) {
        return GenChainMaxLength(words, head, tail, disallowed_head, enableLoop,[](const auto&) { return 1; });
    }

    std::pair<int, std::vector<std::string>> GenChainChar(std::vector<std::string>& words,
            char head, char tail, char disallowed_head, bool enableLoop) {
        return GenChainMaxLength(words, head, tail, disallowed_head, enableLoop,[](const auto& s) { return s.length(); });
    }

    int WordChainCoreInterface:: gen_chains_all(char* words[], int len, char* result[]) {
        auto wordList = CharConverter::ReadFromBytePtrArray(words, len);
        //auto [ret, res] = GenChainsAll(wordList);
        auto temp = GenChainsAll(wordList);

        auto ret = std::get<0>(temp);
        auto res = std::get<1>(temp);
        if (ret < 0) {
            return ret;
        }
        CharConverter::WriteToBytePtrArray(res, result);
        return ret;
    }

    int WordChainCoreInterface:: gen_chain_word(char* words[], int len, char* result[], char head,
                       char tail, char disallowed_head, bool enable_loop) {
        auto wordList = CharConverter::ReadFromBytePtrArray(words, len);
        //auto [ret, chain] = GenChainWord(wordList, head, tail, enable_loop);
        auto temp = GenChainWord(wordList, head, tail, disallowed_head, enable_loop);
        auto ret = std::get<0>(temp);
        auto chain = std::get<1>(temp);
        if (ret < 0) {
            return ret;
        }
        CharConverter::WriteToBytePtrArray(chain, result);
        return ret;
    }

    int WordChainCoreInterface:: gen_chain_char(char* words[], int len, char* result[], char head,
                       char tail, char disallowed_head, bool enable_loop) {
        auto wordList = CharConverter::ReadFromBytePtrArray(words, len);
        //auto [ret, chain] = GenChainChar(wordList, head, tail, enable_loop);
        auto temp = GenChainChar(wordList, head, tail, disallowed_head,enable_loop);
        auto ret = std::get<0>(temp);
        auto chain = std::get<1>(temp);
        if (ret < 0) {
            return ret;
        }
        CharConverter::WriteToBytePtrArray(chain, result);
        return ret;
    }
}
