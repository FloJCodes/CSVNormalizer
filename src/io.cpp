#include "io.hpp"
#include <fstream>
#include <stdexcept>

void Read_lines(const std::string& filename, std::function<void(const std::string&)> on_line)
{
	std::ifstream file(filename);

	// Check if the file was opened successfully
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + filename);
	}

	// Read lines from the file and call the callback function
	std::string line;
	while (std::getline(file, line)) {
		on_line(line);
	}
}