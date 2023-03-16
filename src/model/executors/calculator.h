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
         */
        double Calculate(std::list<std::string> &rpn_expression);

    protected:
        /***
         * @brif Converts the string to a number from a queue rpn and pushes it to the
         * stack numbers
         * @param token is string-number
         */
        void GetDigitFromRpn(const std::string &token);
        /***
         * @brif calculates expression (binary operator)
         * @param token is operator
         */
        double BinaryFunc(std::string &token, std::stack<double> &numbers);
        /***
         * @brif calculates expression (unary operator)
         * @param token is operator
         */
        double UnaryFunc(std::string &token, std::stack<double> &numbers);
        //  std::queue<std::string> rpn_expression_;
        //  std::stack<double> numbers_;

    private:
    };
}  // namespace s21


#endif //CPP3_SMARTCALC_V2_0_0_CALCULATOR_H
