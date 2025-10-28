#include <iostream>
#include <string>
#include "Parser.h"
#include "inf_int.h"
#include "include2/Parser.h"

using namespace std;

int main() {
    // 1) 테스트용 수식과 변수 지정
    string exprInput = "2*x+4";   // ← 여기 식 마음대로 바꿔가면서 테스트
    string varName   = "x";
    inf_int varValue("3");        // x = 3

    cout << "[LOG] expr=" << exprInput << ", "
         << varName << "=" << varValue << endl;

    try {
        cout << "[LOG] creating parser\n";
        Parser p(exprInput);

        cout << "[LOG] calling parse()\n";
        Expr* root = p.parse();
        cout << "[LOG] parse() returned\n";

        cout << "[LOG] calling evaluate()\n";
        inf_int result = root->evaluate(varName, varValue);
        cout << "[LOG] evaluate() returned\n";

        cout << "Result: " << result << endl;

        delete root;
        cout << "[LOG] root deleted\n";
    } catch (...) {
        cerr << "[Error] 예외 발생\n";
    }

    return 0;
}
