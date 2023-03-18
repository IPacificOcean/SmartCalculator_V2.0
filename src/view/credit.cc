#include "credit.h"
#include "ui_secondwindow.h"
#include "calculator.h"
#include <QDebug>

Credit::Credit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Credit)
{
    ui->setupUi(this);
    ui->lineEdit_sum_credit->setValidator(new QDoubleValidator(this));
    ui->lineEdit_limit->setValidator(new QDoubleValidator(this));
    ui->lineEdit_percent->setValidator(new QDoubleValidator(this));
    ui->annuit->setChecked(true);
}

Credit::~Credit()
{
    delete ui;
}

void Credit::on_calculate_clicked()
{
    QString line, count;
    double rate, coeff, sum, months, pay_per_months, total = 0.0, common_pay_per_months;
    months = ui->lineEdit_limit->text().toDouble();
    sum = ui->lineEdit_sum_credit->text().toDouble();
    ui->listWidget_pay->clear();
    if (ui->annuit->isChecked()) {
        rate = ui->lineEdit_percent->text().toDouble() / 12 / 100;
        coeff = rate * pow((1 + rate), months) / (pow((1 + rate), months) - 1);
        pay_per_months = coeff * sum;
        total = pay_per_months * months;
        total = round(total);
        pay_per_months = round(pay_per_months);
        line = QString::number(total, 'g', 20);
        ui->lineEdit_total_sum->setText(line);
        line = QString::number(total - sum, 'g', 20);
        ui->lineEdit_overpayment->setText(line);
        line = QString::number(pay_per_months, 'g', 20);
        for(int i = 1; i <= (int)months; i++) {
           count =QString::number(i, 'g', 20);
           ui->listWidget_pay->addItem(count  + " month: " + line);
        }
    } else if (ui->diff->isChecked()) {
        pay_per_months = sum / months;
        double tmp = sum;
        rate = ui->lineEdit_percent->text().toDouble();
        for(int i = 1; i <= (int)months; i++) {
            common_pay_per_months = pay_per_months + (tmp * rate / 100 * AVERAGE_DAYS_IN_MONTH / 365);
            count =QString::number(i, 'g', 20);
            common_pay_per_months = round(common_pay_per_months);
            line = QString::number(common_pay_per_months, 'g', 20);
            ui->listWidget_pay->addItem(count  + " month: " + line);
            tmp -= pay_per_months;
            total += common_pay_per_months;
        }
        total = round(total);
        line = QString::number(total, 'g', 20);
        ui->lineEdit_total_sum->setText(line);
        line = QString::number(total - sum, 'g', 20);
        ui->lineEdit_overpayment->setText(line);
    }


//    qDebug()<<coeff;
//    qDebug()<<pay_per_months;
//    qDebug()<<total;
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

