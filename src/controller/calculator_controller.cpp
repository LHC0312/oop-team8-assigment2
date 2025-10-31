#include "calculator_controller.h"

using namespace std;

void CalculatorController::run() {
    view.displayTitle();
    view.displayDescription();
    
    isRunning = true;
    
    while (isRunning) {
        const auto expression = view.getExpression();
        processExpression(expression);
    }
}

void CalculatorController::processExpression(const string& expression) {
    const auto result = service.evaluateExpression(expression);
    
    if (result == "EXIT") {
        isRunning = false;
        return;
    }
    
    if (result.substr(0, 6) == "Error:") {
        view.resultDisplay(result.substr(7));
    } else {
        view.resultDisplay(result);
    }
}

