//
// Created by Qyburn Bongo on 3/16/23.
//

#ifndef GOOGLE_TESTS_MODEL_H
#define GOOGLE_TESTS_MODEL_H


#include <list>
#include <queue>
#include <string>
#include <vector>
#include <utility>
#include <QDebug>

#include "../data/data_credit.h"
#include "../data/data_deposit.h"
#include "../data/data_plot.h"
#include "../executors/calculator_exec.h"
#include "../executors/plot.h"
#include "../executors/parser.h"
#include "../executors/validator.h"

namespace s21 {

    class Model {
    public:
        /**
         * @brief calculates an expression
         * @param expression string with a mathematical expression
         * @return calculation result
         */
        double Calculation(std::string &expression);

        /**
         *
         * @param data_plot
         * @return
         */
        std::pair<std::vector<double>, std::vector<double>> PlotCalculation(
                const DataPlot &data_plot);

//        DataCredit CreditCalculation(DataCredit &data_credit);

//        DataDeposit DebitCalculation(DataDeposit &data_deposit);

    private:
        Validator validator_;
        Parser parser_;
        Calculator calculator_;
        CalculatorPlot calculator_plot_;
    };

}  // namespace s21


#endif //GOOGLE_TESTS_MODEL_H
