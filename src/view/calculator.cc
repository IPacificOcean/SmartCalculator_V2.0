#include "calculator.h"
#include "ui_calculator.h"
#include <QMessageBox>
#include <QDebug>
#include "credit.h"
#include "debit.h"


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

//    form = new Formplot;
//    form->show();
//    connect(this, &MainWindow::signal, form, &Formplot::slot);

    connect(ui->pushButton_sin,SIGNAL(clicked()),this,SLOT(func_exp()));
    connect(ui->pushButton_cos,SIGNAL(clicked()),this,SLOT(func_exp()));
    connect(ui->pushButton_tan,SIGNAL(clicked()),this,SLOT(func_exp()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()),this,SLOT(func_exp()));
    connect(ui->pushButton_asin,SIGNAL(clicked()),this,SLOT(func_exp()));
    connect(ui->pushButton_acos,SIGNAL(clicked()),this,SLOT(func_exp()));
    connect(ui->pushButton_atan,SIGNAL(clicked()),this,SLOT(func_exp()));
    connect(ui->pushButton_ln,SIGNAL(clicked()),this,SLOT(func_exp()));
    connect(ui->pushButton_log,SIGNAL(clicked()),this,SLOT(func_exp()));

    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_mult,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_mod,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_pow,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_brck_op,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_brck_cl,SIGNAL(clicked()),this,SLOT(digit_nambers()));
    connect(ui->pushButton_var_x,SIGNAL(clicked()),this,SLOT(digit_nambers()));


    connect(ui->pushButton_eq,SIGNAL(clicked()),this,SLOT(on_pushButton_eq_clicked()));

    connect(ui->pushButton_del,SIGNAL(clicked()),this,SLOT(on_pushButton_del_clicked()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::func_exp()
{
   QPushButton *button = (QPushButton *) sender();
   QString new_label;
   new_label = (ui->lineEdit->text() + button->text());
   ui->lineEdit->setText(new_label + '(');
}

void Calculator::digit_nambers()
{
    QPushButton *button = (QPushButton *) sender();
    QString new_label;
    new_label = (ui->lineEdit->text() + button->text());
    ui->lineEdit->setText(new_label);
}


void Calculator::on_pushButton_eq_clicked()
{
//        QString value;
//        value = ui->lineEdit->text();
//        double result;
//        QByteArray str_bit = value.toLocal8Bit();
//        char *res_str = str_bit.data();
//        int check = launch(res_str, &result);
//        if (!check) {
//           ui->lineEdit->setText("ERROR");
//        } else {
//           value = QString::number(result, 'g', 16);
//           ui->lineEdit->setText(value);
//        }

        double res = 0;

         QString inputStr = ui->lineEdit->text();

         try {
           res =  controller.Calculation(inputStr);
           inputStr = QString::number(res, 'g', 15);
           ui->lineEdit->setText(inputStr);
         } catch (...) {
           ui->lineEdit->setText("invalid input");
         }
}


void Calculator::on_pushButton_del_clicked()
{
    ui->lineEdit->clear();
    ui->widget->clearGraphs();
//    ui->widget->graph(0)->data()->clear();
    x.clear();
    y.clear();
    ui->widget->replot();

}


void Calculator::on_pushButton_clear_clicked()
{
    QString value = ui->lineEdit->text();
    value.chop(1);
    ui->lineEdit->setText(value);
}

double Calculator::doubleSpinBox_Xmax() {
    return ui->doubleSpinBox_Xmax->text().toDouble();
}

double Calculator::doubleSpinBox_Xmin() {
    return ui->doubleSpinBox_Xmin->text().toDouble();
}


void Calculator::on_pushButton_graph_clicked()
{
//    ui->widget->clearGraphs();
//    QString new_label = ui->lineEdit->text();
//       QString value, origin_string;
//       h = 0.01;
//       xBegin = doubleSpinBox_Xmin();
//       xEnd = doubleSpinBox_Xmax();
//       ui->widget->xAxis->setRange(xBegin, xEnd);
//       ui->widget->yAxis->setRange(xBegin, xEnd);
//       Y = 0;
//   //    N = (xEnd - xBegin)/h + 2;

//       for(X = xBegin; X <= xEnd; X+= h) {
//           if (fabs(X) < EPS) X = 0;
//           x.push_back(X);
////           qDebug()<<X;
//           origin_string = new_label;

//           value = origin_string.replace("x",('(' + QString::number(X) + ')'));
//           QByteArray str_bit = value.toLocal8Bit();
////           qDebug()<<value;
//           char *res_str = str_bit.data();
//           int check = launch(res_str, &Y);
//           if (!check) {
//              ui->lineEdit->setText("ERROR");
//           } else {
//              y.push_back(Y);
//           }
//       }
//       ui->widget->addGraph();
//       ui->widget->graph(0)->setData(x,y);
//       ui->widget->replot();
//       x.clear();  //  для очистки
//       y.clear();

    ui->widget->clearGraphs();
//     h = ui->lineEdit_step->text().toDouble();
     xBegin = doubleSpinBox_Xmin();
     xEnd = doubleSpinBox_Xmax();
      qDebug()<<xBegin;
      qDebug()<<xEnd;
     s21::DataPlot data_plot_input(ui->lineEdit->text().toStdString(), xBegin, xEnd);
     std::pair<QVector<double>, QVector<double>> data_plot;

     ui->widget->xAxis->setRange(data_plot_input.x_begin_, data_plot_input.x_end_);
     ui->widget->yAxis->setRange(data_plot_input.x_begin_, data_plot_input.x_end_);
//     ui->widget->yAxis->setRange(ui->lineEdit_y_min->text().toDouble(), ui->lineEdit_y_max->text().toDouble());
     try {
       data_plot = controller.PlotCalculation(data_plot_input);
       ui->widget->addGraph();
       ui->widget->graph(0)->addData(data_plot.first, data_plot.second);
       ui->widget->replot();
     } catch (...) {
       ui->lineEdit->setText("invalid parametr");
     }

}





void Calculator::on_pushButton_credit_clicked()
{
    Credit window;
    window.setModal(true);
    window.setWindowTitle("Credit");
    window.exec();
}


void Calculator::on_pushButton_debit_clicked()
{
    debit window;
    window.setModal(true);
    window.setWindowTitle("Debit");
    window.exec();
}

