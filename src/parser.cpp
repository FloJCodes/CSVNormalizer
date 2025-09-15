#include "parser.hpp"
#include <vector>
#include <string>

Parser::Parser(char delimiter)
	: delimiter_(delimiter) 
{
    
}

std::vector<std::string> Parser::parseLine(const std::string& line)
{
	std::vector<std::string> fields;
	std::string field;
	bool inQuotes = false;

    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        }
        else if (c == delimiter_ && !inQuotes) {
            fields.push_back(field);
            field.clear();
        }
        else {
            field += c;
        }
    }
    fields.push_back(field);
	rows_.push_back(fields);

    return fields;
}

const std::vector<std::vector<std::string>>& Parser::getRows() const
{
	return rows_;
}