#ifndef VIEW_H
#define VIEW_H

#include <string>

using namespace std;

class View {
public:
    View() = default;
    ~View() = default;
    
    void displayTitle() const;
    void displayDescription() const;
    void displayResult(const string& result) const;
    void displayError(const string& error) const;
    string getExpression() const;

private:
    void printTitle() const;
    void printDescription() const;
};

#endif