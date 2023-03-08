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
    Calculator calc(expression);
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
    Calculator calc(expression);
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
    Calculator calc(expression);
    calc.ExpressionToRpn();
    calc.PrintExpression();
    cout << "________________" << endl;
    cout << "23s*5q+" << endl;
    calc.PrintRpnExpression();
}

TEST_F(Calculator_test, expression_to_rpn_double) {
    std::string expression = "2.58*sin(3.45)+sqrt(5)";
    Calculator calc(expression);
    calc.ExpressionToRpn();
    calc.PrintExpression();
    cout << "________________" << endl;
    cout << "23s*5q+" << endl;
    calc.PrintRpnExpression();
}

TEST_F(Calculator_test, ParseOfDigit) {
//    std::string expression = "25.58+89.47";
    std::string expression = "25.58e-1+89.47";
    double result{};
    size_t index = 0;
    Calculator calc(expression);
    result = calc.ParseOfDigit(index);
    cout << "________________" << endl;
    cout << result << endl;
    cout << index << endl;
}




int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

