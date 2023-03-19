//
// Created by Qyburn Bongo on 3/16/23.
//

#include "controller.h"

double s21::Controller::Calculation(QString &expression) {
    double result{};
    std::string expressionToString = expression.toStdString();
    try {
        result = model_.Calculation(expressionToString);
    } catch (...) {
//                throw std::invalid_argument("Invalid input");
        throw;
    }
    return result;
}

std::pair<QVector < double>, QVector<double>>

s21::Controller::PlotCalculation(
        const DataPlot &data_plot) {
    std::pair<QVector < double>, QVector < double >> castQvector;

    try {
        std::pair<std::vector<double>, std::vector<double>> temp = model_.PlotCalculation(data_plot);
        castQvector.first = QVector<double>(temp.first.begin(), temp.first.end());
        castQvector.second = QVector<double>(temp.second.begin(), temp.second.end());
    } catch (...) {
        throw;
    }

    return castQvector;
}
