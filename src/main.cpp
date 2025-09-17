#include "io.hpp"
#include "parser.hpp"
#include <iostream>
#include <fstream>

Parser parser(',');

int main() {
    try {
        std::ifstream file("../../../data/customers-100.csv");
		if (!file.is_open())
		{
			throw std::runtime_error("Could not open file");
		}

		parser.ParseStream(file);
    }
    catch (const std::exception& ex) 
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    
	const auto& rows = parser.GetRows();
    for (const auto& row : rows)
    {
        for (int i = 0; i < row.size(); ++i)
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
		std::cout << "----------------------------------------" << std::endl;
        std::cout << "Error rows:" << std::endl;
        for (const auto& row : errorRows)
        {
            for (int i = 0; i < row.size(); ++i)
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