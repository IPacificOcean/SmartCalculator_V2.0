#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <qvector.h>
#include <string.h>

#define AVERAGE_DAYS_IN_MONTH 30.416666666666667851
#define NDFL 13/100

extern "C" {
#include "../../s21_smart_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void func_exp();
    void digit_nambers();
    void on_pushButton_eq_clicked();
    void on_pushButton_del_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_graph_clicked();
    double doubleSpinBox_Xmax();
    double doubleSpinBox_Xmin();


    void on_pushButton_credit_clicked();

    void on_pushButton_debit_clicked();

private:
    Ui::Calculator *ui;
    double xBegin, xEnd, h, X, Y;
    int N;

    QVector<double> x,y;



signals:
//    void signal(QString);
};
#endif // CALCULATOR_H
