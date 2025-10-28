#include "../view/View.cpp"

class CalculatorController {
  private:
    int isRunning = false;
  public:
    CalculatorController();
    void run();
};

CalculatorController::CalculatorController() {

}

void CalculatorController::run() {
  View view;
  while(isRunning) {
    try {
    vector<string> tokens = view.tokenize();

    }
    catch {

    }
  }
}



