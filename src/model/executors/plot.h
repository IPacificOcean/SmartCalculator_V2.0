//
// Created by Qyburn Bongo on 3/16/23.
//

#ifndef GOOGLE_TESTS_PLOT_H
#define GOOGLE_TESTS_PLOT_H

#include <string.h>

#include <list>
#include <stack>
#include <utility>
#include <vector>

#include "../data/data_plot.h"
#include "calculator_exec.h"

#define EPS 1e-7

namespace s21 {

class CalculatorPlot : public Calculator {
 public:
  /**
   * @brief Calculates a mathematical expression for the graph
   * @param data_plot - a class that contains the data for counting
   * @param rpn_expression - the list of tokens of a mathematical expression
   * @return pair with 2 arrays of coordinates x, y to plot
   */
  std::pair<std::vector<double>, std::vector<double>> PlotCalculation(
      const DataPlot &data_plot, std::list<std::string> rpn_expression);

 private:
  void GetDigitFromRpn(const std::string &token, const double &xValue,
                       std::stack<double> &numbers);

  double CalculateStepSize(const DataPlot &data_plot);
};

}  // namespace s21

#endif  // GOOGLE_TESTS_PLOT_H
