#include "../domain/Number.cpp"
#include <vector>

using namespace std;

class CalculratorService {
  public:
    Number calculate(vector<string> tokens);
};