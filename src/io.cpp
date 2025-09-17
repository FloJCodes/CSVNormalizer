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