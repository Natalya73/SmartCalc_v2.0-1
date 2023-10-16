/// \file
#ifndef MODEL_H
#define MODEL_H

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <string>
#define ANNUITY 1
#define DIFFERENTIAL 2
#define OK 1
#define FALSE 0

///
/// \brief entity created has head, value, priority and type
/**
 * @brief
 *
 * @param entity
 * @param value
 * @param priority
 * @param EntityType
 */
namespace s21 {

class Model {
  public:
enum EntityType {
  kNum = 0,      // number
  kPlus = 1,     // +
  kMinus = 2,    // -
  kMult = 3,     // *
  kDivide = 4,   // '/'
  kModDiv = 5,  //
  kPower = 6,
  kBracketOpen = 7,   // '('  0
  kBracketClose = 8,  // ')'  0
  kCosinus = 9,
  kSinus = 10,
  kTangence = 11,
  kAcosinus = 12,
  kAsinus = 13,
  kAtangence = 14,
  kSqrtUser = 15,
  kLnUser = 16,
  kLogUser = 17,
  kDot = 18,
  kComma = 19,
  kIks = 20
};

struct Nn {
  char entity;
  double value;
  int priority;
  int EntityType;
} ;

// x1234567890+-*/mod^()cossintanacosasinatansqrtlnlogdotcomma,.

double apply_function(int function_type, double *value_1);
double apply_operator(int operator_type, double *value_1, double *value_2);
void reverse(std::stack<s21::Model::Nn>& Parsed_String, std::stack<s21::Model::Nn>& Rev_Parsed_String);
void parse(char *str, std::stack<s21::Model::Nn>&A, double x_number);

int operator_u(char *str);
int number_1(char *str);
int brackets_norm(char *str);
int check_op_single(char *str);
int validated(char *str);
int polish_notation(char *string, std::stack<Nn>& OutputQueue, double x_number);
double calculate(std::stack<Nn>& StackToSolve);
double string_calc(char *string, double x_number);

//  BONUS PART

#define LEAP 1
#define REGULAR 2
#define CENTRAL_BANK_RATE 0.075
#define TAX_RATE 0.13

enum typeParam {
  CapMonthly = 1,
  CapQuarterly = 2,
  CapHalfYear = 3,
  CapYear = 4,
  CapEndOfTerm = 5,
  PayFrMonth = 6,
  PayFrQuarter = 7,
  PayFrHalfYear = 8,
  PayFrEndOfTerm = 9,
  ReplMonth = 10,
  ReplQuarter = 11,
  ReplHalfYear = 12,
  ReplYear = 13,
  WithdrawMonth = 14,
  WithdrawQuarter = 15,
  WithdrawHalfYear = 17,
  WithdrawYear = 18
};

void credit_calc(float credit_amount, int credit_term,
                 float credit_percentage_rate, int repay_type,
                 float *monthly_pay_first, float *monthly_pay_last,
                 float *overpay, float *total_repayment);
void deposit_calc_simple(double Deposit_amount, int Deposit_term,
                         double Deposit_percent, double Tax_rate,
                         double *AccruedInterests, double *TaxAmount,
                         double *DepositClosingAmount);


void deposit_calc(double Deposit_amount, int Deposit_term,
                  double Deposit_percent, double Tax_rate, int capitalize,
                  double *AccruedInterests, double *TaxAmount,
                  double *DepositClosingAmount);


}; // Model
}  // namespace s21

#endif  // CALCULATORMODEL_H
