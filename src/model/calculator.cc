//
// Created by Qyburn Bongo on 3/7/23.
//

#include "calculator.h"


void Calculator::ExpressionToRpn() {
    for (const char c : expression_) {
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            operators_.push(c);
        } else if (c == 's') {

        } else if (c != ' ') {
            rpn_expression_.push(c);
        }
    }

    while (!operators_.empty()) {
        rpn_expression_.push(operators_.top());
        operators_.pop();
    }
}

void Calculator::PrintRpnExpression() {
    std::queue<char> rpn_expression2 = rpn_expression_;
    while (!rpn_expression2.empty()) {
        std::cout << rpn_expression2.front() ;
        rpn_expression2.pop();
    }
}

int Calculator::GetPercedance(char c) const {
    int percedance;
    if (c == '(')  percedance = 1;
    if (c == '+' || c == '-') percedance = 2;
    if (c == '*' || c == '/' || c == 'm') percedance = 3;
    return percedance;
}

int Calculator::FuncIs(int index) {
    for (int i = index; i < expression_.size(); i++) {
        int next_symbol = i + 1;
        if (expression_[i] == 's' && expression_[next_symbol] == 'i') index = i + 3;

    }
    return index;
}
