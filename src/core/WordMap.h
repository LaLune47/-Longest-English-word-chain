#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <memory>

namespace core
{
	class WordMap : public std::enable_shared_from_this<WordMap>
	{
	private:
		std::unordered_map<std::string, int> _wordToId = std::unordered_map<std::string, int>();
		std::unordered_map<int, std::string> _idToWord = std::unordered_map<int, std::string>();
		int _wordCount = 0;

	public:
        static WordMap Build(std::vector<std::string> &wordList);

		int AddWord(const std::string &word);

		std::string GetWord(int id);

		int GetId(const std::string &word);

		std::vector<std::string> GetAllWords() const;
	};
}
