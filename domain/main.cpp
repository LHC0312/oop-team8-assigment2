#include "include/inf_int.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    while (true) {
        cout << "Input: ";

        string line;
        if (!std::getline(cin, line)) {
            // EOF나 입력 오류면 그냥 종료
            break;
        }

        if (line == "0") {
            break;
        }

        string lhs_str;
        string rhs_str;
        char op = 0;

        {
            size_t i = 0;
            while (i < line.size() && line[i] == ' ') i++;

            size_t start = i;
            while (i < line.size() && line[i] != ' ' && line[i] != '\t') {
                i++;
            }
            lhs_str = line.substr(start, i - start);

            while (i < line.size() && line[i] == ' ') i++;
            if (i < line.size()) {
                op = line[i];
                i++;
            }

            while (i < line.size() && line[i] == ' ') i++;
            start = i;
            while (i < line.size() && line[i] != ' ' && line[i] != '\t') {
                i++;
            }
            rhs_str = line.substr(start, i - start);
        }

        inf_int lhs(lhs_str.c_str());
        inf_int rhs(rhs_str.c_str());
        inf_int result;

        if (op == '+') {
            result = lhs + rhs;
        } else if (op == '-') {
            result = lhs - rhs;
        } else if (op == '*') {
            result = lhs * rhs;
        } else {
            cout << "Output: [ERROR] unsupported operator" << endl;
            continue;
        }

        cout << "Output: " << result << endl;
    }

    return 0;
}
