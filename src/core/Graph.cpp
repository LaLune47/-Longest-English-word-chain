#include <queue>
#include <iostream>
#include "Graph.h"

namespace core
{

    void Graph::AddNode(int id, int weight) {
        _weights[id] = weight;
        if (id >= _inDegrees.size()) {
            _inDegrees.resize(id + 1);
            _inDegrees[id] = 0;
        }
    }

	void Graph::AddEdge(int from, int to)
	{
		Edge tempVar = Edge();
		tempVar.From = from;
		tempVar.To = to;
		AddEdge(tempVar);
	}

	void Graph::AddEdge(Edge edge)
	{
		if (_edges.find(edge.From) != _edges.end())
		{
			_edges.emplace(edge.From, std::vector<Edge>());
		}

		if (_edges.find(edge.To) != _edges.end())
		{
			_edges.emplace(edge.To, std::vector<Edge>());
		}

		_edges[edge.From].push_back(edge);
		_inDegrees[edge.To]++;
	}

    bool Graph::HasCircle() {
        auto tempInDegrees = std::vector<int>(_inDegrees);
        std::queue<int> q;
        for (auto & _edge : _edges) {
            if (tempInDegrees[_edge.first] == 0) {
                q.push(_edge.first);
            }
        }
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (auto edge : _edges[node]) {
                tempInDegrees[edge.To]--;
                if (tempInDegrees[edge.To] == 0) {
                    q.push(edge.To);
                }
            }
        }
        return any_of(tempInDegrees.begin(), tempInDegrees.end(), [](int x){ return x != 0; });
    }

    std::vector<int> Graph::DagTopoSort() {
        auto tempInDegrees = std::vector<int>(_inDegrees);
        auto result = std::deque<int>();
        std::queue<int> q;
        for (auto & _edge : _edges) {
            if (tempInDegrees[_edge.first] == 0) {
                q.push(_edge.first);
            }
        }
        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            result.push_back(node);

            for (auto edge : _edges[node]) {
                tempInDegrees[edge.To]--;
                if (tempInDegrees[edge.To] == 0) {
                    q.push(edge.To);
                }
            }
        }

        assert(any_of(tempInDegrees.begin(), tempInDegrees.end(), [](int x){ return x == 0; }));
        std::vector<int> res(result.size());
        for (int & re : res) {
            re = result.front();
            result.pop_front();
        }
        return res;
    }

	std::vector<int> Graph::FindLongestChainRecursive(const std::function<bool(int)>& head, const std::function<bool(int)>& tail)
	{
        std::vector<int> headQueue;
        for (auto & _edge : _edges) {
            if (head(_edge.first)) {
                headQueue.push_back(_edge.first);
            }
        }

		auto longestChain = std::vector<int>();
		auto curValue = 0;
		auto maxValue = 0;
		for (auto headNode : headQueue)
		{
            std::vector<int> curChain;
            std::unordered_set<int> chainSet;
            FindLongestChainWithSourceRecursive(headNode, tail, curChain, chainSet, longestChain, curValue, maxValue);
		}

		return longestChain.size() >= 2 ? longestChain : std::vector<int>();
	}

    void Graph::FindLongestChainWithSourceRecursive(int u, const std::function<bool(int)>& tail, std::vector<int>& curChain,
                                             std::unordered_set<int>& chainSet, std::vector<int>& longestChain, int& curValue, int& maxValue) {
        curChain.push_back(u);
        chainSet.insert(u);
        curValue += _weights[u];

        if (tail(u) && curChain.size() >= 2 && curValue > maxValue) {
            longestChain.clear();
            longestChain.insert(longestChain.end(), curChain.begin(), curChain.end());
            maxValue = curValue;
        }

        for (auto edge : _edges[u]) {
            int v = edge.To;
            if (!chainSet.count(v)) {
                FindLongestChainWithSourceRecursive(v, tail, curChain, chainSet, longestChain, curValue, maxValue);
            }
        }
        curChain.pop_back();
        chainSet.erase(u);
        curValue -= _weights[u];
    }

    std::vector<int> Graph::DagFindLongestChain(const std::function<bool(int)>& head, const std::function<bool(int)>& tail) {

        std::unordered_set<int> visited;
        std::vector<int> topo = DagTopoSort();

        std::vector<int> queue;
        for (int node : topo) {
            if (head(node)) {
                queue.push_back(node);
            }
        }

        std::vector<int> result;
        int maxLength = INT_MIN;
        for (int node : queue) {
            if (!visited.count(node)) {
                //auto [longestPathFromNode, length] = DagFindLongestChainWithSource(node, visited, tail);
                auto temp = DagFindLongestChainWithSource(node, visited, tail);
                auto longestPathFromNode = std::get<0>(temp);
                auto length = std::get<1>(temp);
                if (longestPathFromNode.size() >= 2 && (result.empty() || maxLength < length)) {
                    maxLength = length;
                    result = longestPathFromNode;
                }
            }
        }

        return result;
    }

    std::pair<std::vector<int>, int> Graph::
    DagFindLongestChainWithSource(int source,std::unordered_set<int>& visited, const std::function<bool(int)>& tail) {
        std::unordered_map<int, int> path;
        std::queue<int> q;
        q.push(source);
        std::unordered_map<int, int> distance;
        for (auto & _edge : _edges) {
            distance[_edge.first] = INT_MIN;
        }
        distance[source] = _weights[source];
        path[source] = INT_MIN;
        visited.insert(source);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            visited.insert(node);
            if (distance[node] == INT_MIN) {
                continue;
            }
            for (auto edge : _edges[node]) {
                if (distance[edge.To] < distance[node] + _weights[edge.To]) {
                    distance[edge.To] = distance[node] + _weights[edge.To];
                    path[edge.To] = node;
                    q.push(edge.To);
                }
            }
        }

        std::vector<std::pair<int, int>> filterResult;
        for (auto dis : distance) {
            if (tail(dis.first) && dis.second != INT_MIN) {
                filterResult.emplace_back(dis);
            }
        }
        if (filterResult.empty()) {
            return make_pair(std::vector<int>(), INT_MIN);
        }

        int longestPathEnd = filterResult[0].first;
        int maxLength = filterResult[0].second;
        for (auto dis : filterResult) {
            if (dis.second > maxLength) {
                maxLength = dis.second;
                longestPathEnd = dis.first;
            }
        }

        std::vector<int> result;
        for (int n = longestPathEnd; n != INT_MIN; n = path[n]) {
            result.push_back(n);
        }
        reverse(result.begin(), result.end());
        return make_pair(result, maxLength);
    }

    void Graph::FindPath(int u, std::vector<int>& curChain, std::unordered_set<int>& chainSet, std::vector<std::vector<int>>& chains) {
        curChain.push_back(u);
        chainSet.insert(u);

        if (curChain.size() > 1) {
            chains.push_back(curChain);
        }

        for (auto edge : _edges[u]) {
            int v = edge.To;
            if (!chainSet.count(v)) {
                FindPath(v, curChain, chainSet, chains);
            }
        }

        curChain.pop_back();
        chainSet.erase(u);
    }


	std::vector<std::vector<int>> Graph::FindAllChains()
	{
		auto chains = std::vector<std::vector<int>>();
		for (const auto& node : _edges)
		{
            std::vector<int> curChain;
            std::unordered_set<int> chainSet;
            FindPath(node.first, curChain, chainSet, chains);
		}
		return chains;
	}
}
