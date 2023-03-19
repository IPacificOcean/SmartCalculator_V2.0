//
// Created by Qyburn Bongo on 3/16/23.
//

#ifndef GOOGLE_TESTS_DATA_CREDIT_H
#define GOOGLE_TESTS_DATA_CREDIT_H

#include <vector>

enum Loan_type {
    ANNUITY, DIFFERENTIATED
};

namespace s21 {

    struct DataCredit {
        DataCredit(Loan_type l_type, double loan_sum,
                   int period_in_months, double percent_rate)
                : l_type_(l_type),
                  loan_sum_(loan_sum),
                  period_in_months_(period_in_months),
                  percent_rate_(percent_rate) {}

        Loan_type l_type_ = ANNUITY;
        double loan_sum_{};
        int period_in_months_{};
        double percent_rate_{};

        std::vector<double> output_monthly_payment_{};
        double output_overpayment_loan_{};
        double output_final_payment_{};
    };

}  // namespace s21

#endif //GOOGLE_TESTS_DATA_CREDIT_H
