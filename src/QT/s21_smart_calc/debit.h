#ifndef DEBIT_H
#define DEBIT_H

#include <QDialog>

namespace Ui {
class debit;
}

class debit : public QDialog
{
    Q_OBJECT

public:
    explicit debit(QWidget *parent = nullptr);
    ~debit();

private slots:
    void on_pushButton_calculate_clicked();

    double on_pushButton_del_clicked();

    void on_pushButton_add_clicked();

    double on_pushButton_del_2_clicked();

    void on_pushButton_add_2_clicked();


private:
    Ui::debit *ui;
};

#endif // DEBIT_H
