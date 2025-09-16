#include <iostream>
#include <vector>
#include <string>

class Parser {
public:
    Parser(char m_delimiter = ',');
    std::vector<std::string> ParseLine(const std::string& line);
    const std::vector<std::vector<std::string>>& ValidateRows();
    const std::vector<std::vector<std::string>>& GetRows() const;
    const std::vector<std::vector<std::string>>& GetErrorRows() const;
private:
    char m_delimiter;
    std::vector<std::vector<std::string>> m_rows;
    std::vector<std::vector<std::string>> m_errorRows;
};