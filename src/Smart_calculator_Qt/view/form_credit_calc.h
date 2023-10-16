/// \file
#ifndef FORM_CREDIT_CALC_H
#define FORM_CREDIT_CALC_H

#include <QWidget>
#include "../model/model.h"
#include "../controller/controller.h"

namespace Ui {
class Form_Credit_Calc;
}

class Form_Credit_Calc : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Credit_Calc(QWidget *parent = nullptr);
    ~Form_Credit_Calc();

private:
    Ui::Form_Credit_Calc *ui;

 private slots:

    void CALCULATE_pressed();
};

#endif // FORM_CREDIT_CALC_H
