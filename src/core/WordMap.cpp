#include <algorithm>
#include <locale>
#include "WordMap.h"

namespace core
{
    static std::string toLower(const std::string& input) {
        std::string result = input;
        std::locale loc;
        std::transform(result.begin(), result.end(), result.begin(),
                       [&loc](wchar_t c) { return std::tolower(c, loc); });
        return result;
    }


	std::shared_ptr<WordMap> WordMap::Build(std::vector<std::string> &wordList)
	{
		auto wordMap = std::make_shared<WordMap>();
		for (const auto& word : wordList)
		{
			wordMap->AddWord(toLower(word));
		}

		return wordMap;
	}

	int WordMap::AddWord(const std::string &word)
	{
		if (_wordToId.find(word) != _wordToId.end())
		{
			return _wordToId[word];
		}

		++_wordCount;
		_wordToId.emplace(word, _wordCount);
		_idToWord.emplace(_wordCount, word);
		return _wordCount;
	}

	std::string WordMap::GetWord(int id)
	{
		assert(id > 0 && id <= _wordCount);
		return _idToWord[id];
	}

	int WordMap::GetId(const std::string &word)
	{
        assert(_wordToId.find(toLower(word)) != _wordToId.end());
		return _wordToId[toLower(word)];
	}

    std::vector<std::string> WordMap::GetAllWords() const {
        std::vector<std::string> keys;
        for (const auto& key : _wordToId) {
            keys.push_back(key.first);
        }
        return keys;
    }
}
