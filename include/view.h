#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class View {

    public:
      View();
      void displayTitle();
      void displayDescription();
      void resultDisplay(const string& expressionResult);
      string getExpression(bool isVariableMode = false);
      unordered_map<string, double> readVariables();
      void printCalculateResult(double result);
      void printError(const string& errormsg);

    private:
      void printTitle();
      void printDescription();

  };

#endif