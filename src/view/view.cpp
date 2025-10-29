#include "../include/view.h"
#include <iostream>

using namespace std;

void View::displayTitle() const {
    printTitle();
}

void View::displayDescription() const {
    printDescription();
}

void View::displayResult(const string& result) const {
    cout << "Output: " << result << endl;
}

void View::displayError(const string& error) const {
    cout << "Output: [ERROR] " << error << endl;
}

string View::getExpression() const {
    cout << "Input: ";
    string expression;
    getline(cin, expression);
    return expression;
}

void View::printTitle() const {
    cout << "===== Big Integer Calculator =====" << endl;
}

void View::printDescription() const {
    cout << "Enter expressions with +, -, *, and () support" << endl;
    cout << "Enter '0' to exit" << endl;
}