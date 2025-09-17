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
    for (int i = 0; i < line.size(); ++i)
    {
        char c = line[i];
        if (c == '"')
        {
            // CSV-Standard: ein doppeltes "" innerhalb eines Feldes ergibt ein "
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                field += '"';
                ++i;
            }
            else {
                inQuotes = !inQuotes;
            }
        }
        else if (c == m_delimiter && !inQuotes)
        {
            fields.push_back(field);
            field.clear();
        }
        else
        {
            field += c;
        }
    }

    fields.push_back(field);

    return fields;
}

void Parser::ParseStream(std::istream& is)
{
    std::string line;
    std::string multiline;
    bool building_multiline = false;

    while (std::getline(is, line))
    {
        if (!building_multiline)
        {
			// Count quotes in the line
            size_t quoteCount = 0;
            for (size_t i = 0; i < line.size(); ++i) 
            {
                if (line[i] == '"') 
                {
					// Ignore "" as escaped quotes
                    if (i + 1 < line.size() && line[i + 1] == '"') 
                    {
                        ++i;
                    }
                    else 
                    {
                        ++quoteCount;
                    }
                }
            }

            if (quoteCount % 2 == 0) 
            {
                // Parse normal for even amount
                auto fields = ParseLine(line);
                m_rows.push_back(fields);
            }
            else 
            {
                // Start multiline für odd amount
                multiline = line;
                building_multiline = true;
            }
        }
        else
        {
            // Count quotes in new line
            size_t quoteCount = 0;
            for (size_t i = 0; i < line.size(); ++i) 
            {
                if (line[i] == '"') 
                {
					// Ignore "" as escaped quotes
                    if (i + 1 < line.size() && line[i + 1] == '"') 
                    {
                        ++i;
                    }
                    else 
                    {
                        ++quoteCount;
                    }
                }
            }

            if (quoteCount % 2 == 0)
            {
                // New line has even quotes : Error in previous line
				auto prevRow = ParseLine(multiline);
				m_errorRows.push_back(prevRow);

                auto thisRow = ParseLine(line);
                m_rows.push_back(thisRow);
            }
            else
            {
				// New line has odd quotes : Parse full multiline
                multiline += "\n" + line;
                auto fields = ParseLine(multiline);
                m_rows.push_back(fields);
            }

            multiline.clear();
            building_multiline = false;
        }
    }

    // End of file but still multiline open : Error
    if (!multiline.empty() && building_multiline) {
        auto fields = ParseLine(multiline);
        m_errorRows.push_back(fields);
    }
}

const std::vector<std::vector<std::string>>& Parser::ValidateRows()
{
    size_t fieldAmount = m_rows.empty() ? 0 : m_rows[0].size();

	// Iterate through each row and check if number of fields matches the first row
    for (const std::vector<std::string>& row : m_rows)
    {
        bool isError = false;

        if (row.size() != fieldAmount)
        {
            isError = true;
        }
        else
        {
            for (const std::string& field : row)
            {
                if (field.empty())
                {
                    isError = true;
                    break;
                }
            }
        }

		if (isError)
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