//
// Created by Qyburn Bongo on 3/16/23.
//

#ifndef GOOGLE_TESTS_MODEL_H
#define GOOGLE_TESTS_MODEL_H


#include <list>
#include <queue>
#include <string>
#include <vector>

#include "../data/data_credit.h"
#include "../data/data_deposit.h"
#include "../data/data_plot.h"
#include "../executors/calculator_exec.h"
#include "../executors/plot.h"
#include "../executors/parser.h"
#include "../executors/validator.h"
#include "../executors/credit_exec.h"

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
         * @brief Calculates a mathematical expression for the graph
         * @param data_plot - a class that contains the data for counting
         * @return pair with 2 arrays of coordinates x, y to plot
         */
        std::pair<std::vector<double>, std::vector<double>> PlotCalculation(
                const DataPlot &data_plot);

        /**
         * @brief Calculates loan payments
         * @param data_credit - a structure that contains data on the loan
         * @return structure that contains the data with the credit calculations
         */
        DataCredit &CreditCalculation(DataCredit &data_credit) {
            return calculator_credit_.CreditCalculation(data_credit);
        }

//        DataDeposit DebitCalculation(DataDeposit &data_deposit);

    private:
        Validator validator_;
        Parser parser_;
        s21::Calculator calculator_;
        CalculatorPlot calculator_plot_;
        CalculatorCredit calculator_credit_;
    };

}  // namespace s21


#endif //GOOGLE_TESTS_MODEL_H
