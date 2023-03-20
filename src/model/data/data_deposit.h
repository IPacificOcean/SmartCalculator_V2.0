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
        DataDeposit(double deposit_sum, int deposit_period,
                    PeriodicityPayments payment_frequency,
                    double percent_rate, double tax_rate,
                    Capitalization capitalization,
                    std::vector<double> replenish_accounts,
                    std::vector<double> withdrawals)
                : deposit_sum_(deposit_sum),
                  deposit_period_(deposit_period),
                  payment_frequency(payment_frequency),
                  percent_rate(percent_rate),
                  tax_rate_(tax_rate),
                  capitalization_(capitalization),
                  replenish_accounts_(replenish_accounts),
                  withdrawals_(withdrawals) {}

        // ____INPUT____
        double deposit_sum_{};
        int deposit_period_{};
        PeriodicityPayments payment_frequency =
                ONCE;
        double percent_rate{};
        double tax_rate_{};
        Capitalization capitalization_ = NO;
        std::vector<double> replenish_accounts_{};
        std::vector<double> withdrawals_{};

        // ____OUTPUT____
        double replenishment_amount_{};
        double withdrawal_amount_{};
        double
                total_interest_{};
        double amount_of_tax_{};
        double total_deposit_amount_{};
    };

}  // namespace s21

#endif //GOOGLE_TESTS_DATA_DEPOSIT_H
