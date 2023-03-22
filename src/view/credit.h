#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

#include "../controller/controller.h"

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);

  ~Credit();

 private slots:
  void on_calculate_clicked();

 private:
  Ui::Credit *ui;
  s21::Controller controller_{};
};

#endif  // CREDIT_H
