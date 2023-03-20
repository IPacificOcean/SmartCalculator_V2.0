#include "debit.h"
#include "ui_debit.h"
#include "calculator.h"
#include <QDebug>

debit::debit(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::debit) {
    ui->setupUi(this);
    ui->lineEdit_sum_dep->setValidator(new QDoubleValidator(this));
    ui->lineEdit_period->setValidator(new QDoubleValidator(this));
    ui->lineEdit_rate->setValidator(new QDoubleValidator(this));
    ui->lineEdit_tax->setValidator(new QDoubleValidator(this));
    ui->lineEdit_add->setValidator(new QDoubleValidator(this));
    ui->lineEdit_del->setValidator(new QDoubleValidator(this));
    ui->lineEdit_add_all->setValidator(new QDoubleValidator(this));
    ui->lineEdit_sub_all->setValidator(new QDoubleValidator(this));


}

debit::~debit() {
    delete ui;
}

void debit::on_pushButton_calculate_clicked() {
    // ____INPUT____
    double input_contribution_amount = ui->lineEdit_sum_dep->text().toDouble();   // сумма вклада // lineEdit_sum_dep
    int input_period_of_placement = ui->lineEdit_period->text().toDouble();     // срок размещения // lineEdit_period
    PeriodicityPayments input_periodicity_payments = (ui->comboBox_peiod_of_pay->currentText() == "Ежемесячно")
                                                     ? MONTHLY : ONCE; // периодичность выплат // comboBox_peiod_of_pay
    double input_interest_rate = ui->lineEdit_rate->text().toDouble();   // процентная ставка // lineEdit_rate
    double input_tax_rate = ui->lineEdit_tax->text().toDouble();  // налоговая ставка // lineEdit_tax // * 1000000 / 100

    Capitalization iput_apitalization = (ui->comboBox_capital->currentText() == "Ежемесячно") ? MONTHLY_CAP
                                                                                              : NO; // капитализация // comboBox_capital

    std::vector<double> input_refills{};    // пополнения // listWidget_add
    while (ui->listWidget_add->count() != 0) {
        input_refills.push_back(on_pushButton_del_clicked());
    }

    std::vector<double> input_withdrawals{};  // снятия // listWidget_sub
    while (ui->listWidget_sub->count() != 0) {
        input_withdrawals.push_back(on_pushButton_del_2_clicked());
    }

    // ____CALCULATION____
    s21::DataDeposit data_deposit(input_contribution_amount,
                                  input_period_of_placement,
                                  input_periodicity_payments,
                                  input_interest_rate,
                                  input_tax_rate,
                                  iput_apitalization,
                                  input_refills,
                                  input_withdrawals);

    data_deposit = controller_.DebitCalculation(data_deposit);

    // ____OUTPUT____
    double &output_total_refills = data_deposit.output_total_refills_;      // сумма пополнения // lineEdit_add_all // add_all
    double &output_total_withdrawals = data_deposit.output_total_withdrawals_;  // сумма снятия // lineEdit_sub_all // sub_all
    double &output_interest_charges = data_deposit.output_interest_charges_;  // начисленные проценты // lineEdit_percents // percents
    double &output_tax_amount = data_deposit.output_tax_amount_;        // сумма налога // lineEdit_tax_sum // tax_sum
    double &output_total_deposit_amount = data_deposit.output_total_deposit_amount_;  // сумма вклада к концу срока // lineEdit_total_sum_dep // total


    // ____SETTING_VALUES____
    ui->lineEdit_add_all->setText(QString::number(output_total_refills));
    ui->lineEdit_sub_all->setText(QString::number(output_total_withdrawals));

    ui->lineEdit_add->setText("0");
    ui->lineEdit_del->setText("0");

    ui->lineEdit_total_sum_dep->setText(QString::number(output_total_deposit_amount, 'g', 20));
    ui->lineEdit_percents->setText(QString::number(output_interest_charges, 'g', 20));
    ui->lineEdit_tax_sum->setText(QString::number(output_tax_amount));
}

double debit::on_pushButton_del_clicked() {
    QString line = "";
    if (ui->listWidget_add->count() != 0) {
        line = ui->listWidget_add->takeItem(ui->listWidget_add->count() - 1)->text();
    }
    return line.toDouble();
}

void debit::on_pushButton_add_clicked() {
    QString line;
    line = ui->lineEdit_add->text();
    ui->listWidget_add->addItem(line);
}

double debit::on_pushButton_del_2_clicked() {
    QString line = "";
    if (ui->listWidget_sub->count() != 0) {
        line = ui->listWidget_sub->takeItem(ui->listWidget_sub->count() - 1)->text();
    }
    return line.toDouble();
}

void debit::on_pushButton_add_2_clicked() {
    QString line;
    line = ui->lineEdit_del->text();
    ui->listWidget_sub->addItem(line);
}

