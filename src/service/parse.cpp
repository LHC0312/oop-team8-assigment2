#include "parse.h"
#include "variable.h"
#include "inf_int.h"
#include "operatorManager.h"

#include <string>

using namespace std;

class Parser {
  private:
    string s;
    int pos;
  public:
    Parser(const string& input);
    char peek();
    char get();
    void skipSpaces();

};

Parser::Parser(const string& input) : s(input), pos(0) {

}

char Parser::peek() const {
  if (pos < s.size()) return s[pos];
  return '\0';
}

char Parser::get() {
  if (pos < s.size()) return s[pos++];
  return '\0';
}

void Parser::skipSpaces() {
  while (std::isspace(static_cast<unsigned char>(peek()))) {
    get();
  }
}

inf_int* Parser::parseNumber() {
  std::string numStr;
  while (std::isdigit(static_cast<unsigned char>(peek()))) {
    numStr.push_back(get());
  }
  if (numStr.empty()) {
    throw std::runtime_error("Expected number");
  }
  return new inf_int(numStr.c_str());
}

variable* Parser::parseVariable() {
  std::string name;
  while (std::isalpha(static_cast<unsigned char>(peek()))) {
    name.push_back(get());
  }
  if (name.empty()) {
    throw std::runtime_error("Expected variable name");
  }
  return new Variable();
}

