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

namespace s21 {

    class Model {
    public:
//        /**
//         * calculates an expression
//         * @param expression string with a mathematical expression
//         * @return calculation result
//         */
        double Calculation(std::string &expression) {
            if (validator_.IsNotValid(expression)) {
                throw std::invalid_argument("Invalid input");
            }

            std::list<std::string> queueRpn = parser_.GetRpn(expression);

            double result{};
            try {
                result = calculator_.Calculate(queueRpn);
            } catch (...) {
                throw std::invalid_argument("Calculation error");
            }
            return result;
        }

////        double Calculation(std::string &expression, double &x) { return 0; }

//        /**
//         *
//         * @param data_plot
//         * @return
//         */
//        std::pair<std::vector<double>, std::vector<double>> PlotCalculation(
//                const DataPlot &data_plot) {
//            if (validator_.IsNotValid(data_plot.expression_)) {
//                throw std::invalid_argument("Invalid input");
//            }

//            std::list<std::string> rpn_expression =
//                    parser_.GetRpn(data_plot.expression_);

//            std::pair<std::vector<double>, std::vector<double>> res;

//            try {
//                res = calculator_plot_.PlotCalculation(data_plot, rpn_expression);
//            } catch (...) {
//                throw;
//            }

//            return res;
//        }

//        DataCredit CreditCalculation(DataCredit &data_credit);

//        DataDeposit DebitCalculation(DataDeposit &data_deposit);

    private:
        Validator validator_;
        Parser parser_;
        Calculator calculator_;
//        CalculatorPlot calculator_plot_;
    };

}  // namespace s21


#endif //GOOGLE_TESTS_MODEL_H
