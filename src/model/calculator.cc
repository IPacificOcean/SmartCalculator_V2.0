//
// Created by Qyburn Bongo on 3/7/23.
//
#include <cstdlib>
#include <string>
#include "calculator.h"

void Calculator::ExpressionToRpn() {
    for (size_t i = 0; i < expression_.size(); i++) {
        char c = expression_[i];
        if (c != ' ' && isdigit(c)) {
            rpn_expression_.push(c);
        } else if (isalpha(c)) {
            c = FuncIs(i);
            operators_.push(c);
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^') {
            ConditionsByPrecedence(c);
        }
    }
    PopFromStack();
}


double Calculator::ParseOfDigit(size_t &index) {
    std::size_t pos = index;
    double digit {};
    digit = std::stod (expression_.substr(pos), &pos);
    index += pos;
    return digit;
}

void Calculator::ConditionsByPrecedence(char c) {
    if (operators_.empty() || c == '(' || GetPrecedence(c) > GetPrecedence(operators_.top())) operators_.push(c);
    else if (c == ')') {
        while (operators_.top() != '(') {
            rpn_expression_.push(operators_.top());
            operators_.pop();
        }
        operators_.pop();
    } else {
        PopFromStack();
        operators_.push(c);
    }
}

void Calculator::PopFromStack() {
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

int Calculator::GetPrecedence(char c) const {
    int precedence;
    if (c == '(')  precedence = 0;
    else if (c == ')')  precedence = -1;
    else if (c == '+' || c == '-') precedence = 1;
    else if (c == '*' || c == '/' || c == 'm') precedence = 2;
    else if (c == '^') precedence = 3;
    else precedence = 4;
    return precedence;
}

char Calculator::FuncIs(size_t &index) {
    char symbol_func{};
    int next_symbol = index + 1;
    if (expression_[index] == 's' && expression_[next_symbol] == 'i') {
        index = index + 2;
        symbol_func = 's';
        }
    if (expression_[index] == 'm') {
        index = index + 2;
        symbol_func = 'm';
    }
    if (expression_[index] == 'c') {
        index = index + 2;
        symbol_func = 'c';
    }
    if (expression_[index] == 't') {
        index = index + 2;
        symbol_func = 't';
    }
    if (expression_[index] == 'l' && expression_[next_symbol] == 'n') {
        index = index + 1;
        symbol_func = 'l';
    }
    if (expression_[index] == 'l' && expression_[next_symbol] == 'o') {
        index = index + 2;
        symbol_func = 'L';
    }
    if (expression_[index] == 'a' && expression_[next_symbol] == 's') {
        index = index + 3;
        symbol_func = 'S';
    }
    if (expression_[index] == 'a' && expression_[next_symbol] == 'c') {
        index = index + 3;
        symbol_func = 'C';
    }
    if (expression_[index] == 'a' && expression_[next_symbol] == 't') {
        index = index + 3;
        symbol_func = 'T';
    }
    if (expression_[index] == 's' && expression_[next_symbol] == 'q') {
        index = index + 3;
        symbol_func = 'q';
    }
    return symbol_func;
}







