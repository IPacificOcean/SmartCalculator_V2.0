#ifndef DEBIT_EXEC_H
#define DEBIT_EXEC_H

#include <cmath>

#include "../data/data_deposit.h"
#include "credit_exec.h"

constexpr double AVERAGE_DAYS = 30.416666666666667851;
constexpr double NDFL = 13.00 / 100.00;

namespace s21 {

class CalculatorDebit {
 public:
  DataDeposit &DebitCalculation(DataDeposit &data_deposit);
};
}  // namespace s21
#endif  // DEBIT_EXEC_H
