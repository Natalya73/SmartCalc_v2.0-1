/// \file
#ifndef FORM_DEPOSIT_CALC_H
#define FORM_DEPOSIT_CALC_H

#include <QWidget>
#include "../model/model.h"
#include "../controller/controller.h"

namespace Ui {
class form_deposit_calc;
}

class form_deposit_calc : public QWidget
{
    Q_OBJECT

public:
    explicit form_deposit_calc(QWidget *parent = nullptr);
    ~form_deposit_calc();

private slots:
    void CALCULATE_clicked();

private:
    Ui::form_deposit_calc *ui;
};

#endif // FORM_DEPOSIT_CALC_H
