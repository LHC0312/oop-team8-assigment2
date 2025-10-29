#include "../include/calculator_controller.h"

CalculatorController::CalculatorController() : isRunning(false) {}

void CalculatorController::run() {
    view.displayTitle();
    view.displayDescription();
    
    isRunning = true;
    
    while (isRunning) {
        std::string expression = view.getExpression();
        processExpression(expression);
    }
}

void CalculatorController::processExpression(const std::string& expression) {
    std::string result = service.evaluateExpression(expression);
    
    if (result == "EXIT") {
        isRunning = false;
        return;
    }
    
    if (result.substr(0, 6) == "Error:") {
        view.displayError(result.substr(7));
    } else {
        view.displayResult(result);
    }
}

