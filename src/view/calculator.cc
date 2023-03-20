#include "calculator.h"
#include "ui_calculator.h"
#include <QMessageBox>
#include <QDebug>
#include <QChar>
#include <cctype>
#include <stdexcept>
#include "credit.h"
#include "debit.h"


Calculator::Calculator(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::Calculator) {
    ui->setupUi(this);

    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(func_exp()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(func_exp()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(func_exp()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(func_exp()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(func_exp()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(func_exp()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(func_exp()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(func_exp()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(func_exp()));

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_brck_op, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_brck_cl, SIGNAL(clicked()), this, SLOT(digit_nambers()));
    connect(ui->pushButton_var_x, SIGNAL(clicked()), this, SLOT(digit_nambers()));

//    connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(on_pushButton_del_clicked()));

}

Calculator::~Calculator() {
    delete ui;
}

void Calculator::func_exp() {
    QPushButton *button = (QPushButton *) sender();
    QString new_label;
    new_label = (ui->lineEdit->text() + button->text());
    ui->lineEdit->setText(new_label + '(');
}

void Calculator::digit_nambers() {
    QPushButton *button = (QPushButton *) sender();
    QString new_label;
    new_label = (ui->lineEdit->text() + button->text());
    ui->lineEdit->setText(new_label);
}


void Calculator::on_pushButton_eq_clicked() {
    double res = 0;
    QString inputStr = ui->lineEdit->text();

    try {
        res = controller.Calculation(inputStr);
        inputStr = QString::number(res, 'g', 15);
        ui->lineEdit->setText(inputStr);
    } catch (std::exception &e) {
        QString error(e.what());
        ui->lineEdit->setText(e.what());
    }
}


void Calculator::on_pushButton_del_clicked() {
    ui->lineEdit->clear();
    ui->widget->clearGraphs();
//    x.clear();
//    y.clear();
    ui->widget->replot();

}


void Calculator::on_pushButton_clear_clicked() {
    if (!ui->lineEdit->text().isEmpty()) {
        QString value = ui->lineEdit->text();

        if (((value.data()[value.size() - 1]) == '(') && ((value.data()[value.size() - 2]).isLetter())) {
            if ((value.data()[value.size() - 3]) == 'l') {
                value.chop(3);
            } else if ((value.data()[value.size() - 5]).isLetter()) {
                value.chop(5);
            } else {
                value.chop(4);
            }
        } else if (value.back() == 'd') {
            value.chop(3);
        } else {
            value.chop(1);
        }
        ui->lineEdit->setText(value);
    }
}

double Calculator::doubleSpinBox_Xmax() {
    return ui->doubleSpinBox_Xmax->text().toDouble();
}

double Calculator::doubleSpinBox_Xmin() {
    return ui->doubleSpinBox_Xmin->text().toDouble();
}


void Calculator::on_pushButton_graph_clicked() {
    if (!ui->lineEdit->text().isEmpty()) {
        ui->widget->clearGraphs();
        xBegin = doubleSpinBox_Xmin();
        xEnd = doubleSpinBox_Xmax();
        s21::DataPlot data_plot_input(ui->lineEdit->text().toStdString(), xBegin, xEnd);
        std::pair<QVector<double>, QVector<double>> data_plot;

        ui->widget->xAxis->setRange(data_plot_input.x_begin_, data_plot_input.x_end_);
        ui->widget->yAxis->setRange(data_plot_input.x_begin_, data_plot_input.x_end_);
//     ui->widget->yAxis->setRange(ui->lineEdit_y_min->text().toDouble(), ui->lineEdit_y_max->text().toDouble());
        try {
            data_plot = controller.PlotCalculation(data_plot_input);
            ui->widget->addGraph();
//            ui->widget->graph(0)->setData(data_plot.first, data_plot.second);
            ui->widget->graph(0)->setPen(QColor(127, 127, 255, 127));
            ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
            ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
            ui->widget->addGraph();
            ui->widget->graph(0)->addData(data_plot.first, data_plot.second);
            ui->widget->replot();
        } catch (std::exception &e) {
            ui->lineEdit->setText(e.what());
        }
    }
}


void Calculator::on_pushButton_credit_clicked() {
    Credit window;
    window.setModal(true);
    window.setWindowTitle("Credit");
    window.exec();
}


void Calculator::on_pushButton_debit_clicked() {
    debit window;
    window.setModal(true);
    window.setWindowTitle("Debit");
    window.exec();
}

//qDebug()<<xEnd;
