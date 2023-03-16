#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <deque>
#include <algorithm>
#include <limits>
#include <functional>
#include <cassert>
#include <memory>

namespace core
{
	class Edge
	{
	public:
		int From = 0, To = 0;
	};

	class Graph : public std::enable_shared_from_this<Graph>
	{
	private:
		std::unordered_map<int, std::vector<Edge>> _edges = std::unordered_map<int, std::vector<Edge>>();
		std::unordered_map<int, int> _weights = std::unordered_map<int, int>();
		std::vector<int> _inDegrees = std::vector<int>();

	public:
		void AddNode(int id, int weight);

		void AddEdge(int from, int to);

	private:
		void AddEdge(Edge edge);

	public:
		bool HasCircle();

	private:
		std::vector<int> DagTopoSort();

	public:
		std::vector<int> FindLongestChainRecursive(const std::function<bool(int)>& head, const std::function<bool(int)>& tail);

	private:
        void FindLongestChainWithSourceRecursive(int u, const std::function<bool(int)>& tail, std::vector<int>& curChain,
                                                        std::unordered_set<int>& chainSet, std::vector<int>& longestChain, int& curValue, int& maxValue);

    public:
		std::vector<int> DagFindLongestChain(const std::function<bool(int)>& head, const std::function<bool(int)>& tail);

    public:
        std::pair<std::vector<int>, int> DagFindLongestChainWithSource(int source, std::unordered_set<int>& visited, const std::function<bool(int)>& tail);

    private:
        void FindPath(int u, std::vector<int>& curChain, std::unordered_set<int>& chainSet, std::vector<std::vector<int>>& chains);

    public:
		std::vector<std::vector<int>> FindAllChains();
	};
}
