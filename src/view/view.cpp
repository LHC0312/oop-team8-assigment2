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
    cout << "Enter variable values (format: x=5 or just: 5 for x)\n";
    cout << "> ";

    unordered_map<string, double> vars;
    string line;
    getline(cin, line);
    
    // Handle simple number input (assume it's for 'x')
    try {
        double value = stod(line);
        vars["x"] = value;
        return vars;
    } catch (...) {
        // If it's not a simple number, try parsing as key=value pairs
    }
    
    stringstream ss(line);
    string kv;

    while(ss >> kv){
        auto pos = kv.find("=");
        if (pos != string::npos) {
            string varName = kv.substr(0, pos);
            string value = kv.substr(pos + 1);
            
            // Convert variable name to lowercase for consistency
            transform(varName.begin(), varName.end(), varName.begin(), ::tolower);
            vars[varName] = stod(value);
        }
    }

    // If no variables were parsed and we have tokens, assume it's x=value format
    if (vars.empty()) {
        vars["x"] = 0; // Default value
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