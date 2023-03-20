//
// Created by Qyburn Bongo on 3/7/23.
//

#include <gtest/gtest.h>

#include <iostream>

#include "../model/executors//parser.h"
#include "../model/fasad/model.h"

using std::cout;
using std::endl;
using namespace s21;

class Calculator_test : public ::testing::Test {
protected:
    void SetUp() override {}

    Parser parser;
    Model model;
};

TEST_F(Calculator_test, model_calculation_1) {
    std::string expression = "2+3*2-5/2^4";
    double res{};

    res = model.Calculation(expression);

    cout << res << endl;
}

TEST_F(Calculator_test, parse_test) {
    std::string expression = "2+3*2-5/2^4";

    std::list<std::string> result = parser.ExpressionToRpn(expression);
    parser.PrintExpression(expression);
    cout << "________________" << endl;
    cout << "232*+524^/-" << endl;
    parser.PrintRpnExpression(result);
}

TEST_F(Calculator_test, parse_testX) {
    std::string expression = "X+3*2-5/2^X";

    std::list<std::string> result = parser.ExpressionToRpn(expression);
    parser.PrintExpression(expression);
    cout << "________________" << endl;
    cout << "X32*+52X^/-" << endl;
    parser.PrintRpnExpression(result);
}

TEST_F(Calculator_test, CalculateX) {
//      std::string expression = "(1.1X)+3*2-5/2^X";  // валидация
//  std::string expression = "(X)+3*1.1*X*2-5/2^1.1X";  // валидация
//  std::string expression = "(X)+3*1.1*X*2-5/2^X1.1";  // валидация
//  std::string expression = "(X)+3*1.1*1.1X*2-5/2^1.1*X";  // валидация
//  std::string expression = "(X)+3*1.1*X1.1*2-5/2^1.1*X";  //валидация
//  std::string expression = "(1.1X)+3*1.1*X*2-5/2^1.1*X";  // валидация
    std::string expression = "(-X+1.1)+3*1.1*X*2-5/2^1.1*X";

    std::cout << "Input_____string\n" << expression << std::endl << std::endl;

    DataPlot data_plot(expression, -10, 10);

    std::pair<std::vector<double>, std::vector<double>> result =
            model.PlotCalculation(data_plot);

    std::cout << "Xbegin_____Xend" << std::endl;
    for (auto iter: result.first) {
        std::cout << iter << ' ';
    }
    std::cout << "\n\nYbegin_____Yend" << std::endl;
    for (auto iter: result.second) {
        std::cout << iter << ' ';
    }
}

TEST_F(Calculator_test, expression_to_rpn_brck) {
    std::string expression = "2*(2+3)/5-(1+4)^2";
    double calculated_result = model.Calculation(expression);
    double should_result = -23;
    EXPECT_DOUBLE_EQ(calculated_result, should_result);
}

TEST_F(Calculator_test, expression_to_rpn_funck) {
    std::string expression = "2*sin(3)+sqrt(5)";
    double calculated_result = model.Calculation(expression);
    double should_result = 2.518307993619524;
    EXPECT_DOUBLE_EQ(calculated_result, should_result);
}

TEST_F(Calculator_test, expression_to_rpn_double) {
    std::string expression = "2.58e+1*sin(3.45)+sqrt(5)";
    double calculated_result = model.Calculation(expression);
    double should_result = -5.5953030503776873;
    EXPECT_DOUBLE_EQ(calculated_result, should_result);
}

TEST_F(Calculator_test, Calculate) {
    std::string expression =
            "sqrt(4)+9.235+2^3^sin(cos(10))-564-sqrt(25)+28.6*35mod99^2^3";

    double calculated_result = model.Calculation(expression);
    double should_result = 444.59309217773205;
    EXPECT_DOUBLE_EQ(calculated_result, should_result);
}

TEST_F(Calculator_test, Calculate1) {
    std::string expression =
            "5+(1+2)*4*(1)*cos(2*7.5-2)+sin(cos(2*5))-sqrt(2^log(5-1))+ln(55)";

    double calculated_result = model.Calculation(expression);
    double should_result = 17.920647794675116;
    EXPECT_DOUBLE_EQ(calculated_result, should_result);
}

TEST_F(Calculator_test, Calculate2) {
    std::string expression =
            "-5+(-1+2)*4*cos(-2*7.5-2)+sin(cos(2*5))-sqrt(2^log(5-1))+ln(55)";

    double calculated_result = model.Calculation(expression);
    double should_result = -4.069366934933627;
    EXPECT_DOUBLE_EQ(calculated_result, should_result);
}

TEST_F(Calculator_test, Calculate3) {
    std::string expression = "3+(3+5)*2+3/(1-4)^3*2";

    double calculated_result = model.Calculation(expression);
    double should_result = 18.77777777777778;
    EXPECT_DOUBLE_EQ(calculated_result, should_result);
}

TEST_F(Calculator_test, Calculate4) {
    std::string expression = "-1+(-2+5)";

    double calculated_result = model.Calculation(expression);
    double should_result = 2;
    EXPECT_DOUBLE_EQ(calculated_result, should_result);
}

TEST_F(Calculator_test, ParseOfDigitFromExpression) {
    std::string expression = "25.58e-1+89.47";
    double calculated_result = model.Calculation(expression);
    double should_result = 92.02799999999999;
    EXPECT_DOUBLE_EQ(calculated_result, should_result);
}

TEST_F(Calculator_test, IsNotValid) {
//  std::string expression = "(2)^(-1/2)";
//    std::string expression = "9.47+1.1*5";
//  std::string expression = "2.58e-1*1+80.8";
//    std::string expression = "25.58+89.47";
//    std::string expression =
//    "(5)+(1+2)*4*(-12)+cos(2*7.5-2)+sin(cos(2*5))-sqrt(2^log(5-1))+(1)+ln(5)+(1)";
//    std::string expression = "5.55e+1+sin(-2.88) ";
//    std::string expression = "1+(1)+sin(-2)+1+(1)+1";
//    std::string expression = "";
//    std::string expression = "0";
//    std::string expression = " ";
//  double res = model.Calculation(expression);

//  cout << res << endl;
}


TEST_F(Calculator_test, DrawGraphValid) {
    std::string expression = "(X-X)";
    DataPlot data_plot(expression, -10, 10);
    std::pair<std::vector<double>, std::vector<double>> result = model.PlotCalculation(data_plot);
//    double should_result = 92.02799999999999;
//    EXPECT_DOUBLE_EQ(calculated_result, should_result);
}



