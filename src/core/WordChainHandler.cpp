#include "WordChainHandler.h"
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include "Graph.h"
#include "WordMap.h"

core::Graph BuildWordGraph(core::WordMap wordMap,
                           const std::function<int(const std::string&)>& calcWeight) {
    core::Graph graph;
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