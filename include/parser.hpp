#include <iostream>
#include <vector>
#include <string>

class Parser {
public:
    Parser(char delimiter = ',');
    std::vector<std::string> parseLine(const std::string& line);
    const std::vector<std::vector<std::string>>& getRows() const;
private:
    char delimiter_;
    std::vector<std::vector<std::string>> rows_;
};