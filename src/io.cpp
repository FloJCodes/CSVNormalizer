#include "io.hpp"
#include <fstream>
#include <stdexcept>

void ReadLines(const std::string& filename, std::function<void(const std::string&)> on_line)
{
	std::ifstream file(filename);

	// Check if the file was opened successfully
	if (!file.is_open()) 
	{
		throw std::runtime_error("Could not open file: " + filename);
	}

	// Read lines from the file and call the callback function
	std::string line;
	while (std::getline(file, line)) 
	{
		on_line(line);
	}
}

void ReadCsv(const std::string& filename, Parser& parser)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file: " + filename);
	}

	parser.ParseStream(file);
}

void WriteCSV(const std::string& filename, const std::vector<std::vector<std::string>>& rows, char delimiter)
{
	std::ofstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Error opening file for writing: " << filename << "\n";
		return;
	}

	for (const auto row : rows)
	{
		for (int i = 0; i < row.size(); ++i)
		{
			std::string field = row[i];
			// If the field contains the delimiter, a quote, or a newline it needs to be quoted
			if (field.find(delimiter) != std::string::npos || field.find('"') != std::string::npos || field.find('\n') != std::string::npos)
			{	
				int pos = 0;
				// Escape quotes by doubling them
				while ((pos = field.find('"', pos)) != std::string::npos)
				{
					field.insert(pos, "\"");
					pos += 2; // Move past the pair of quotes
				}
				field = "\"" + field + "\""; // Surround with quotes
			}
			file << field;
			if (i < row.size() - 1)
			{
				file << delimiter;
			}
		}
		file << "\n";
	}
}