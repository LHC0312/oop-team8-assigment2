#include "view.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>
#include <unordered_map>

using namespace std;

View::View() {
    // Default constructor
}

void View::displayTitle(){
    printTitle();
}

void View::displayDescription(){
    printDescription();
}

void View::displayVariablePrompt(){
    cout << "Expression contains variables. Please provide values:\n";
}

void View::resultDisplay(const string& expressionResult){
    int used = static_cast<int>(11 + expressionResult.size());
    int pad = max(0, 36 - used);

    cout <<"┌──────────────────────────────────┐\n";
    cout <<"| Result :"<<expressionResult<<string(pad, ' ')<<"|\n";
    cout <<"└──────────────────────────────────┘\n";
}

string View::getExpression(bool isVariableMode){
    if (isVariableMode)
        cout << "Write linear expression (Allowed variable is x)\n";
    else
        cout << "Write down expression (q to quit)\n";
    cout << "> ";

    string line;
    if (!getline(cin, line)) {
        return "q";  // EOF reached, quit the program
    }

    string expression;
    string token;
    stringstream ss(line);

    while(ss >> token){
        expression += token;
    }

    return expression;
}

unordered_map<string, double> View::readVariables(){
    cout << "Enter variable values (format: x=5 or 5)\n";
    cout << "> ";

    unordered_map<string, double> vars;
    string line;
    getline(cin, line);
    
    // Remove leading/trailing whitespace
    line.erase(0, line.find_first_not_of(" \t\n\r"));
    line.erase(line.find_last_not_of(" \t\n\r") + 1);
    
    // Check if line is empty
    if (line.empty()) {
        cout << "No input provided. Using default value x=0\n";
        vars["x"] = 0;
        return vars;
    }
    
    // Check if the entire line contains '=' for variable assignment
    auto pos = line.find("=");
    if (pos != string::npos) {
        string varName = line.substr(0, pos);
        string value = line.substr(pos + 1);
        
        // Remove whitespace
        varName.erase(remove_if(varName.begin(), varName.end(), ::isspace), varName.end());
        value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());
        
        if (varName.empty() || value.empty()) {
            cout << "Invalid format. Please use format: x=5 or 5\n";
            vars["x"] = 0;
            return vars;
        }
        
        // Convert variable name to lowercase for consistency
        transform(varName.begin(), varName.end(), varName.begin(), ::tolower);
        
        try {
            vars[varName] = stod(value);
        } catch (...) {
            cout << "Invalid number: " << value << ". Using default value x=0\n";
            vars["x"] = 0;
        }
        return vars;
    }
    
    // Handle simple number input (assume it's for 'x')
    try {
        double value = stod(line);
        vars["x"] = value;
        return vars;
    } catch (...) {
        cout << "Invalid input: " << line << ". Please use format: x=5 or 5\n";
        vars["x"] = 0;
    }

    return vars;
}

void View::printCalculateResult(double result){
    stringstream ss;
    ss << result;
    resultDisplay(ss.str());
}

void View::printError(const string& errormsg){
    cerr << "Error" << errormsg << endl;
}

void View::printTitle(){
    cout << "===== Big Integer Calculator =====\n";
}

void View::printDescription(){
    cout << "   ┌─────┬─────┬─────┬─────┐\n";
    cout << "   │  7  │  8  │  9  │  /  │\n";
    cout << "   ├─────┼─────┼─────┼─────┤\n";
    cout << "   │  4  │  5  │  6  │  *  │\n";
    cout << "   ├─────┼─────┼─────┼─────┤\n";
    cout << "   │  1  │  2  │  3  │  -  │\n";
    cout << "   ├─────┼─────┼─────┼─────┤\n";
    cout << "   │  0  │  .  │ ( ) │  +  │\n";
    cout << "   └─────┴─────┴─────┴─────┘\n";
}