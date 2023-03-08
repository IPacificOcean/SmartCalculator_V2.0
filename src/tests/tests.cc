//
// Created by Qyburn Bongo on 3/7/23.
//

#include <gtest/gtest.h>
#include <iostream>
#include "../model/calculator.cc"

using std::cout;
using std::endl;

class S21Array_test : public ::testing::Test {
protected:
    void SetUp() override {

    }


};

TEST_F(S21Array_test, test_expression) {
    std::string expression = "2 + 2 *3";
//    cout << expression.length() << endl;
//    cout << "________________" << endl;
    Calculator calc(expression);
    calc.ExpressionToRpn();
    calc.PrintExpression();
    cout << "________________" << endl;
    calc.PrintRpnExpression();
}




int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

