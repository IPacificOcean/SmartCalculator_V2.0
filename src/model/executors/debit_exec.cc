
#include "debit_exec.h"

s21::DataDeposit &s21::CalculatorDebit::DebitCalculation(s21::DataDeposit &data_deposit) {
    double part_for_tax{};
    // ____INPUT____
    double &deposit_sum = data_deposit.deposit_sum_;
    int &deposit_period = data_deposit.deposit_period_;
    PeriodicityPayments &payment_frequency = data_deposit.payment_frequency;
    double &percent_rate = data_deposit.percent_rate;
    double &tax_rate = data_deposit.tax_rate_;
    tax_rate = tax_rate * 1000000 / 100;
    Capitalization &capitalization = data_deposit.capitalization_;
    std::vector<double> &replenish_accounts = data_deposit.replenish_accounts_;
    std::vector<double> &withdrawals = data_deposit.withdrawals_;

    // ____OUTPUT____
    double &replenishment_amount = data_deposit.replenishment_amount_;
    double &withdrawal_amount = data_deposit.withdrawal_amount_;
    double &total_interest = data_deposit.total_interest_;
    double &amount_of_tax = data_deposit.amount_of_tax_;
    double &total_deposit_amount = data_deposit.total_deposit_amount_;

    // ____CALCULATION____
    for (auto refill: replenish_accounts) {
        replenishment_amount += refill;
    }
    deposit_sum += replenishment_amount;

    for (auto withdrawal: withdrawals) {
        withdrawal_amount += withdrawal;
    }
    deposit_sum -= withdrawal_amount;

    if (capitalization == MONTHLY_CAP) {
        total_interest =
                (deposit_sum * pow((1 + (percent_rate / 100) / 12), deposit_period)) -
                deposit_sum;
    } else {
        total_interest =
                (deposit_sum * percent_rate * deposit_period * AVERAGE_DAYS_IN_MONTH /
                 365) / 100;
    }
    part_for_tax = total_interest - tax_rate;

    if (part_for_tax > 0 && tax_rate) {
        amount_of_tax = part_for_tax * NDFL;
    } else {
        amount_of_tax = 0;
    }

    if (payment_frequency == MONTHLY) {
        total_deposit_amount = deposit_sum;
    } else {
        total_deposit_amount = deposit_sum + total_interest - amount_of_tax;
    }

    total_deposit_amount = round(total_deposit_amount);
    total_interest = round(total_interest);

    return data_deposit;
}

/* Ежемесячная капитализация
Когда банк суммирует доход по депозиту раз в месяц, расчет ведется по формуле:
Дв = Р * (1 + N/12)^T

где:

Дв — итоговый доход, то есть размер вклада на конец срока включая сумму открытия и начисленный процент,
P — начальный депозит,
N — годовая ставка, разделенная на 100,
T — срок договора в месяцах.

Рассчитаем итоговую сумму с теми же исходными данными:
350000*(1+0.047/12)^9 = 362532.56
///////////////////////////////////

Расчет простых процентов
Выяснив годовую ставку, периоды и виды начисления процентов, можно посчитать доход по вкладу.
Простые проценты начисляются по следующей формуле:
S = (P*I*T/K)/100

где:

S — выплаченные проценты,
P — первоначальная сумма вложений,
I — годовая ставка,
T — количество дней вклада,
K — количество дней в году — 365 или 366.

Если вкладчик открыл депозит на 350 000 руб. сроком на 9 месяцев под 4,7%, процентный доход по вкладу составит:

(350000*4.7*273/365)/100 = 12303,7 (сумма может отличаться в зависимости от кол-ва дней в месяце)
*/
