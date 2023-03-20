
#include "debit_exec.h"

s21::DataDeposit &s21::CalculatorDebit::DebitCalculation(s21::DataDeposit &data_deposit) {
    double part_for_tax{};
    // ____INPUT____
    double &input_contribution_amount = data_deposit.input_contribution_amount_;   // сумма вклада // lineEdit_sum_dep
    int &input_period_of_placement = data_deposit.input_period_of_placement_;     // срок размещения // lineEdit_period
    PeriodicityPayments &input_periodicity_payments = data_deposit.input_periodicity_payments_; // периодичность выплат // comboBox_peiod_of_pay
    double &input_interest_rate = data_deposit.input_interest_rate_;   // процентная ставка // lineEdit_rate
    double &input_tax_rate = data_deposit.input_tax_rate_;  // налоговая ставка // lineEdit_tax
    input_tax_rate = input_tax_rate * 1000000 / 100;
    Capitalization &iput_apitalization = data_deposit.iput_apitalization_; // капитализация // comboBox_capital
    std::vector<double> &input_refills = data_deposit.input_refills_;    // пополнения // listWidget_add
    std::vector<double> &input_withdrawals = data_deposit.input_withdrawals_;  // снятия // listWidget_sub

    // ____OUTPUT____
    double &output_total_refills = data_deposit.output_total_refills_;      // сумма пополнения // lineEdit_add_all // add_all
    double &output_total_withdrawals = data_deposit.output_total_withdrawals_;  // сумма снятия // lineEdit_sub_all // sub_all
    double &output_interest_charges = data_deposit.output_interest_charges_;  // начисленные проценты // lineEdit_percents // percents
    double &output_tax_amount = data_deposit.output_tax_amount_;        // сумма налога // lineEdit_tax_sum // tax_sum
    double &output_total_deposit_amount = data_deposit.output_total_deposit_amount_;  // сумма вклада к концу срока // lineEdit_total_sum_dep // total

    // ____CALCULATION____
    for (auto refill: input_refills) {
        output_total_refills += refill;
    }
    input_contribution_amount += output_total_refills;

    for (auto withdrawal: input_withdrawals) {
        output_total_withdrawals += withdrawal;
    }
    input_contribution_amount -= output_total_withdrawals;

    if (iput_apitalization == MONTHLY_CAP) {
        output_interest_charges =
                (input_contribution_amount * pow((1 + (input_interest_rate / 100) / 12), input_period_of_placement)) -
                input_contribution_amount;
    } else {
        output_interest_charges =
                (input_contribution_amount * input_interest_rate * input_period_of_placement * AVERAGE_DAYS_IN_MONTH /
                 365) / 100;
    }
    part_for_tax = output_interest_charges - input_tax_rate;

    if (part_for_tax > 0 && input_tax_rate) {
        output_tax_amount = part_for_tax * NDFL;
    } else {
        output_tax_amount = 0;
    }

    if (input_periodicity_payments == MONTHLY) {
        output_total_deposit_amount = input_contribution_amount;
    } else {
        output_total_deposit_amount = input_contribution_amount + output_interest_charges - output_tax_amount;
    }

    output_total_deposit_amount = round(output_total_deposit_amount);
    output_interest_charges = round(output_interest_charges);

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


