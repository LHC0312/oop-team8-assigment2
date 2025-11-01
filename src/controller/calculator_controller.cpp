#include "calculator_controller.h"

using namespace std;

void CalculatorController::run() {
    view.displayTitle();
    view.displayDescription();
    
    isRunning = true;
    
    while (isRunning) {
        const auto expression = view.getExpression(false);
        processExpression(expression);
    }
}

void CalculatorController::processExpression(const string& expression) {
    string result;
    
    if (service.hasVariables(expression)) {
        view.displayVariablePrompt();
        const auto variables = view.readVariables();
        result = service.evaluateExpressionWithVariables(expression, variables);
    } else {
        result = service.evaluateExpression(expression);
    }
    
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

