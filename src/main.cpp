#include "io.hpp"
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    try {
        read_lines("../../../data/customers-100.csv", [](const std::string& line) {
            std::cout << line << std::endl;
            });
    }
    catch (const std::exception& ex) {
        std::cerr << "Fehler: " << ex.what() << std::endl;
        std::cin.get(); // File stays open
    }
    std::cin.get(); // File stays open
    return 0;
}