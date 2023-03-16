#include <vector>
#include <string>

class CharConverter {
public:
    static std::vector<std::string> ReadFromBytePtrArray(char** words, int len) ;
    static void WriteToBytePtrArray(const std::vector<std::string>& buffer, char** words);
};