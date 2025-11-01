#ifndef CALCULATOR_CONTROLLER_H
#define CALCULATOR_CONTROLLER_H

#include "view.h"
#include "calculator_service.h"

using namespace std;

class CalculatorController {
public:
    CalculatorController() = default;
    ~CalculatorController() = default;
    
    void run();

private:
    View view;
    CalculatorService service;
    bool isRunning = false;

    void processExpression(const string& expression);
};

#endif