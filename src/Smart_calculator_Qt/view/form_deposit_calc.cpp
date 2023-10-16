/// \file
#include "form_deposit_calc.h"
#include "ui_form_deposit_calc.h"

double Deposit_amount = 0.0;
int Deposit_term = 0.0;
double Deposit_percent = 0.0;
double Tax_rate = 0.0;
double Placements = 0.0;
double Withdrawals = 0.0;
double AccruedInterests = 0.0;
double TaxAmount = 0.0;
double DepositClosingAmount = 0.0;

form_deposit_calc::form_deposit_calc(QWidget *parent)
    : QWidget(parent), ui(new Ui::form_deposit_calc) {
  ui->setupUi(this);
  connect(ui->CALCULATE, SIGNAL(clicked()), this, SLOT(CALCULATE_clicked()));

  ui->AccruedInterests->setText(QString::number(AccruedInterests));
  ui->TaxAmount->setText(QString::number(TaxAmount));
  ui->DepositClosingAmount->setText(QString::number(DepositClosingAmount));
}

form_deposit_calc::~form_deposit_calc() { delete ui; }

void form_deposit_calc::CALCULATE_clicked() {
  double deposit = 0;
  int SrokDepo = 0;
  double PercentDepo = 0;
  double Nalog = 0;
  double PercentsTotal = 0;
  double TaxTotal = 0;
  double DepoAndPercents = 0;
  int capitalize = 0;
  double replenish = 0, withdraw = 0;
  s21::Controller controller;
  deposit = ui->Deposit_amount_2->value();
  SrokDepo = ui->Deposit_term_2->value();
  PercentDepo = ui->Deposit_percent_2->value();
  Nalog = ui->Tax_rate_2->value();
  replenish = ui->Placements_2->value();
  withdraw = ui->Withdrawals_2->value();

  // PARTIAL REPLENISHMENTS
  if (ui->ComboboxPlacements->currentText() == "monthly") {
    for (int i = 0; i < SrokDepo; i++) {
      deposit = (deposit + replenish);
      controller.C_deposit_calc(deposit, SrokDepo, PercentDepo, Nalog, capitalize,
                   &PercentsTotal, &TaxTotal, &DepoAndPercents);
    }
  }
  if (ui->ComboboxPlacements->currentText() == "quarterly") {
    for (int i = 0; i < SrokDepo / 3; i++) {
      deposit = deposit + replenish;
      controller.C_deposit_calc(deposit, SrokDepo, PercentDepo, Nalog, capitalize,
                   &PercentsTotal, &TaxTotal, &DepoAndPercents);
    }
  }
  if (ui->ComboboxPlacements->currentText() == "once in 6 months") {
    for (int i = 0; i < SrokDepo / 6; i++) {
      deposit = deposit + replenish;
      controller.C_deposit_calc(deposit, SrokDepo, PercentDepo, Nalog, capitalize,
                   &PercentsTotal, &TaxTotal, &DepoAndPercents);
    }
  }
  if (ui->ComboboxPlacements->currentText() == "yearly") {
    for (int i = 0; i < SrokDepo / 12; i++) {
      deposit = deposit + replenish;
      controller.C_deposit_calc(deposit, SrokDepo, PercentDepo, Nalog, capitalize,
                   &PercentsTotal, &TaxTotal, &DepoAndPercents);
    }
  }
  // PARTIAL WITHDRAWALS

  if (ui->comboBoxWithdrawals->currentText() == "monthly") {
    for (int i = 0; i < SrokDepo; i++) {
      deposit = (deposit - withdraw);
      controller.C_deposit_calc(deposit, SrokDepo, PercentDepo, Nalog, capitalize,
                   &PercentsTotal, &TaxTotal, &DepoAndPercents);
    }
  }

  if (ui->comboBoxWithdrawals->currentText() == "quarterly") {
    for (int i = 0; i < SrokDepo / 3; i++) {
      deposit = deposit - withdraw;
      controller.C_deposit_calc(deposit, SrokDepo, PercentDepo, Nalog, capitalize,
                   &PercentsTotal, &TaxTotal, &DepoAndPercents);
    }
  }
  if (ui->comboBoxWithdrawals->currentText() == "once in 6 months") {
    for (int i = 0; i < SrokDepo / 6; i++) {
      deposit = deposit - withdraw;
      controller.C_deposit_calc(deposit, SrokDepo, PercentDepo, Nalog, capitalize,
                   &PercentsTotal, &TaxTotal, &DepoAndPercents);
    }
  }
  if (ui->comboBoxWithdrawals->currentText() == "yearly") {
    for (int i = 0; i < SrokDepo / 12; i++) {
      deposit = deposit - withdraw;
      controller.C_deposit_calc(deposit, SrokDepo, PercentDepo, Nalog, capitalize,
                   &PercentsTotal, &TaxTotal, &DepoAndPercents);
    }
  }

  if (ui->Payment_frequency->currentText() == "Monthly") {
    controller.C_deposit_calc_simple(deposit, SrokDepo, PercentDepo, Nalog, &PercentsTotal,
                        &TaxTotal, &DepoAndPercents);
  }
  if (ui->Payment_frequency->currentText() == "End of term") {
    controller.C_deposit_calc_simple(deposit, SrokDepo, PercentDepo, Nalog, &PercentsTotal,
                        &TaxTotal, &DepoAndPercents);
  }

  if (ui->CapitalizationMonth->isChecked()) {
    capitalize = s21::Model::CapMonthly;
    controller.C_deposit_calc(deposit, SrokDepo, PercentDepo, Nalog, capitalize,
                 &PercentsTotal, &TaxTotal, &DepoAndPercents);
  }

  if (ui->CapitalizationQuarter->isChecked()) {
    capitalize = s21::Model::CapQuarterly;
    controller.C_deposit_calc(deposit, SrokDepo, PercentDepo, Nalog, capitalize,
                 &PercentsTotal, &TaxTotal, &DepoAndPercents);
  }

  if (ui->CapitalizationHalfYear->isChecked()) {
    capitalize = s21::Model::CapHalfYear;
    controller.C_deposit_calc(deposit, SrokDepo, PercentDepo, Nalog, capitalize,
                 &PercentsTotal, &TaxTotal, &DepoAndPercents);
  }
  if (ui->CapitalizationEndOfTerm->isChecked()) {
    capitalize = 0;
    controller.C_deposit_calc(deposit, SrokDepo, PercentDepo, Nalog, capitalize,
                 &PercentsTotal, &TaxTotal, &DepoAndPercents);
  }
  QString V_AccruedInterests = QString::number(PercentsTotal, 'f', 2);
  ui->AccruedInterests->setText(V_AccruedInterests);
  QString V_TaxAmount = QString::number(TaxTotal, 'f', 2);
  ui->TaxAmount->setText(V_TaxAmount);
  QString V_DepositClosingAmount = QString::number(DepoAndPercents, 'f', 2);
  ui->DepositClosingAmount->setText(V_DepositClosingAmount);
}
