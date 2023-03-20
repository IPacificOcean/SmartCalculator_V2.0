//
// Created by Qyburn Bongo on 3/16/23.
//

#ifndef GOOGLE_TESTS_CONTROLLER_H
#define GOOGLE_TESTS_CONTROLLER_H

#include <string>

#include "../model/fasad/model.h"
#include "../model/data/data_credit.h"
#include "../model/data/data_deposit.h"
#include "../model/data/data_plot.h"
#include <QString>
#include <QVector>
#include <vector>

namespace s21 {

    class Controller {
    public:

        /**
         * @brief Calculates a mathematical expression
         * @param expression - a mathematical expression
         * @return calculation result
         */
        double Calculation(QString &expression);


        /**
         * @brief Calculates a mathematical expression for the graph
         * @param data_plot - a class that contains the data for counting
         * @return pair with 2 arrays of coordinates x, y to plot
         */
        std::pair<QVector < double>, QVector<double>> PlotCalculation(
        const DataPlot &data_plot
        );

        /**
         * @brief Calculates loan payments
         * @param data_credit - a structure that contains data on the loan
         * @return structure that contains the data with the credit calculations
         */
        DataCredit &CreditCalculation(DataCredit &data_credit) {
            return model_.CreditCalculation(data_credit);
        }

        /**
         * @brief  Calculates interest on the deposit
         * @param data_deposit - a structure that contains data on the deposit
         * @return structure that contains the data with the deposit calculations
         */
        DataDeposit &DebitCalculation(DataDeposit &data_deposit) {
            return model_.DebitCalculation(data_deposit);
        }

    private:

        Model model_{};
    };

}  // namespace s21


#endif //GOOGLE_TESTS_CONTROLLER_H
