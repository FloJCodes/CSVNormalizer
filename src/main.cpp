#include "io.hpp"
#include "parser.hpp"
#include <iostream>

Parser parser(',');

int main() {
    try {
        read_lines("../../../data/customers-100.csv", [&](const std::string& line) 
            {
				parser.parseLine(line);
            });
    }
    catch (const std::exception& ex) 
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    
	const auto& rows = parser.getRows();
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


    return 0;
}