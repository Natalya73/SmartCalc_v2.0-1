/// \file
#include "model.h"
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ANNUITY 1
#define DIFFERENTIAL 2
#define OK 1
#define FALSE 0
///
/// \brief entity created has entity, value, priority and type
/**
 * @brief
 *
 * @param head
 * @param value
 * @param priority
 * @param EntityType
 */

namespace s21 {

/// \brief  parses  an incoming string "str" and
/// \brief puts its entities  into stack A
///
/**
 * @brief
 *
 * @param str
 * @param A
 * @param x_number  \brief is case there is an 'x'value in the equation
 */
/*! \internal

  parses  an incoming string "str" and puts its entities  into stack A.
*/
void s21::Model::parse(char *str, std::stack<s21::Model::Nn>&A, double x_number) {
  int i = 0;
  int len = strlen(&str[i]);
  if(validated(str)) {
  for (i = 0; i < len; i++) {
    if (str[i] == '(') {
      A.push({'(', 0, 0, kBracketOpen});
    } else if (str[i] == ')') {
      A.push({')', 0, 0, kBracketClose});
    } else if (str[i] == '+') {
      if (i == 0 || str[i - 1] == '(') {
        A.push({'+', 0, 0, kNum});
      }
      A.push({'+', 0, 1, kPlus});
    } else if (str[i] == '-') {
      if (i == 0 || str[i - 1] == '(') {
        A.push({'-', 0, 0, kNum});
      }
      A.push({'-', 0, 1, kMinus});
    } else if (str[i] == '*') {
      A.push({'*', 0, 2, kMult});
    } else if (str[i] == '/') {
      A.push({'/', 0, 2, kDivide});
    } else if (str[i] == '^') {
      A.push({'^', 0, 4, kPower});
    } else if (str[i] == '.') {
      A.push({'.', 0, 0, kDot});
    }
    // else if (str[i] == ',') {
    //     push(A, 0, 0, kComma);
    // }
    else if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
      A.push({'m', 0, 2, kModDiv});
      i += 2;
    } else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') {
      A.push({'s', 0, 3, kSinus});
      i += 2;
    } else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') {
      A.push({'c', 0, 3, kCosinus});
      i += 2;
    } else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
               str[i + 3] == 'n') {
      A.push({'S', 0, 3, kAsinus});
      i += 3;
    } else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
               str[i + 3] == 's') {
      A.push({'C', 0, 3, kAcosinus});
      i += 3;
    } else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') {
      A.push({'t', 0, 3, kTangence});
      i += 2;
    } else if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
               str[i + 3] == 'n') {
      A.push({'T', 0, 3, kAtangence});
      i += 3;
    } else if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
               str[i + 3] == 't') {
      A.push({'q', 0, 3, kSqrtUser});
      i += 3;
    } else if (str[i] == 'l' && str[i + 1] == 'n') {
      A.push({'l', 0, 3, kLnUser});
      i += 1;
    } else if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g') {
      A.push({'L', 0, 3, kLogUser});
      i += 2;
    } else if (str[i] == 'x' || (str[i] >= '0' && str[i] <= '9')) {
      if (str[i] == 'x') {
        A.push({'x', x_number, 0, kNum});
      } else {
        A.push({32, atof(str + i), 0, kNum});
        i += strspn(str + i, "1234567890.") - 1;
        // char buffer[255] = {0};
        // int k = 0;
        // while (isdigit(str[i + k]) || str[i + k] == '.') {
        //   buffer[k] = str[i + k];
        //   k++;
        // }
        // double temp_2 = atof(buffer);
        // push(A, temp_2, 0, kNum);
        // i = i + k - 1;
      }
    }
  }
  }
}
/// \brief checks an incoming string char "str"
/// \return returns '1' if  the char is an operator and '0' if not
///
/**
 * @brief
 * @param str
 */
/*! \internal
returns '1' if  the char is an operator and '0' if not
  
*/
int s21::Model::operator_u(char *str) {
  int result;
  int i = 0;
  if (str[i] == '-' || str[i] == '+' || str[i] == '/' || str[i] == '*' ||
      str[i] == '^' ||
      (str[i] == 'm' &&
       str[i + 2] == 'd')) {  //|| (str[i] == 'm' && str[i+2] == 'd')
    result = OK;
    str++;
  } else {
    result = FALSE;
  }
  return result;
}
/// \brief checks an incoming string char "str"
/// \return returns '1' if  the char is a number and '0' if not
///
/**
 * @brief
 * @param str - incoming string
 */
/*! \internal
returns '1' if  the char is a number and '0' if not
  
*/
int s21::Model::number_1(char *str) {
  int result;
  int i = 0;
  int res = isdigit(str[i]);
  if (res != 0) {
    result = OK;
    str++;
  } else {
    result = FALSE;
  }
  return result;
}
/// \brief checks an incoming string char "str"
/// \return returns '1' if  the paranthesis in a string match and used correctly
/// and '0' if not
///
/**
 * @brief
 * @param str - incoming string
 */
/*! \internal
returns '1' if  brackets ok and 0  if not
  
*/
int s21::Model::brackets_norm(char *str) {
  int result = OK;
  int c1 = 0;
  unsigned long len = strlen(str);
  for (unsigned long i = 0; i < len; i++) {
    switch (str[i]) {
      case '(':
        c1++;
        break;
      case ')':
        c1--;
        if (c1 < 0) result = FALSE;
        break;
    }
  }
  if (c1 == 0 && result == OK) {
    result = OK;
  } else {
    result = FALSE;
  }
  return result;
}
/// \brief checks an incoming string char "str"
/// \return returns '1' if  the char is a single operator and '0' if not
///
/**
 * @brief
 * @param str - incoming string
 */
/*! \internal
returns '1' if  the operator is one and '0' if not
  
*/
int s21::Model::check_op_single(char *str) {
  int result = OK;
  unsigned long len = strlen(str);
  unsigned long op = 0;
  for (op = 0; op < len; op++) {
    if (operator_u(&str[op]) && operator_u(&str[op + 1])) {
      result = FALSE;
    }
  }
  return result;
}

/// \brief  Polish notations checks a string and sorts its entities according to
/// \brief  the shunting yard algorithm
/// \return  returns the final stack-queue for calculation according to the
/// shunting yard algorithm \return and OK if the result is successful -  FALSE
/// if not
/// Here an STL container stack is used to store and rearrange data
/**
 * @brief
 * @param string
 * @param OutputQueue
 * @param x_number
 */
/*! \internal
returns '1' if  the operator is one and '0' if not
  Polish notations checks a string and sorts its entities according to the shunting yard algorithm
*/
int s21::Model::polish_notation(char *string, std::stack<Nn>& OutputQueue, double x_number) {
  std::stack<Nn> tmp;
  std::stack<Nn> Input;
  std::stack<Nn> OperatorStack;
  int result = OK;
  // int parse_permitted = validated(string);
    result = OK;
    parse(string, tmp, x_number);
  reverse(tmp, Input);
  while (!Input.empty()) {
    if (Input.top().EntityType == kNum) {
      OutputQueue.push({Input.top().entity, Input.top().value, Input.top().priority, Input.top().EntityType});
      Input.pop();
    } else if (Input.top().EntityType >= kCosinus && Input.top().EntityType <= kLogUser) {
      OperatorStack.push({Input.top().entity, Input.top().value, Input.top().priority, Input.top().EntityType});
      Input.pop();
    } else if (Input.top().EntityType >= kPlus && Input.top().EntityType < kPower) {
      while (!OperatorStack.empty() && OperatorStack.top().EntityType != kBracketOpen &&
             Input.top().priority <= OperatorStack.top().priority)
                      // Input.top().priority <= OperatorStack.top().priority)
      {
        OutputQueue.push({OperatorStack.top().entity, OperatorStack.top().value, OperatorStack.top().priority,
             OperatorStack.top().EntityType});
        OperatorStack.pop();
      }
      OperatorStack.push({Input.top().entity, Input.top().value, Input.top().priority, Input.top().EntityType});
      Input.pop();
    } else if (Input.top().EntityType == kPower) {
      while (!OperatorStack.empty() && OperatorStack.top().EntityType != kBracketOpen &&
             Input.top().priority < OperatorStack.top().priority)  // There was an error: nput->priority
                                           // > OperatorStack.top().priority)
      {
        OutputQueue.push({OperatorStack.top().entity, OperatorStack.top().value, OperatorStack.top().priority,
             OperatorStack.top().EntityType});
        OperatorStack.pop();
      }
      OperatorStack.push({Input.top().entity, Input.top().value, Input.top().priority, Input.top().EntityType});
      Input.pop();
    } else if (Input.top().EntityType == kBracketOpen) {
      OperatorStack.push({Input.top().entity, Input.top().value, Input.top().priority, Input.top().EntityType});
      Input.pop();
    } else if (Input.top().EntityType == kBracketClose) {
      //while token on top is not kBracketOpen
      while (!OperatorStack.empty() && OperatorStack.top().EntityType != kBracketOpen) {
        //relocate operator in from the stack to the outputqueue
        OutputQueue.push({OperatorStack.top().entity, OperatorStack.top().value, OperatorStack.top().priority,
             OperatorStack.top().EntityType});
        OperatorStack.pop();
      }  // kBracketClose is popped from the stack but its not added to the OutputQueue
      OperatorStack.pop();

      if (!OperatorStack.empty() && OperatorStack.top().EntityType >= kCosinus &&
          OperatorStack.top().EntityType <= kLogUser) {  // functions
        OutputQueue.push({OperatorStack.top().entity, OperatorStack.top().value, OperatorStack.top().priority,
             OperatorStack.top().EntityType});
        OperatorStack.pop();
      }
      //delete the bracketClose from the Input
      Input.pop();
    }
  }
  while (!OperatorStack.empty() && (OperatorStack.top().EntityType != kBracketOpen)) {
    OutputQueue.push({OperatorStack.top().entity, OperatorStack.top().value, OperatorStack.top().priority,
         OperatorStack.top().EntityType});
    OperatorStack.pop();
  }
  return result;
}

/// \brief  reverses the order of entities from one stack,
/// \brief  which is a parsed string, into another
/// \return  returns nothing except the reversed parsed string
///
/**
 * @brief
 * @param Parsed_String
 * @param Rev_Parsed_String
 * @param
 */
void s21::Model::reverse(std::stack<s21::Model::Nn>& Parsed_String, std::stack<s21::Model::Nn>& Rev_Parsed_String) {
  while (!Parsed_String.empty()) {
    s21::Model::Nn temp = Parsed_String.top();
    Rev_Parsed_String.push({temp.entity, temp.value, temp.priority,
         temp.EntityType});
    Parsed_String.pop();
  }
}

/// \brief  removes an entity from the stack top
///
/// \return  returns 1 if popping is a success and 0 if not
///
/**
 * @brief
 * @param head
 */


/// \brief  calculates the string sorted by the polish notation algorithm
///
/// \return  a double value
///
/**
 * @brief
 * @param StackToSolve
 */

/*! \internal
calculates on polish notations
*/

double s21::Model::calculate(std::stack<Nn>& StackToSolve) {
  std::stack<Nn> temp;
  std::stack<Nn> sort;
  reverse(StackToSolve, temp);
  double Total_Result = 0.0;
  int i = 0;
  while (!temp.empty()) {
    if (!temp.empty() && temp.top().EntityType == kNum) {
      sort.push({temp.top().entity, temp.top().value, temp.top().priority, temp.top().EntityType});
      temp.pop();
      i++;
    } else if (!temp.empty() && temp.top().EntityType >= kPlus && temp.top().EntityType <= kPower) {
      double sort_popped_value = sort.top().value;
      sort.pop();
      Total_Result = apply_operator(temp.top().EntityType, &sort.top().value, &sort_popped_value);
      sort.pop();
      sort.push({temp.top().entity, Total_Result, 0, 0});
      temp.pop();
      if (temp.empty()) {
        break;
      }
      i++;
    } else if (!temp.empty() && temp.top().EntityType >= kCosinus &&
               temp.top().EntityType <= kLogUser) {
      double sort_popped_value = sort.top().value;
      sort.pop();
      Total_Result = apply_function(temp.top().EntityType, &sort_popped_value);
      sort.push({temp.top().entity, Total_Result, 0, 0});
      temp.pop();
      if (temp.empty()) {
        break;
      }
      i++;
    }
  }
  return Total_Result;
}

/// \brief  responsible for involving a math.h function according to the
/// corresponding type of an operator
///
/// \return  a double value
///
/**
 * @brief
 * @param function_type
 * @param  value_1
 */

/*! \internal
calculates on polish notation
*/

double s21::Model::apply_function(int function_type, double *value_1) {
  double result = 0.0;
  if (function_type == kCosinus) {
    result = cos(*value_1);
  } else if (function_type == kSinus) {
    result = sin(*value_1);
  } else if (function_type == kTangence) {
    result = tan(*value_1);
  } else if (function_type == kAcosinus) {
    result = acos(*value_1);
  } else if (function_type == kAsinus) {
    result = asin(*value_1);
  } else if (function_type == kAtangence) {
    result = atan(*value_1);
  } else if (function_type == kSqrtUser) {
    result = sqrt(*value_1);
  } else if (function_type == kLnUser) {
    result = log(*value_1);
  } else if (function_type == kLogUser) {
    result = log10(*value_1);
  }
  return result;
}

/// \brief  responsible for involving a math.h operator according to the
/// corresponding type of an operator
///
/// \return  a double value
///
/**
 * @brief
 * @param operator_type
 * @param  value_1
 * @param  value_2
 */
/*! \internal
calculates on polish notation
*/
double s21::Model::apply_operator(int operator_type, double *value_1, double *value_2) {
  double result = 0.0;
  if (operator_type == kPlus) {
    result = (*value_1) + (*value_2);
  } else if (operator_type == kMinus) {
    result = (*value_1) - (*value_2);
  } else if (operator_type == kMult) {
    result = (*value_1) * (*value_2);
  } else if (operator_type == kDivide) {
    result = (*value_1) / (*value_2);
  } else if (operator_type == kModDiv) {
    result = fmod((*value_1), (*value_2));
  } else if (operator_type == kPower) {
    result = pow((*value_1), (*value_2));
  }
  return result;
}

/// \brief  check the incomding
///
/// \return  a double value
///
/**
 * @brief
 * @param operator_type
 * @param  value_1
 * @param  value_2
 */

/// \brief checks an incoming string char "str"
/// \return returns '1' if  the string is input correctly and '0'if not
///
/**
 * @brief
 * @param str
 */
/*! \internal
validates a string
*/
int s21::Model::validated(char *str) {
  int len = strlen(str);
  int result = OK;
  int i = 0;
  for (i = 0; i < len && result == OK; i++) {  
    // check is there are two operators in a row '+-
    if (!check_op_single(str)) {
      result = FALSE;
      break;
    }
    if (!brackets_norm(str)) {
      result = FALSE;
      break;
    }
    if (str[0] == ')' || str[len - 1] == '(') {
      result = FALSE;
      break;
    }
    // check if there are ')('
    if (str[i] == ')' && str[i + 1] == '(') {
      result = FALSE;
      break;
    }
    // check if there is always an operator between a bracket and a digit
    if (number_1(&str[i]) && str[i + 1] == '(') {
      result = FALSE;
      break;
    }
    if (i > 0 && number_1(&str[i]) && str[i - 1] == ')') {
      result = FALSE;
      break;
    }
    // if brackets are empty '()'
    if (str[i] == '(' && str[i + 1] == ')') {
      result = FALSE;
      break;
    }
    // if  * / mod // is btween an opening bracket and a digit:
    if (str[i] == '(' &&
        (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == 'm')) {
      result = FALSE;
      break;
    }
    if (str[i] == '(' && str[i + 1] == '.') {
      result = FALSE;
      break;
    }
    if (str[i] == '(' && str[i + 1] == ',') {
      result = FALSE;
      break;
    }

    // if  (*) and (/) are in the beginning or any operator at the end of the line
    // if(strchr(&str[0], '*') || strchr(&str[0], '/') ||
    // operator_u(&str[len-1])){
    if (str[0] == '*' || str[0] == '/' || str[0] == '%' || operator_u(&str[len - 1])) {
      result = FALSE;
      break;
    }

    if (str[0] == 'm') {
      result = FALSE;
      break;
    }
    if (str[i] == 'd' && !number_1(&str[i + 1]) &&
        str[i + 1] != '(') {  //'(' added in case 5mod(-2)
      result = FALSE;
      break;
    }

    if (str[i] == 'm') {
      if (i > 0 && (number_1(&str[i - 1])) && str[i] == 'm' &&
          (number_1(&str[i + 3]))) {
        result = OK;
      } else {  //
        result = FALSE;
      }
    }

    // перед и после mod должно быть число. I.e. не пустота (m == str[0]), не
    // оператор, не функция, не скобка '('
    if (str[i] == 'm') {
      if (i > 0 && (number_1(&str[i - 1])) && str[i] == 'm' &&
          (number_1(&str[i + 3]))) {
        result = OK;
      }
      if (i > 0 && (!number_1(&str[i - 1])) && str[i] == 'm' &&
          (!number_1(&str[i + 3]))) {
        result = FALSE;
      }
      if (i > 0 && (operator_u(&str[i - 1])) && str[i] == 'm') {
        result = FALSE;
      }
      if (str[i] == 'm' && !number_1(&str[i + 3])) {
        result = FALSE;
      } else {
        result = FALSE;
      }
    }
    int k = 0;
    while ((number_1(&str[i]) || str[i] == '.') || str[i] == ',') {
      if (str[i] == '.' || str[i] == ',') {
        k++;
      }
      i++;
    }
    if (k == 1 || k == 0)
      result = OK;
    else if (k > 1)
      result = FALSE;
  }
  return result;
}

/// \brief calcualtes an incoming string considering the x_number if any
/// \return returns the double result
///
/**
 * @brief
 * @param string
 * @param x_number
 */
/*! \internal
calculates on polish notation
*/
double s21::Model::string_calc(char *string, double x_number) {
  std::stack<Nn> A;
  polish_notation(string, A, x_number);
  double result = calculate(A);
  return result;
}

/// \brief calculates credit amount according to certain parameters
/// \return returns four values of float types
///
/**
 * @brief
 * @param  credit_amount
 * @param  credit_term
 * @param  credit_percentage_rate
 * @param  repay_type
 * @param  monthly_pay_first
 * @param  monthly_pay_last
 * @param  overpay
 * @param  total_repayment
 */
/*! \internal
calculates credit stuff
*/
void s21::Model::credit_calc(float credit_amount, int credit_term,
                 float credit_percentage_rate, int repay_type,
                 float *monthly_pay_first, float *monthly_pay_last,
                 float *overpay, float *total_repayment) {
  float percent_per_month;
  float ostatok_dolga;
  // floats percent_P;
  *overpay = 0;
  *total_repayment = 0;
  float percent_P = credit_percentage_rate / 100 / 12;  // constant 0.01
  // ostatok_dolga = credit_amount;
  if (repay_type == ANNUITY) {
    // percent_P = credit_percentage_rate/100/12; //constant 0.01
    *monthly_pay_first =
        round(
            credit_amount *
            (percent_P + percent_P / (powf((1 + percent_P), credit_term) - 1)) *
            100) /
        100;
    ostatok_dolga = credit_amount;
    for (int i = 0; i < credit_term; i++) {
      percent_per_month = ostatok_dolga * percent_P;
      float debt_part = *monthly_pay_first - percent_per_month;
      float debt_by_month_end = ostatok_dolga - debt_part;
      ostatok_dolga = debt_by_month_end;
      *overpay = (*overpay + percent_per_month);
    }
    *total_repayment = (credit_amount + *overpay);
    *monthly_pay_last = (*monthly_pay_first);
  } else if (repay_type == DIFFERENTIAL) {
    // percent_P = credit_percentage_rate/100/12; //constant 0.01
    *monthly_pay_first =
        round(
            credit_amount *
            (percent_P + percent_P / (powf((1 + percent_P), credit_term) - 1)) *
            100) /
        100;
    ostatok_dolga = credit_amount;
    float debt_part = ostatok_dolga / credit_term;
    percent_per_month = ostatok_dolga * percent_P;
    *monthly_pay_first = debt_part + percent_per_month;
    for (int i = 0; i < credit_term; i++) {
      percent_per_month = ostatok_dolga * percent_P;
      *monthly_pay_last = debt_part + percent_per_month;
      float debt_by_month_end = ostatok_dolga - debt_part;
      ostatok_dolga = debt_by_month_end;
      *overpay = *overpay + percent_per_month;
      //    *monthly_pay_last = *monthly_pay_first;
    }
    *total_repayment = (credit_amount + *overpay);
    //    *monthly_pay_last = *monthly_pay_first;
  }
  // percent_per_month = ostatok_dolga*percent_P;
  ostatok_dolga = credit_amount;
}

/// \brief calculates deposit percent according to certain parameters
/// \return returns 3 values of double types
///
/**
 * @brief
 * @param  Deposit_amount
 * @param  Deposit_term
 * @param  Deposit_percent
 * @param  Tax_rate
 * @param  AccruedInterests
 * @param  TaxAmount
 * @param  DepositClosingAmount
 */
/*! \internal
calculates deposit stuff
*/
void s21::Model::deposit_calc_simple(double Deposit_amount, int Deposit_term,
                         double Deposit_percent, double Tax_rate,
                         double *AccruedInterests, double *TaxAmount,
                         double *DepositClosingAmount) {
  *AccruedInterests =
      (Deposit_amount * Deposit_percent * (Deposit_term)) / 1200;
  *TaxAmount = *AccruedInterests * (Tax_rate / 100);
  *DepositClosingAmount = Deposit_amount + *AccruedInterests;
}

/// \brief calculates deposit interests
/// \return returns 3 values of double types according to capitalization period
///
/**
 * @brief
 * @param  Deposit_amount
 * @param  Deposit_term
 * @param  Deposit_percent
 * @param  Tax_rate
 * @param  AccruedInterests
 * @param  capitalize
 * @param  TaxAmount
 * @param  DepositClosingAmount
 */

/*! \internal
calculates deposit stuff
*/
void s21::Model::deposit_calc(double Deposit_amount, int Deposit_term,
                  double Deposit_percent, double Tax_rate, int capitalize,
                  double *AccruedInterests, double *TaxAmount,
                  double *DepositClosingAmount) {
  if (capitalize == CapMonthly) {
    *DepositClosingAmount =
        Deposit_amount *
        pow((1 + ((Deposit_percent / 100) / 12)), Deposit_term);
    // }
    *AccruedInterests = *DepositClosingAmount - Deposit_amount;
    *TaxAmount = *AccruedInterests * (Tax_rate / 100);
  } else if (capitalize == CapQuarterly) {
    //             } else if (capitalize == CapQuarterly && periodicity == 0 &&
    //             replenish == 0 && withdraw == 0) {
    *DepositClosingAmount =
        Deposit_amount *
        pow((1 + ((Deposit_percent / 100) / 4)), Deposit_term / 3);
    // }
    *AccruedInterests = *DepositClosingAmount - Deposit_amount;
    *TaxAmount = *AccruedInterests * (Tax_rate / 100);
  } else if (capitalize == CapHalfYear) {
    //    } else if (capitalize == CapHalfYear && periodicity == 0 && replenish
    //    == 0 && withdraw == 0) {
    *DepositClosingAmount =
        Deposit_amount *
        pow((1 + ((Deposit_percent / 100) / 2)), Deposit_term / 6.0);
    // }
    *AccruedInterests = *DepositClosingAmount - Deposit_amount;
    *TaxAmount = *AccruedInterests * (Tax_rate / 100);
  }
}

} // namespace s21
