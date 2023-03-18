#include <vector>
#include <string>

class CharConverter {
public:
    static std::vector<std::string> read_from_ptr(char** words, int len) ;
    static void write_to_byte(const std::vector<std::string>& buffer, char** words);
};