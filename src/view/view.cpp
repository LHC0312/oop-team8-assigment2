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
    getline(cin, line);

    string expression;
    string token;
    stringstream ss(line);

    while(ss >> token){
        expression += token;
    }

    return expression;
}

unordered_map<string, double> View::readVariables(){
    cout << "Write down value of variable\n";
    cout << ">";

    unordered_map<string, double> vars;
    string line;
    getline(cin, line);
    string kv;
    stringstream ss(line);

    while(ss >> kv){
        auto pos = kv.find("=");

        string varName = kv.substr(0, pos);
        string value = kv.substr(pos + 1);

        vars[varName] = stod(value);
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