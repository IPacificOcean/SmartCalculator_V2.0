#include "credit.h"
#include "ui_credit.h"
#include "calculator.h"
#include <QDebug>

Credit::Credit(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Credit) {
    ui->setupUi(this);
    ui->lineEdit_sum_credit->setValidator(new QDoubleValidator(this));
    ui->lineEdit_limit->setValidator(new QDoubleValidator(this));
    ui->lineEdit_percent->setValidator(new QDoubleValidator(this));
    ui->annuit->setChecked(true);
}

Credit::~Credit() {
    delete ui;
}

void Credit::on_calculate_clicked() {
    // ____INPUT____
    Loan_type l_type = (ui->annuit->isChecked()) ? ANNUITY : DIFFERENTIATED;
    double loan_sum = ui->lineEdit_sum_credit->text().toDouble();
    int period_in_months = ui->lineEdit_limit->text().toInt();
    double percent_rate = ui->lineEdit_percent->text().toDouble();

    ui->listWidget_pay->clear();

    s21::DataCredit data_credit(l_type, loan_sum, period_in_months, percent_rate);

    data_credit = controller_.CreditCalculation(data_credit);

    // ____OUTPUT____
    std::vector<double> output_monthly_payment = data_credit.output_monthly_payment_;
    double output_overpayment_loan = data_credit.output_overpayment_loan_;
    double output_final_payment = data_credit.output_final_payment_;

    // ____SETTING_VALUES____
    ui->lineEdit_total_sum->setText(QString::number(output_final_payment, 'g', 20));
    ui->lineEdit_overpayment->setText(QString::number(output_overpayment_loan, 'g', 20));

    for (int i = 1; i <= period_in_months; i++) {
        ui->listWidget_pay->addItem(
                QString::number(i, 'g', 20) + " month: " + QString::number(output_monthly_payment.at(i - 1), 'g', 20));
    }

}