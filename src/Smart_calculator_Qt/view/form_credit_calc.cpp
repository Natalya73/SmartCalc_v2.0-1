/// \file
#include "form_credit_calc.h"
#include "ui_form_credit_calc.h"

float Credit_amount = 0.0;
int Credit_term = 0.0;
float Credit_rate = 0.0;
float Monthly_pay_first = 0.0;
float Monthly_pay_last = 0.0;
float Overpay = 0.0;
float Total_Repay = 0.0;

Form_Credit_Calc::Form_Credit_Calc(QWidget *parent)
    : QWidget(parent), ui(new Ui::Form_Credit_Calc) {
  ui->setupUi(this);
  connect(ui->CALCULATE, SIGNAL(clicked()), this, SLOT(CALCULATE_pressed()));
}

Form_Credit_Calc::~Form_Credit_Calc() { delete ui; }
void Form_Credit_Calc::CALCULATE_pressed() {
  float Kredit = ui->Credit_amount_2->value();  // summa

  int SrokKredita = ui->Credit_term_2->value();       // srok
  float PercentKredita = ui->Credit_rate_2->value();  // procent
  float PervyPlatezh;
  float PosledniPlatezh;
  float Pereplata;
  float Dolg_i_Procenty;
  int credit_type = DIFFERENTIAL;
  if (ui->Annuity->isChecked()) credit_type = ANNUITY;
  s21::Controller controller;
  controller.C_credit_calc(Kredit, SrokKredita, PercentKredita, credit_type, &PervyPlatezh,
              &PosledniPlatezh, &Pereplata, &Dolg_i_Procenty);
  QString V_Monthly_pay_first = QString::number(PervyPlatezh, 'f', 2);
  ui->Monthly_pay_first->setText(V_Monthly_pay_first);
  QString V_Monthly_pay_last = QString::number(PosledniPlatezh, 'f', 2);
  ui->Monthly_pay_last->setText(V_Monthly_pay_last);
  QString V_Overpay = QString::number(round(Pereplata), 'f', 2);
  ui->Overpay->setText(V_Overpay);
  QString V_Total_Repay = QString::number(round(Dolg_i_Procenty), 'f', 2);
  ui->Total_Repay->setText(V_Total_Repay);
}
