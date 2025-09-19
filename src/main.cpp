#include "io.hpp"
#include "parser.hpp"
#include <iostream>
#include <fstream>

int mainDebug() {
    Parser parser(',');

    // Create stream and parse file
    try 
    {
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
    
	//Write parsed data to console
	const std::vector<std::vector<std::string>>& rows = parser.GetRows();
    for (const std::vector<std::string>& row : rows)
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

	// Write error rows to console
	const std::vector<std::vector<std::string>>& errorRows = parser.ValidateRows();
    if (!errorRows.empty())
    {
		std::cout << "----------------------------------------" << std::endl;
        std::cout << "Error rows:" << std::endl;
        for (const std::vector<std::string>& row : errorRows)
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

	// Write valid rows to console
	const std::vector<std::vector<std::string>>& validRows = parser.GetValidRows();
    if (!validRows.empty())
    {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Valid rows:" << std::endl;
        for (const std::vector<std::string>& row : validRows)
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

    WriteCSV("output.csv", validRows, ',');

    return 0;
}



int main(int argc, char* argv[]) {
    if (argc < 3) 
    {
        std::cout << "Usage: CSVNormalizer <input.csv> <output.csv> [--delimiter <char>] [--remove-error-rows]\n";
        return 1;
    }
    
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    char delimiter = ',';
    bool removeErrorRows = false;

    // Iterate through arguments to change needed bools
    for (int i = 3; i < argc; ++i) 
    {
        std::string arg = argv[i];
        if (arg == "--delimiter" && i + 1 < argc)
        {
            delimiter = argv[i + 1][0];
            ++i;
        }
        else if (arg == "--remove-error-rows") 
        {
            removeErrorRows = true;
        }
        else 
        {
            std::cout << "Unknown option: " << arg << "\n";
            return 1;
        }
    }
    
	// Print configuration
    std::cout << "INPUT: " << inputFile << "\n";
    std::cout << "OUTPUT: " << outputFile << "\n";
    std::cout << "DELIMITER: " << delimiter << "\n";
    std::cout << "REMOVE ERRORS: " << (removeErrorRows ? "yes" : "no") << "\n" << std::endl;

	std::cout << "Generating file... \n " << std::endl;

	Parser parser(delimiter);

	// Create stream and parse file
    try 
    {
        std::ifstream file(inputFile);
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

	// Write parsed data or valid data to output file
	const std::vector<std::vector<std::string>>& rows = parser.GetRows();
	if (removeErrorRows) 
    {
        const std::vector<std::vector<std::string>>& errorRows = parser.ValidateRows();
        WriteCSV(outputFile, parser.GetValidRows(), delimiter);

        std::cout << "File generated" << std::endl;
	}
	else 
    {
		WriteCSV(outputFile, rows, delimiter);
        std::cout << "File generated" << std::endl;
	}

    return 0;
}
