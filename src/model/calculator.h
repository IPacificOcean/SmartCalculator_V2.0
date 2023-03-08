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

class Calculator {
public:
    std::stack<char> operators_;
    std::queue<std::string> rpn_expression_;

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
 * @param token
 * @return percedance
 */
    int GetPrecedence(char c) const;

    char FuncIs(size_t &index);

    void PopFromStack();

    void ConditionsByPrecedence(char c);

    double ParseOfDigit( size_t &index);
private:
    std::string expression_;

};


#endif //CPP3_SMARTCALC_V2_0_0_CALCULATOR_H
