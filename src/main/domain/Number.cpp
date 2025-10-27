#include <string>
using namespace std;

class Number {
  private:

  public:
    inline static const string TYPE = "NUMBER";
    inline static Number from();
    string toString();

};