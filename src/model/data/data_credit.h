//
// Created by Qyburn Bongo on 3/16/23.
//

#ifndef GOOGLE_TESTS_DATA_CREDIT_H
#define GOOGLE_TESTS_DATA_CREDIT_H

#include <vector>

enum TypeOfCredit { ANNUITY, DIFFERENTIATED };

namespace s21 {

struct DataCredit {
  DataCredit(TypeOfCredit input_type_of_credit, double input_total_credit,
             int input_term_in_months, double input_interest_rate)
      : input_type_of_credit_(input_type_of_credit),
        input_total_credit_(input_total_credit),
        input_term_in_months_(input_term_in_months),
        input_interest_rate_(input_interest_rate) {}

  // ____INPUT____
  TypeOfCredit input_type_of_credit_ = ANNUITY;
  double input_total_credit_{};
  int input_term_in_months_{};
  double input_interest_rate_{};
  // ____OUTPUT____
  std::vector<double> output_monthly_payment_{};
  double output_overpayment_loan_{};
  double output_final_payment_{};
};

}  // namespace s21

#endif //GOOGLE_TESTS_DATA_CREDIT_H
