//
// Created by Qyburn Bongo on 3/7/23.
//

#ifndef CPP3_SMARTCALC_V2_0_0_CALCULATOR_H
#define CPP3_SMARTCALC_V2_0_0_CALCULATOR_H
#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <queue>

namespace s21{

class Calculator {
public:

    Calculator(const std::string &expression) : expression_(expression) {}

    ~Calculator() = default;

    void PrintExpression() const { std::cout << expression_ << std::endl; }

    void PrintRpnExpression();

/***
 * @brif parsing math expression  to rpn
 */
    void ExpressionToRpn();

/***
 * @brif get percedance of operators
 * @param с is token
 * @return percedance
 */
    int GetPrecedence(char c) const;

/***
 * @brif сhecks what function
 * @param index is expression string index
 * @return alias math function
 */
    char CheckFuncIs(size_t &index);

    void PopFromStack();

/***
 * @brif сhecks what precedens of operators
 * @param index is expression string index
 */
    void ConditionsByPrecedence(char c);

/***
 * @brif parses a number from a string
 * @param index is expression string index which is shifted by the number of characters in the number
 * @return double number
 */
    double ParseOfDigitFromExpression(size_t &index);

    void GetDigitFromRpn(std::string token);

    double CalculateRpnExpression();

    void BinaryFunc(std::string token);

private:
    std::string expression_;
    std::stack<char> operators_;
    std::stack<double> numbers_;
    std::queue<std::string> rpn_expression_;
};
}

#endif //CPP3_SMARTCALC_V2_0_0_CALCULATOR_H
