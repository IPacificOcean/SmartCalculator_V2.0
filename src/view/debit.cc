#include "debit.h"

#include <QDebug>

#include "calculator.h"
#include "ui_debit.h"

debit::debit(QWidget *parent) : QDialog(parent), ui(new Ui::debit) {
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

debit::~debit() { delete ui; }

void debit::on_pushButton_calculate_clicked() {
  // ____INPUT____
  double deposit_sum = ui->lineEdit_sum_dep->text().toDouble();
  int deposit_period = ui->lineEdit_period->text().toDouble();
  PeriodicityPayments payment_frequency =
      (ui->comboBox_peiod_of_pay->currentText() == "Ежемесячно") ? MONTHLY
                                                                 : ONCE;
  double percent_rate = ui->lineEdit_rate->text().toDouble();
  double tax_rate = ui->lineEdit_tax->text().toDouble();

  Capitalization capitalization =
      (ui->comboBox_capital->currentText() == "Ежемесячно") ? MONTHLY_CAP : NO;

  std::vector<double> replenish_accounts{};
  while (ui->listWidget_add->count() != 0) {
    replenish_accounts.push_back(on_pushButton_del_clicked());
  }

  std::vector<double> withdrawals{};
  while (ui->listWidget_sub->count() != 0) {
    withdrawals.push_back(on_pushButton_del_2_clicked());
  }

  // ____CALCULATION____
  s21::DataDeposit data_deposit(deposit_sum, deposit_period, payment_frequency,
                                percent_rate, tax_rate, capitalization,
                                replenish_accounts, withdrawals);

  data_deposit = controller_.DebitCalculation(data_deposit);

  // ____OUTPUT____
  double &replenishment_amount = data_deposit.replenishment_amount_;
  double &withdrawal_amount = data_deposit.withdrawal_amount_;
  double &total_interest = data_deposit.total_interest_;
  double &amount_of_tax = data_deposit.amount_of_tax_;
  double &total_deposit_amount = data_deposit.total_deposit_amount_;

  // ____SETTING_VALUES____
  ui->lineEdit_add_all->setText(QString::number(replenishment_amount));
  ui->lineEdit_sub_all->setText(QString::number(withdrawal_amount));

  ui->lineEdit_add->setText("0");
  ui->lineEdit_del->setText("0");

  ui->lineEdit_total_sum_dep->setText(
      QString::number(total_deposit_amount, 'g', 20));
  ui->lineEdit_percents->setText(QString::number(total_interest, 'g', 20));
  ui->lineEdit_tax_sum->setText(QString::number(amount_of_tax));
}

double debit::on_pushButton_del_clicked() {
  QString line = "";
  if (ui->listWidget_add->count() != 0) {
    line =
        ui->listWidget_add->takeItem(ui->listWidget_add->count() - 1)->text();
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
    line =
        ui->listWidget_sub->takeItem(ui->listWidget_sub->count() - 1)->text();
  }
  return line.toDouble();
}

void debit::on_pushButton_add_2_clicked() {
  QString line;
  line = ui->lineEdit_del->text();
  ui->listWidget_sub->addItem(line);
}
