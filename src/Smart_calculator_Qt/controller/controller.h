/// \file
/**

* @file controller.h
* @brief Controller class header
The header declares the methods of the Controller class for the Model-View-Controller architecture.

* @date 2023-07-15
* @author elmersha
*/
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  Controller() {}
  ~Controller() {}
  double C_string_calc(char *string, double x_number);
  int C_validated(char *str);
  void C_credit_calc(float credit_amount, int credit_term,
                   float credit_percentage_rate, int repay_type,
                   float *monthly_pay_first, float *monthly_pay_last,
                   float *overpay, float *total_repayment);
  void C_deposit_calc_simple(double Deposit_amount, int Deposit_term,
                           double Deposit_percent, double Tax_rate,
                           double *AccruedInterests, double *TaxAmount,
                           double *DepositClosingAmount);
  void C_deposit_calc(double Deposit_amount, int Deposit_term,
                    double Deposit_percent, double Tax_rate, int capitalize,
                    double *AccruedInterests, double *TaxAmount,
                    double *DepositClosingAmount);
 private:
  s21::Model Model_;  // field to access the model

};  // Controller

}  // namespace s21

#endif  // CONTROLLER_H
