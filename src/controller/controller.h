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
         * @param expression строка с математическим выражением в прямой форме
         * @return результат расчета
         */
        double Calculation(QString &expression);


        /**
         * Выполняет расчет для отрисовки графика
         * @param data_plot класс который содержит данные для рсчета
         * @return пару с 2 векторами координа х, у для построения графика
         */
        std::pair<QVector < double>, QVector<double>> PlotCalculation(
        const DataPlot &data_plot
        );

        /**
         * Расчитывает платеж по кредиту за период
         * @param data_credit
         * @return
         */
        DataCredit& CreditCalculation(DataCredit &data_credit) {
            return model_.CreditCalculation(data_credit);
          }

//        /**
//         * Расчитывает проценты по депозиту
//         * @param data_deposit
//         * @return
//         */
//        DataDeposit DebitCalculation(DataDeposit &data_deposit);

    private:

        Model model_{};
    };

}  // namespace s21


#endif //GOOGLE_TESTS_CONTROLLER_H
