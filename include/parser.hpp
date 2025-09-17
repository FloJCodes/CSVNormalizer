#include <iostream>
#include <vector>
#include <string>

#ifndef PARSER_HPP
#define PARSER_HPP

class Parser {
public:
    Parser(char delimiter = ',');
    std::vector<std::string> ParseLine(const std::string& line);
    void ParseStream(std::istream& is);
    const std::vector<std::vector<std::string>>& ValidateRows();
    const std::vector<std::vector<std::string>>& GetRows() const;
    const std::vector<std::vector<std::string>>& GetErrorRows() const;
private:
    char m_delimiter;
    std::vector<std::vector<std::string>> m_rows;
    std::vector<std::vector<std::string>> m_errorRows;
};

#endif // PARSER_HPP