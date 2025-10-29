#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>
#include <unordered_map>

using namespace std;

class View {
    
    public:
      View();

      void displayTitle(){
        printTitle();
      }
      
      void displayDescription(){
        printDescription();
      }
      
      void resultDisplay(const string& expressionResult){
        int used = static_cast<int>(11 + expressionResult.size());
        int pad = max(0, 35 - used);


        cout <<"┌──────────────────────────────────┐\n";
        cout <<"| Result :"<<expressionResult<<string(pad, ' ')<<"|\n";
        cout <<"└──────────────────────────────────┘\n";

      }
      //1 mode : simple arithmetic operation , 2 mode : equation
      int chooseMode(){
        cout <<"[Mode] 1.Basic  2.Equation\n";
        cout <<"Select mode : 1 or 2\n";
        cout <<">";
        
        string sel;
        getline(cin, sel);
        if(sel == "2"){
          return 2;
        }
        return 1;
      }


      //get line and make it as token 
      vector<string> tokenize(bool isVariableMode = false){
        if (isVariableMode)
            cout << "Write linear expression (Allowed variable is x)\n";
        else
            cout << "Write down expression (q to quit)\n";
        cout << "> ";

        string line;
        getline(cin, line);

        vector<string> tokens;
        string token;
        stringstream ss(line);

        while(ss >> token){
          tokens.push_back(token);
        }

        return tokens;
      }

      //use when it is 2 mode 
      unordered_map<string, double> readVariables(){
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

          vars[varName] = stod(value); //변수이면 double로 받는게 맞나? 얘도 string으로 해야하나 흠 
        }

        return vars;
      }
      
      //print result
      void printCalculateResult(double result){
        stringstream ss;
        ss << result;
        resultDisplay(ss.str());
      }
      
      //print error
      void printError(const string& errormsg){
        cerr << "Error" << errormsg << endl;
      }

    private:
      void printTitle(){
        cout << "===== Big Integer Calculator =====\n";
      }

      //keyboard design
      void printDescription(){
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
        
      
  };



