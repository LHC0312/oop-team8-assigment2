#include <iostream>
#include <string>
//#include "Parser.h"
#include "include/inf_int.h"
#include "expr/include2/Parser.h"
#include "expr/include2/Equation.h"

using namespace std;

int main() {
    
    string exprInput = "2*x+4=12";
    string varName   = "x";
    inf_int evalValue("3");

    cout << "[LOG] expr=" << exprInput << endl;

    try {
        Parser p(exprInput);
        Expr* root = p.parse();
        cout << "[LOG] parse() returned\n";

        Equation equationSolver; // 2. 클래스 이름 변경
        equationSolver.process(root, varName, evalValue); // 3. 변수 이름 변경

        delete root;
        cout << "[LOG] root deleted\n";
    } catch (...) {
        // ...
    }
    return 0;
}
