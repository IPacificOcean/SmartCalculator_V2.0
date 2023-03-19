//
// Created by Qyburn Bongo on 3/7/23.
//

#ifndef CPP3_SMARTCALC_V2_0_0_CALCULATOR_H
#define CPP3_SMARTCALC_V2_0_0_CALCULATOR_H

#include <cstring>
#include <iostream>
#include <queue>
#include <list>
#include <stack>
#include <string>

namespace s21 {

    class Calculator {
    public:
        /***
         * @brif main method for calculation expression
         * @param rpn_expression - the list of tokens of a mathematical expression
         * @return calculation result
         */
        double Calculate(std::list<std::string> &rpn_expression);

    protected:
        /***
         * @brif Converts the string to a number from a list rpn and pushes it to the stack numbers
         * @param token is string-number
         */
        void GetDigitFromRpn(const std::string &token);

        /***
         * @brif calculates expression (binary operator)
         * @param token is a operator, numbers - stack of numbers
         * @return the result of calculations with a particular operator
         */
        double BinaryFunc(std::string &token, std::stack<double> &numbers);

        /***
         * @brif calculates expression (binary operator)
         * @param token is a operator, numbers - stack of numbers
         * @return the result of calculations with a particular operator
         */
        double UnaryFunc(std::string &token, std::stack<double> &numbers);

    };
}  // namespace s21


#endif //CPP3_SMARTCALC_V2_0_0_CALCULATOR_H
