#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>

#include <cassert>

#include "./Smart_calculator_Qt/model/model.h"

// namespace s21 {

TEST(MyTest, Subtract) {
  s21::Model a;
  char str[256] = "6-6";
  double etalon = 0;
  double x_number = 0;
  double tolerance = 1e-07;  // tolerable allowance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, Subtract2) {
  s21::Model a;
  char str[256] = "-11+2";
  double etalon = -9;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, validated1) {
  s21::Model a;
  char input[256] = "3 +";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}

TEST(MyTest, validated2) {
  s21::Model a;
  char input[256] = "-(8.0009)+(-2.0) -1 - 2";
  int v = a.validated(input);
  ASSERT_EQ(v, 1);
}

TEST(MyTest, validated3) {
  s21::Model a;
  char input[256] = "%3-4sin(1)";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}

TEST(MyTest, validated4) {
  s21::Model a;
  char input[256] = " -(-8 * z(-2))) -1 - 2";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}

TEST(MyTest, validated5) {
  s21::Model a;
  char input[256] = " (8.0 + (-2)) -1 - 2(";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}

TEST(MyTest, validated6) {
  s21::Model a;
  char input[256] = " (8.0 + (-2)) -1 -- 2";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}

TEST(MyTest, validated7) {
  s21::Model a;
  char input[256] = "(8+(-2))-1%2";
  int v = a.validated(input);
  ASSERT_EQ(v, 1);
}

TEST(MyTest, validated8) {
  s21::Model a;
  char input[256] =
      "1 % 2 + cos() + sin(-2) +tan(acos(x) + asin(x)) +atan(0) +sqrt(-1) "
      "+l_n(log(2))";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}

TEST(MyTest, validated9) {
  s21::Model a;
  char input[256] =
      "1%2+cos(8.0)+sin(-2)+tan(acos(x)+asin(x))+atan(0)+sqrt(1)+(l_og(2))";
  int v = a.validated(input);
  ASSERT_EQ(v, 1);
}

TEST(MyTest, validated10) {
  s21::Model a;
  char input[256] =
      "1 % 2 + cos8.0) + sin(-2) +tan(acos(x) + asin(x)) +atan(0) +sqrt(-1) "
      "+l_n(log(2))";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}

TEST(MyTest, validated11) {
  s21::Model a;
  char input[256] =
      "1 % 2 + cos(8.0) + sin(-2) +tan(acos(x) + asin(x)) +atan(0) +sqrt(-1) "
      "+ln(log(2))";
  int v = a.validated(input);
  ASSERT_EQ(v, 1);
}

TEST(MyTest, validated12) {
  s21::Model a;
  char input[256] =
      "1 % 2 + cos(8.0)+ sin(-2) +tan(acos(x) + asin(x)) +atan(0) +sqrt(-1) "
      "+(log(2))";
  int v = a.validated(input);
  ASSERT_EQ(v, 1);
}

TEST(MyTest, validated13) {
  s21::Model a;
  char input[256] =
      "1 % 2 ++(8.0+) + sin(-2) +tan(acos(x) + asin(x)) +atan(0) +sqrt(-1) "
      "+l_n(log(2))";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}

TEST(MyTest, validated16) {
  s21::Model a;
  char input[256] = "sin(-2)*tan(acos(x))";
  int v = a.validated(input);
  ASSERT_EQ(v, 1);
}

TEST(MyTest, validated17) {
  s21::Model a;
  char input[256] = "ln(-2)*tan(acos(x)/asin(x))";
  int v = a.validated(input);
  ASSERT_EQ(v, 1);
}

TEST(MyTest, validated18) {
  s21::Model a;
  char input[256] = "x + 1";
  int v = a.validated(input);
  ASSERT_EQ(v, 1);
}

TEST(MyTest, validated19) {
  s21::Model a;
  char input[256] = "55mod5";
  int v = a.validated(input);
  ASSERT_EQ(v, 1);
}
TEST(MyTest, validated20) {
  s21::Model a;
  char input[256] = "mod5";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}
TEST(MyTest, validated21) {
  s21::Model a;
  char input[256] = "wmodr";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}

TEST(MyTest, validated22) {
  s21::Model a;
  char input[256] = "2.3.3";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}
TEST(MyTest, validated23) {
  s21::Model a;
  char input[256] = "3mod2";
  int v = a.validated(input);
  ASSERT_EQ(v, 1);
}
TEST(MyTest, validated24) {
  s21::Model a;
  char input[256] = "(mod2)";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}

TEST(MyTest, validated25) {
  s21::Model a;
  char input[256] = "-mod2)";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}
TEST(MyTest, validated26) {
  s21::Model a;
  char input[256] = "(.2)";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}
TEST(MyTest, validated27) {
  s21::Model a;
  char input[256] = "(,2)";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}
TEST(MyTest, validated28) {
  s21::Model a;
  char input[256] = "2(";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}
TEST(MyTest, validated29) {
  s21::Model a;
  char input[256] = ")(4";
  int v = a.validated(input);
  ASSERT_EQ(v, 0);
}

TEST(MyTest, stringCalc_1) {
  s21::Model a;
  char str[256] = "3+3";
  double etalon = 6;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}
TEST(MyTest, stringCalc_2) {
  s21::Model a;
  char str[256] = "6-1";
  double etalon = 5;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_3) {
  s21::Model a;
  char str[256] = "cos(10)";
  double etalon = -0.83907152907;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_4) {
  s21::Model a;
  char str[256] = "cos(11)+66-90/70";
  double etalon = 64.7187114123;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_5) {
  s21::Model a;
  char str[256] = "-10+(cos(101))/102";
  double etalon = -9.99125485422;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_6) {
  s21::Model a;
  char str[256] = "-10+(cos(101))";
  double etalon = -9.10799513021;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_7) {
  s21::Model a;
  char str[256] = "10+(cos(101))";
  double etalon = 10.8920048698;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_8) {
  s21::Model a;
  char str[256] = "2^2^2";
  double etalon = 16;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_9) {
  s21::Model a;
  char str[256] = "2^2^2^2";
  double etalon = 65536;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_10) {
  s21::Model a;
  char str[256] = "tan(log(3)) + 3 / 8";
  double etalon = 0.89195732177;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_11) {
  s21::Model a;
  char str[256] = "tan(log(3)) + 3 / 8+10/8^5";
  double etalon = 0.89226249755;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_12) {
  s21::Model a;
  char str[256] = "ln(100)";
  double etalon = 4.60517018599;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_13) {
  s21::Model a;
  char str[256] = "log(100)";
  double etalon = 2;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_14) {
  s21::Model a;
  char str[256] = "0.1^2^2^2^2";
  double etalon = 0;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_15) {
  s21::Model a;
  char str[256] = "-2";
  double etalon = -2;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_16) {
  s21::Model a;
  char str[256] = "(-2)";
  double etalon = -2;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}
TEST(MyTest, stringCalc_17) {
  s21::Model a;
  char str[256] = "10+(-2)";
  double etalon = 8;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_18) {
  s21::Model a;
  char str[256] = "10+(-2)";
  double etalon = 8;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_19) {
  s21::Model a;
  char str[256] = "10+(-(-2))";
  double etalon = 12;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_20) {
  s21::Model a;
  char str[256] = "10+(-(-(-2)))";
  double etalon = 8;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_21) {
  s21::Model a;
  char str[256] = "sin(cos(111))";
  double etalon = -0.48165683451;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}
TEST(MyTest, stringCalc_22) {
  s21::Model a;
  char str[256] = "tan(sqrt(222))";
  double etalon = -1.04688321107;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}
TEST(MyTest, stringCalc_23) {
  s21::Model a;
  char str[256] = "sin(cos(111))+tan(sqrt(222))";
  double etalon = -1.52854004559;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_24) {
  s21::Model a;
  char str[256] = "78mod33";
  double etalon = 12;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_25) {
  s21::Model a;
  char str[256] = "2/1+2+3+4*5*6^7-12+((1000+500*2)*201)+sin(1)";
  double etalon = 6000715.841471;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}
TEST(MyTest, stringCalc_26) {
  s21::Model a;
  char str[256] = "2/1+2+3+4*5*6^7-12+((1000+500*2)*201)";
  double etalon = 6000715;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_27) {
  s21::Model a;
  char str[256] = "3+4*2/(1-5)^2^3";
  double etalon = 3.00012207031;
  double x_number = 0;
  double tolerance = 1e-07;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_28) {
  s21::Model a;
  char str[256] = "2/1+2+3+4*5*6^7-727mod728+((1000+500*2)*201)+sin(1)";
  double etalon = 6000000.84147;
  double x_number = 0;
  double tolerance = 1e-06;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}
TEST(MyTest, stringCalc_29) {
  s21::Model a;
  char str[256] = "sin(cos(1))+tan(sqrt(2))-((3))*(4)";
  double etalon = -5.15148557443;
  double x_number = 0;
  double tolerance = 1e-06;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_30) {
  s21::Model a;
  char str[256] = "1+2+3+4*5*6^7-727mod728+((1000+500*2)*201)+sin(1)";
  double etalon = 5999999.84147;
  double x_number = 0;
  double tolerance = 1e-06;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}
TEST(MyTest, stringCalc_31) {
  s21::Model a;
  char str[256] = "cos(32.2^4.1)*sqrt(3.3)";
  double etalon = 0.70838;
  double x_number = 0;
  double tolerance = 1e-06;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_32) {
  s21::Model a;
  char str[256] = "ln(12.5)";
  double etalon = 2.52573;
  double x_number = 0;
  double tolerance = 1e-05;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_33) {
  s21::Model a;
  char str[256] = "log(12.5)";
  double etalon = 1.09691001301;
  double x_number = 0;
  double tolerance = 1e-05;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}
TEST(MyTest, stringCalc_34) {
  s21::Model a;
  char str[256] = "(-4)-9";
  double etalon = -13;
  double x_number = 0;
  double tolerance = 1e-05;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(MyTest, stringCalc_35) {
  s21::Model a;
  char str[256] = "acos(0)";
  double etalon = 1.570796;
  double x_number = 0;
  double tolerance = 1e-05;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}
TEST(MyTest, stringCalc_36) {
  s21::Model a;
  char str[256] = "asin(1)";
  double etalon = 1.570796;
  double x_number = 0;
  double tolerance = 1e-05;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}
TEST(MyTest, stringCalc_37) {
  s21::Model a;
  char str[256] = "atan(1)";
  double etalon = 0.785398;
  double x_number = 0;
  double tolerance = 1e-05;  // set allowable tolerance
  ASSERT_NEAR(a.string_calc(str, x_number), etalon, tolerance);
}

TEST(ModelTest, CreditCalcTest1) {
  s21::Model model;
  float credit_amount = 200000;
  int credit_term = 24;
  float credit_percentage_rate = 12;
  int repay_type = ANNUITY;
  float monthly_pay_first;
  float monthly_pay_last;
  float overpay;
  float total_repayment;
  model.credit_calc(credit_amount, credit_term, credit_percentage_rate,
                    repay_type, &monthly_pay_first, &monthly_pay_last, &overpay,
                    &total_repayment);
  EXPECT_NEAR(monthly_pay_first, 9414.70, 1e-2);
  EXPECT_NEAR(monthly_pay_last, 9414.70, 1e-2);
  EXPECT_NEAR(round(overpay), 25953, 1e-2);
  EXPECT_NEAR(round(total_repayment), 225953.00, 1e-2);
}

TEST(ModelTest, CreditCalcTest2) {
  s21::Model model;
  float credit_amount = 200000;
  int credit_term = 24;
  float credit_percentage_rate = 12;
  int repay_type = DIFFERENTIAL;
  float monthly_pay_first;
  float monthly_pay_last;
  float overpay;
  float total_repayment;
  model.credit_calc(credit_amount, credit_term, credit_percentage_rate,
                    repay_type, &monthly_pay_first, &monthly_pay_last, &overpay,
                    &total_repayment);
  EXPECT_NEAR(monthly_pay_first, 10333.33, 1e-2);
  EXPECT_NEAR(monthly_pay_last, 8416.67, 1e-2);
  EXPECT_NEAR(round(overpay), 25000, 1e-2);
  EXPECT_NEAR(round(total_repayment), 225000.00, 1e-2);
}

TEST(ModelTest, DepositCalcTest1) {
  s21::Model model;
  double Deposit_amount = 350000;
  int Deposit_term = 9;
  double Deposit_percent = 4.7;
  double Tax_rate = 13;
  int capitalize = s21::Model::CapQuarterly;
  double AccruedInterests;
  double TaxAmount;
  double DepositClosingAmount;
  model.deposit_calc(Deposit_amount, Deposit_term, Deposit_percent, Tax_rate,
                     capitalize, &AccruedInterests, &TaxAmount,
                     &DepositClosingAmount);
  EXPECT_NEAR(AccruedInterests, 12483.03, 1e-2);
  EXPECT_NEAR(TaxAmount, 1622.79, 1e-2);
  EXPECT_NEAR(DepositClosingAmount, 362483.03, 1e-2);
}

TEST(ModelTest, DepositCalcTest2) {
  s21::Model model;
  double Deposit_amount = 350000;
  int Deposit_term = 9;
  double Deposit_percent = 4.7;
  double Tax_rate = 13;
  int capitalize = s21::Model::CapHalfYear;
  double AccruedInterests;
  double TaxAmount;
  double DepositClosingAmount;
  model.deposit_calc(Deposit_amount, Deposit_term, Deposit_percent, Tax_rate,
                     capitalize, &AccruedInterests, &TaxAmount,
                     &DepositClosingAmount);
  EXPECT_NEAR(AccruedInterests, 12409.70, 1e-2);
  EXPECT_NEAR(TaxAmount, 1613.26, 1e-2);
  EXPECT_NEAR(DepositClosingAmount, 362409.70, 1e-2);
}

TEST(ModelTest, DepositCalcTest3) {
  s21::Model model;
  double Deposit_amount = 350000;
  int Deposit_term = 9;
  double Deposit_percent = 4.7;
  double Tax_rate = 13;
  double AccruedInterests;
  double TaxAmount;
  double DepositClosingAmount;
  model.deposit_calc_simple(Deposit_amount, Deposit_term, Deposit_percent,
                            Tax_rate, &AccruedInterests, &TaxAmount,
                            &DepositClosingAmount);
  EXPECT_NEAR(AccruedInterests, 12337.50, 1e-2);
  EXPECT_NEAR(TaxAmount, 1603.88, 1e-2);
  EXPECT_NEAR(DepositClosingAmount, 362337.50, 1e-2);
}

TEST(ModelTest, DepositCalcTest4) {
  s21::Model model;
  double Deposit_amount = 350000;
  int Deposit_term = 12;
  double Deposit_percent = 4.7;
  double Tax_rate = 13;
  int capitalize = s21::Model::CapMonthly;
  double AccruedInterests;
  double TaxAmount;
  double DepositClosingAmount;
  model.deposit_calc(Deposit_amount, Deposit_term, Deposit_percent, Tax_rate,
                     capitalize, &AccruedInterests, &TaxAmount,
                     &DepositClosingAmount);
  EXPECT_NEAR(AccruedInterests, 16809.03, 1e-2);
  EXPECT_NEAR(TaxAmount, 2185.17, 1e-2);
  EXPECT_NEAR(DepositClosingAmount, 366809.03, 1e-2);
}
// }  // namespace s21

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
