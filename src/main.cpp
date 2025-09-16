#include "io.hpp"
#include "parser.hpp"
#include <iostream>

Parser parser(',');

int main() {
    try {
        Read_lines("../../../data/customers-100.csv", [&](const std::string& line) 
            {
				parser.ParseLine(line);
            });
    }
    catch (const std::exception& ex) 
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    
	const auto& rows = parser.GetRows();
    for (const auto& row : rows)
    {
        for (int i = 0; i < row.size(); i++)
        {
			std::cout << row[i];
            if (i < row.size() - 1)
            {
				std::cout << "|";
            }
        }
        std::cout << std::endl;
    }

	const auto& errorRows = parser.ValidateRows();
    if (!errorRows.empty())
    {
        std::cout << "Error rows:" << std::endl;
        for (const auto& row : errorRows)
        {
            for (int i = 0; i < row.size(); i++)
            {
                std::cout << row[i];
                if (i < row.size() - 1)
                {
                    std::cout << "|";
                }
            }
            std::cout << std::endl;
        }
    }
    return 0;
}