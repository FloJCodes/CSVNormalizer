#pragma once

#include "parser.hpp"

#include <string>
#include <functional>

void ReadLines(const std::string& filename, std::function<void(const std::string&)> on_line);
void ReadCsv(const std::string& filename, Parser& parser);
void WriteCSV(const std::string& filename, const std::vector<std::vector<std::string>>& rows, char delimiter);
