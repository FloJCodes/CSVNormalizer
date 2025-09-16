#include "parser.hpp"
#include <vector>
#include <string>

Parser::Parser(char delimiter)
    : m_delimiter(delimiter)
{

}

std::vector<std::string> Parser::ParseLine(const std::string& line)
{
    std::vector<std::string> fields = {};
    std::string field = "";
    bool inQuotes = false;

	// Iterate through each character in the line
    for (char c : line)
    {
        if (c == '"')
        {
            inQuotes = !inQuotes;
        }
        // If m_delimiter ist reached & not in quotes, save field and clear field variable
        else if (c == m_delimiter && !inQuotes)
        {
            fields.push_back(field);
            field.clear();
        }
		// Otherwise, add character to current field
        else
        {
            field += c;
        }
    }

    fields.push_back(field);
    m_rows.push_back(fields);

    return fields;
}

const std::vector<std::vector<std::string>>& Parser::ValidateRows()
{
    size_t fieldAmount = m_rows.empty() ? 0 : m_rows[0].size();

	// Iterate through each row and check if number of fields matches the first row
    for (const std::vector<std::string>& row : m_rows)
    {
        if (row.size() != fieldAmount)
        {
            m_errorRows.push_back(row);
        }
    }

    return m_errorRows;
}

const std::vector<std::vector<std::string>>& Parser::GetRows() const
{
    return m_rows;
}

const std::vector<std::vector<std::string>>& Parser::GetErrorRows() const
{
    return m_errorRows;
}