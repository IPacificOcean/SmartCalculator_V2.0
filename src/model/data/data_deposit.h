//
// Created by Qyburn Bongo on 3/16/23.
//

#ifndef GOOGLE_TESTS_DATA_DEPOSIT_H
#define GOOGLE_TESTS_DATA_DEPOSIT_H

#include <vector>

enum PeriodicityPayments {
    ONCE, MONTHLY
};
enum Capitalization {
    NO, MONTHLY_CAP
};

namespace s21 {
    struct DataDeposit {
        DataDeposit(double input_contribution_amount, int input_period_of_placement,
                    PeriodicityPayments input_periodicity_payments,
                    double input_interest_rate, double input_tax_rate,
                    Capitalization iput_apitalization,
                    std::vector<double> input_refills,
                    std::vector<double> input_withdrawals)
                : input_contribution_amount_(input_contribution_amount),
                  input_period_of_placement_(input_period_of_placement),
                  input_periodicity_payments_(input_periodicity_payments),
                  input_interest_rate_(input_interest_rate),
                  input_tax_rate_(input_tax_rate),
                  iput_apitalization_(iput_apitalization),
                  input_refills_(input_refills),
                  input_withdrawals_(input_withdrawals) {}

        // ____INPUT____
        double input_contribution_amount_{};  // сумма вклада // lineEdit_sum_dep
        int input_period_of_placement_{};  // срок размещения // lineEdit_period
        PeriodicityPayments input_periodicity_payments_ =
                ONCE;  // периодичность выплат // comboBox_peiod_of_pay
        double input_interest_rate_{};  // процентная ставка // lineEdit_rate
        double input_tax_rate_{};  // налоговая ставка // lineEdit_tax
        Capitalization iput_apitalization_ = NO;  // капитализация // comboBox_capital
        std::vector<double> input_refills_{};  // пополнения // listWidget_add
        std::vector<double> input_withdrawals_{};  // снятия // listWidget_sub

        // ____OUTPUT____
        double output_total_refills_{};  // сумма пополнения // lineEdit_add_all
        double output_total_withdrawals_{};  // сумма снятия // lineEdit_sub_all
        double
                output_interest_charges_{};  // начисленные проценты // lineEdit_percents
        double output_tax_amount_{};  // сумма налога // lineEdit_tax_sum
        double output_total_deposit_amount_{};  // сумма вклада к концу срока //
        // lineEdit_total_sum_dep
    };

}  // namespace s21

#endif //GOOGLE_TESTS_DATA_DEPOSIT_H
