//
// Created by Qyburn Bongo on 3/16/23.
//

#include "plot.h"

#include <cmath>
#include <iostream>

// надо вместо очереди rpn_expression_ использовать лист, так как в очереди нет
// итераторов и она в первом же цикле обнуляется
std::pair<std::vector<double>, std::vector<double>>
s21::CalculatorPlot::PlotCalculation(const DataPlot &data_plot,
                                     std::list<std::string> rpn_expression) {
  std::vector<double> X{}, Y{};
  double step_size = CalculateStepSize(data_plot);

  for (auto xValue = data_plot.x_begin_; xValue < data_plot.x_end_;
       xValue += step_size) {
    double yValue = 0.0;
    std::stack<double> numbers{};

    if (fabs(xValue) < EPS) {  // нужно при нуле
      xValue = 0.0;
    }

    for (auto token : rpn_expression) {
      GetDigitFromRpn(token, xValue, numbers);
      if (token == "+" || token == "-" || token == "*" || token == "/" ||
          token == "^" || token == "m") {
        numbers.push(BinaryFunc(token, numbers));
      } else if (isalpha(token.front()) && token != "X") {
        numbers.push(UnaryFunc(token, numbers));
      }
    }

    yValue = numbers.top();
    if (!std::isfinite(yValue))
      throw std::invalid_argument("value is infinite or nan");
    X.push_back(xValue);
    Y.push_back(yValue);
  }
  return {X, Y};
}

void s21::CalculatorPlot::GetDigitFromRpn(const std::string &token,
                                          const double &xValue,
                                          std::stack<double> &numbers) {
  if (isdigit(token.front())) {
    numbers.push(std::stod(token));
  } else if (token == "X") {
    numbers.push(xValue);
  }
}

double s21::CalculatorPlot::CalculateStepSize(const DataPlot &data_plot) {
  double x_begin = abs(data_plot.x_begin_);
  double x_end = abs(data_plot.x_end_);
  return static_cast<double>((x_begin + x_end) * 0.0001);
}
