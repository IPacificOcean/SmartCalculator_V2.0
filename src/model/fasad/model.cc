//
// Created by Qyburn Bongo on 3/16/23.
//
#include "model.h"

double s21::Model::Calculation(std::string &expression) {
  if (validator_.IsNotValid(expression)) {
    throw std::invalid_argument("error: invalid input for calculate");
  }
  std::list<std::string> queueRpn = parser_.ExpressionToRpn(expression);
  double result{};
  try {
    result = calculator_.Calculate(queueRpn);
  } catch (...) {
    throw;
  }
  return result;
}

std::pair<std::vector<double>, std::vector<double>> s21::Model::PlotCalculation(
    const DataPlot &data_plot) {
  if (validator_.IsNotValid(data_plot.expression_)) {
    throw std::invalid_argument("error: invalid input for graph");
  }

  std::list<std::string> rpn_expression =
      parser_.ExpressionToRpn(data_plot.expression_);

  std::pair<std::vector<double>, std::vector<double>> res;

  try {
    res = calculator_plot_.PlotCalculation(data_plot, rpn_expression);
  } catch (...) {
    throw;
  }

  return res;
}
