#include <iostream>
#include <string>
#include <exception>
#include "EquationSolverService.h"

int main() {
    EquationSolverService solver;

    while (true) {
        std::cout << "Equation? (ex: 2*x+4=12, 0 to quit): ";

        std::string line;
        if (!std::getline(std::cin, line)) {
            break;
        }

        if (line == "0") {
            break;
        }

        try {
            std::string result = solver.solveEquationLine(line);
            std::cout << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
