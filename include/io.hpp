#pragma once

#include <string>
#include <functional>

void read_lines(const std::string& filename, std::function<void(const std::string&)> on_line);
