QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
HEADERS += \
    ../controller/controller.h \
    ../model/data/data_credit.h \
    ../model/data/data_deposit.h \
    ../model/data/data_plot.h \
    ../model/executors/calculator_exec.h \
    ../model/executors/credit_exec.h \
    ../model/executors/debit_exec.h \
    ../model/executors/parser.h \
    ../model/executors/plot.h \
    ../model/executors/validator.h \
    ../model/fasad/model.h \
    ../s21_smart_calc.h \
    calculator.h \
    credit.h \
    debit.h \
    qcustomplot.h

SOURCES += \
    ../controller/controller.cc \
    ../model/data/data_credit.cc \
    ../model/data/data_deposit.cc \
    ../model/data/data_plot.cc \
    ../model/executors/calculator_exec.cc \
    ../model/executors/credit_exec.cc \
    ../model/executors/debit_exec.cc \
    ../model/executors/parser.cc \
    ../model/executors/plot.cc \
    ../model/executors/validator.cc \
    ../model/fasad/model.cc \
    ../s21_smart_calc.c \
    calculator.cc \
    credit.cc \
    debit.cc \
    main.cc \
    qcustomplot.cc


FORMS += \
    calculator.ui \
    credit.ui \
    debit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

