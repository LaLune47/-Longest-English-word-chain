#include <functional>
#include <string>
#include "Graph.h"
#include "WordMap.h"

class WordChainHandler {
public:
    static std::shared_ptr<core::Graph> BuildWordGraph(std::shared_ptr<core::WordMap> wordMap, std::function<int(const std::string&)> calcWeight);
};