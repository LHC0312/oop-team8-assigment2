#include <iostream>
#include "EquationSolverService.h"

int main() {
    EquationSolverService solver;
    std::string line;

    while (true) {
        std::cout << "Input: ";
        if (!std::getline(std::cin, line)) break;
        if (line == "0") break;

        try {
            std::cout << solver.solveEquationLine(line) << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}
