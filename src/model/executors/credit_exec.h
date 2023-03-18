#ifndef CREDIT_EXEC_H
#define CREDIT_EXEC_H

//#include <QDialog>

#include "../data/data_credit.h"
#include <cmath>

constexpr double AVERAGE_DAYS_IN_MONTH = 30.416666666666667851;


namespace s21 {

class CalculatorCredit {
 public:
  DataCredit& CreditCalculation(DataCredit &data_credit) {
    double coefficient{}, pay_per_months{}, common_pay_per_months{};

    // ____INPUT____
    TypeOfCredit &input_type_of_credit = data_credit.input_type_of_credit_;
    double &input_total_credit = data_credit.input_total_credit_; // sum
    int &input_term_in_months = data_credit.input_term_in_months_; // months
    double &input_interest_rate = data_credit.input_interest_rate_ ; // rate / 12 / 100;
    // ____OUTPUT____
    double& output_overpayment_loan = data_credit.output_overpayment_loan_; // lineEdit_overpayment
    double& output_final_payment = data_credit.output_final_payment_; // total
    std::vector<double>& output_monthly_payment = data_credit.output_monthly_payment_;

    if (input_type_of_credit == ANNUITY) {
      input_interest_rate = input_interest_rate / 12 / 100;
      coefficient = input_interest_rate * pow((1 + input_interest_rate), input_term_in_months) / (pow((1 + input_interest_rate), input_term_in_months) - 1);
      pay_per_months = coefficient * input_total_credit;
      output_final_payment = pay_per_months * input_term_in_months;
      output_final_payment = round(output_final_payment);
      pay_per_months = round(pay_per_months);
      output_overpayment_loan = output_final_payment - input_total_credit;
      for(int i = 0; i < input_term_in_months; ++i) {
        output_monthly_payment.push_back(pay_per_months);
      }
    } else if (input_type_of_credit == DIFFERENTIATED) {
      pay_per_months = input_total_credit / input_term_in_months;
      double tmp = input_total_credit;

      for(int i = 0; i < input_term_in_months; ++i) {
        common_pay_per_months = pay_per_months + (tmp * input_interest_rate / 100 * AVERAGE_DAYS_IN_MONTH / 365);
        common_pay_per_months = round(common_pay_per_months);
        output_monthly_payment.push_back(common_pay_per_months);
        tmp -= pay_per_months;
        output_final_payment += common_pay_per_months;
      }
      output_final_payment = round(output_final_payment);
      output_overpayment_loan = output_final_payment - input_total_credit;
    }
    return data_credit;
  }

};

}  // namespace s21

#endif // CREDIT_EXEC_H
