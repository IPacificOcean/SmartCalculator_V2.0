#ifndef CREDIT_EXEC_H
#define CREDIT_EXEC_H

#include "../data/data_credit.h"
#include <cmath>

constexpr double AVERAGE_DAYS_IN_MONTH = 30.416666666666667851;


namespace s21 {

class CalculatorCredit {
 public:
    DataCredit& CreditCalculation(DataCredit &data_credit);

};

}  // namespace s21

#endif // CREDIT_EXEC_H
