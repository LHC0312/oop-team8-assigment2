#include "../include/view.h"
#include <iostream>

View::View() {}

void View::displayTitle() {
    printTitle();
}

void View::displayDescription() {
    printDescription();
}

void View::displayResult(const std::string& result) {
    std::cout << "Output: " << result << std::endl;
}

void View::displayError(const std::string& error) {
    std::cout << "Output: [ERROR] " << error << std::endl;
}

std::string View::getExpression() {
    std::cout << "Input: ";
    std::string expression;
    std::getline(std::cin, expression);
    return expression;
}

void View::printTitle() {
    std::cout << "===== Big Integer Calculator =====" << std::endl;
}

void View::printDescription() {
    std::cout << "Enter expressions with +, -, *, and () support" << std::endl;
    std::cout << "Enter '0' to exit" << std::endl;
}