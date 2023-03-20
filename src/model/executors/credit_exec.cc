
#include "credit_exec.h"


s21::DataCredit &s21::CalculatorCredit::CreditCalculation(s21::DataCredit &data_credit) {
    double coefficient{}, pay_per_months{}, common_pay_per_months{};

    // ____INPUT____
    Loan_type &l_type = data_credit.l_type_;
    double &loan_sum = data_credit.loan_sum_;
    int &period_in_months = data_credit.period_in_months_;
    double &percent_rate = data_credit.percent_rate_;
    // ____OUTPUT____
    double &output_overpayment_loan = data_credit.output_overpayment_loan_;
    double &output_final_payment = data_credit.output_final_payment_;
    std::vector<double> &output_monthly_payment = data_credit.output_monthly_payment_;

    if (l_type == ANNUITY) {
        percent_rate = percent_rate / 12 / 100;
        coefficient = percent_rate * pow((1 + percent_rate), period_in_months) /
                      (pow((1 + percent_rate), period_in_months) - 1);
        pay_per_months = coefficient * loan_sum;
        output_final_payment = pay_per_months * period_in_months;
        output_final_payment = round(output_final_payment);
        pay_per_months = round(pay_per_months);
        output_overpayment_loan = output_final_payment - loan_sum;
        for (int i = 0; i < period_in_months; ++i) {
            output_monthly_payment.push_back(pay_per_months);
        }
    } else if (l_type == DIFFERENTIATED) {
        pay_per_months = loan_sum / period_in_months;
        double tmp = loan_sum;

        for (int i = 0; i < period_in_months; ++i) {
            common_pay_per_months = pay_per_months + (tmp * percent_rate / 100 * AVERAGE_DAYS_IN_MONTH / 365);
            common_pay_per_months = round(common_pay_per_months);
            output_monthly_payment.push_back(common_pay_per_months);
            tmp -= pay_per_months;
            output_final_payment += common_pay_per_months;
        }
        output_final_payment = round(output_final_payment);
        output_overpayment_loan = output_final_payment - loan_sum;
    }
    return data_credit;
}


/*

Дифференцированный платеж — это система погашения кредита, при которой заемщик ежемесячно вносит разные суммы, размер которых с каждым разом уменьшается.

Пример расчета: сумма кредита — 300 000 рублей, срок кредита — 6 месяцев, ставка по кредиту — 20%. Погашение кредита осуществляется дифференцированными платежами:

1. Ежемесячный платеж по основному долгу = сумма кредита / количество платежных периодов в течение всего срока кредита.

300 000 рублей / 6 месяцев = 50 000 рублей.

2. Ежемесячная сумма начисленных процентов по кредиту = остаток основного долга в текущем периоде * годовая процентная ставка * число дней в платежном периоде (от 28 до 31) / число дней в году (365 или 366).

1-й месяц = 300 000 рублей*20%*31/365=5 095,89 рубля.

2-й месяц = 250 000 рублей*20%*31/365=4 246,58 рубля.

3-й месяц = 200 000 рублей*20%*30/365=3 287,67 рубля.

4-й месяц = 150 000 рублей*20%*31/365=2547,95 рубля.

5-й месяц = 100 000 рублей*20%*30/365=1643,84 рубля.

6-й месяц = 50 000 рублей*20%*31/365=849,32 рубля.

3. Ежемесячный платеж по кредиту = ежемесячный платеж по основному долгу + ежемесячная сумма начисленных процентов по кредиту.

1-й месяц = 50 000 рублей+5 095,89 рубля=55 095,89 рубля.

2-й месяц = 50 000 рублей+4 246,58 рубля=54 246,58 рубля.

3-й месяц = 50 000 рублей+3 287,67 рубля=53 287,67 рубля.

4-й месяц = 50 000 рублей+2 547,95 рубля=52 547,95 рубля.

5-й месяц = 50 000 рублей+1 643,84 рубля=51 643,84 рубля.

6-й месяц = 50 000 рублей+849,32 рубля=50 849,32 рубля.

Итого платежи по кредиту составили 317 671,25 рубля.

////////////////////////////
Пример расчета аннуитетного платежа (расчеты лучше производить в Microsoft Excel, также можно воспользоваться функцией ПЛТ).

Условие: сумма кредита — 1 000 000 рублей, срок — три года (36 месяцев), ставка — 20%. Погашение осуществляется аннуитетными платежами.

1. Ставка по кредиту в месяц = годовая процентная ставка / 12 месяцев 20%/12 месяцев/100 = 0,0166666666666667

2. Коэффициент аннуитета = (0,0166666666666667*(1+0,0166666666666667)^36/((1+0,0166666666666667)^36—1)=0,0371635833597405

3. Ежемесячный аннуитетный платеж = 0,0371635833597405*1 000 000 рублей = 37 164 рублей

4. Итого переплата по кредиту составила 337 889 рублей

При погашении данного кредита дифференцированными платежами сумма уплаченных процентов по нему составила бы 308 915 рублей
*/


