/// \file
/**
*
* @file controller.cc
* @brief Controller class implementation

This file incudes the Controller methods serving to build 
the Model-View-Controller architecture.
The Controller connects the View which is user interface and Model which is the  buisiness logic.

* @date 2023-07-15
* @author elmersha
*/

#include "controller.h"
namespace s21 {
double Controller::C_string_calc(char *string, double x_number)
    {
            return this->Model_.string_calc(string, x_number);
    }
int Controller::C_validated(char *str)
{
        return this->Model_.validated(str);
}
void Controller::C_credit_calc(float credit_amount, int credit_term,
                 float credit_percentage_rate, int repay_type,
                 float *monthly_pay_first, float *monthly_pay_last,
                 float *overpay, float *total_repayment)
    {
        return this->Model_.credit_calc(credit_amount, credit_term,
                                        credit_percentage_rate, repay_type,
                                        monthly_pay_first, monthly_pay_last,
                                        overpay, total_repayment);
    }
void Controller::C_deposit_calc_simple(double Deposit_amount, int Deposit_term,
                         double Deposit_percent, double Tax_rate,
                         double *AccruedInterests, double *TaxAmount,
                         double *DepositClosingAmount)
    {
        return this->Model_.deposit_calc_simple (Deposit_amount, Deposit_term,
                                                 Deposit_percent, Tax_rate,
                                                 AccruedInterests, TaxAmount,
                                                 DepositClosingAmount);
    }



void Controller::C_deposit_calc(double Deposit_amount, int Deposit_term,
                  double Deposit_percent, double Tax_rate, int capitalize,
                  double *AccruedInterests, double *TaxAmount,
                  double *DepositClosingAmount)
    {
        return this->Model_.deposit_calc(Deposit_amount, Deposit_term,
                                         Deposit_percent, Tax_rate, capitalize,
                                         AccruedInterests, TaxAmount,
                                         DepositClosingAmount);
    }

}  // namespace s21
