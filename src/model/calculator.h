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

    explicit Calculator(const std::string &expression) : expression_(expression) {}


    ~Calculator() = default;
/***
 * @brif main method for calculation expression
 */
    double Calculate();


    void PrintExpression() const { std::cout << expression_ << std::endl; }

    void PrintRpnExpression();
/***
 * @brif gets a number from a string of expressions
 * @param index is index a string of expressions
 * @return double-precision number
 */
    double ParseOfDigitFromExpression(size_t &index);
/***
 * @brif parsing math expression  to rpn
 */
    void ExpressionToRpn();


private:

/***
 * @brif get percedance of operators
 * @param с is operator
 * @return precedence
 */
    int GetPrecedence(char c) const;

/***
 * @brif сhecks what function
 * @param index is expression string index
 * @return alias math function
 */
    char CheckFuncIs(size_t &index);
/***
 * @brif moves an element from the stack to the string rpn (by conditions)
 * @param c is token
 */
    void PopFromStack(char c);
/***
 * @brif moves an element from the stack to the string rpn (without conditions)
 */
    void PopFromStackEnd();
/***
 * @brif moves an element from the stack to the string rpn (support function)
 */
    void PushRpnExpression();

/***
 * @brif сhecks what precedens of operators
 * @param index is expression string index
 */
    void ConditionsByPrecedence(char c);

/***
 * @brif Converts the string to a number from a queue rpn and pushes it to the stack numbers
 * @param token is string-number
 */
    void GetDigitFromRpn(const std::string &token);
/***
 * @brif calculates expression (binary operator)
 * @param token is operator
 */
    void BinaryFunc(std::string &token);
/***
 * @brif calculates expression (unary operator)
 * @param token is operator
 */
    void UnaryFunc(std::string &token);
/***
 * @brif check unary minus and plus operators
 * @param c is operator
 * @param index is expression string index
 */
    void UnaryMinusPlus(char c, size_t index);

    std::string expression_;
    std::stack<char> operators_;
    std::stack<double> numbers_;
    std::queue<std::string> rpn_expression_;
};
}

#endif //CPP3_SMARTCALC_V2_0_0_CALCULATOR_H
