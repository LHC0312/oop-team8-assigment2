#include <string>
#include "Number.cpp"
using namespace std;

class Operator {
  private:

  public:
    inline static const string TYPE = "OPER";
    inline static const int PRORITY = 0;
    virtual Number operate(Number a, Number b);
};