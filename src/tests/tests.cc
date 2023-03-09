//
// Created by Qyburn Bongo on 3/7/23.
//

#include <gtest/gtest.h>
#include <iostream>
#include "../model/calculator.cc"

using std::cout;
using std::endl;

class Calculator_test : public ::testing::Test {
protected:
    void SetUp() override {

    }


};

TEST_F(Calculator_test, simple_expression_to_rpn) {
    std::string expression = "2+3*2-5/2^4";
//    cout << expression.length() << endl;
//    cout << "________________" << endl;
    s21::Calculator calc(expression);
    calc.ExpressionToRpn();
    calc.PrintExpression();
    cout << "________________" << endl;
    cout << "232*+524^/-" << endl;
    calc.PrintRpnExpression();
}

TEST_F(Calculator_test, expression_to_rpn_brck) {
    std::string expression = "2*(2+3)/5-(1+4)^2";
//    cout << expression.length() << endl;
//    cout << "________________" << endl;
    s21:: Calculator calc(expression);
    calc.ExpressionToRpn();
    calc.PrintExpression();
    cout << "________________" << endl;
    cout << "223+*5/14+2^-" << endl;
    calc.PrintRpnExpression();
}

TEST_F(Calculator_test, expression_to_rpn_funck) {
    std::string expression = "2*sin(3)+sqrt(5)";
//    std::string expression = "2+2";
//    cout << expression.length() << endl;
//    cout << "________________" << endl;
    s21::Calculator calc(expression);
    calc.ExpressionToRpn();
    calc.PrintExpression();
    cout << "________________" << endl;
    cout << "23s*5q+" << endl;
    calc.PrintRpnExpression();
}

TEST_F(Calculator_test, expression_to_rpn_double) {
    std::string expression = "2.58e+1*sin(3.45)+sqrt(5)";
    s21::Calculator calc(expression);
    calc.ExpressionToRpn();
    calc.PrintExpression();
    cout << "________________" << endl;
    cout << "23s*5q+" << endl;
    calc.PrintRpnExpression();
}

TEST_F(Calculator_test, CalculateRpnExpression) {
//    std::string expression = "2.58e+1*sin(3.45)+sqrt(5)";
//    std::string expression = "(2*((2+3)/5-(1+4))^2)";
    std::string expression = "2^2^3";
    double d{};
    s21::Calculator calc(expression);
    calc.ExpressionToRpn();
    calc.PrintExpression();
    cout << "________________" << endl;
    cout << "23s*5q+" << endl;
    calc.PrintRpnExpression();
    cout << endl;
    cout << "________________" << endl;
    d = calc.CalculateRpnExpression();
    cout << d << endl;
}

TEST_F(Calculator_test, ParseOfDigitFromExpression) {
//    std::string expression = "25.58+89.47";
    std::string expression = "25.58e-1+89.47";
    double result{};
    size_t index = 0;
    s21::Calculator calc(expression);
    result = calc.ParseOfDigitFromExpression(index);
    cout << "________________" << endl;
    cout << result << endl;
    cout << index << endl;
}




int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

