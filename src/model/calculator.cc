//
// Created by Qyburn Bongo on 3/7/23.
//
#include <string>
#include <cmath>

#include "calculator.h"


void s21::Calculator::ExpressionToRpn() {
    for (size_t i = 0; i < expression_.size(); ++i) {
        char c = expression_[i];
        if (c != ' ' && isdigit(c)) {
            double d = ParseOfDigitFromExpression(i);
            rpn_expression_.push(std::to_string(d));
            --i;
        } else if (isalpha(c) && c != 'm') {
            c = CheckFuncIs(i);
            operators_.push(c);
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^' || c == 'm') {
            if (c == 'm') i += 2;
            UnaryMinusPlus(c, i);
            ConditionsByPrecedence(c);
        }
    }
    PopFromStackEnd();
}

double s21::Calculator::ParseOfDigitFromExpression(size_t &index) {
    std::size_t pos = index;
    double digit{};
    digit = std::stod(expression_.substr(pos), &pos);
    index += pos;
    return digit;
}

void s21::Calculator::ConditionsByPrecedence(char c) {
    if (operators_.empty() || c == '(' || GetPrecedence(c) > GetPrecedence(operators_.top()) ||
        (c == '^' && operators_.top() == '^'))
        operators_.push(c);
    else if (c == ')') {
        while (operators_.top() != '(') {
            std::string op = {operators_.top()};
            rpn_expression_.push(op);
            operators_.pop();
        }
        operators_.pop();
    } else {
        PopFromStack(c);
        operators_.push(c);
    }
}

void s21::Calculator::PopFromStack(char c) {
    while (!operators_.empty()) {
        if (operators_.top() == '(') {break;}
        if (GetPrecedence(operators_.top()) < GetPrecedence(c)) { break;}
            std::string op = {operators_.top()};
            rpn_expression_.push(op);
            operators_.pop();

    }
}

void s21::Calculator::PopFromStackEnd() {
    while (!operators_.empty()) {
        std::string op = {operators_.top()};
        rpn_expression_.push(op);
        operators_.pop();
    }
}

void s21::Calculator::PrintRpnExpression() {
    std::queue<std::string> rpn_expression2 = rpn_expression_;
    while (!rpn_expression2.empty()) {
        std::cout << rpn_expression2.front();
        rpn_expression2.pop();
    }
}

int s21::Calculator::GetPrecedence(char c) const {
    int precedence;
    if (c == '(') precedence = 0;
    else if (c == ')') precedence = -1;
    else if (c == '+' || c == '-') precedence = 1;
    else if (c == '*' || c == '/' || c == 'm') precedence = 2;
    else if (c == '^') precedence = 3;
    else precedence = 4;
    return precedence;
}

char s21::Calculator::CheckFuncIs(size_t &index) {
    char symbol_func{};
    size_t next_symbol = index + 1;
    if (expression_[index] == 's' && expression_[next_symbol] == 'i') {
        index = index + 2;
        symbol_func = 's';
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

double s21::Calculator::CalculateRpnExpression() {
    double result = 0.0;
    int error = 0;
    while (!rpn_expression_.empty()) {
        std::string token = rpn_expression_.front();
        rpn_expression_.pop();
        GetDigitFromRpn(token);
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^" || token == "m"){
            BinaryFunc(token);
        } else if (isalpha(token.front())) {
            UnaryFunc(token);
        }
    }
    if (isfinite(result)) error = 1;// TODO something
    return result = numbers_.top();
}

void s21::Calculator::GetDigitFromRpn( const std::string &token) {
    if (isdigit(token.front())){
        numbers_.push(std::stod(token));
    }
}

void s21::Calculator::BinaryFunc(std::string &token) {
//    double num1 = (op == U_MINUS || op == U_PLUS) ? 0 : pop(stack_n);
    double num1{}, num2{};
    num2 = numbers_.top();
    numbers_.pop();
    num1 = numbers_.top();
    numbers_.pop();
    if (token == "+") {numbers_.push(num1 + num2);}
    if (token == "-") {numbers_.push(num1 - num2);}
    if (token == "*") {numbers_.push(num1 * num2);}
    if (token == "/") {numbers_.push(num1 / num2);}
    if (token == "^") {numbers_.push(pow(num1, num2));}
    if (token == "m") {numbers_.push(fmod(num1, num2));}
}

void s21::Calculator::UnaryFunc(std::string &token) {
    double num{};
    num = numbers_.top();
    numbers_.pop();
    if (token == "s") {numbers_.push(sin(num));}
    if (token == "c") {numbers_.push(cos(num));}
    if (token == "t") {numbers_.push(tan(num));}
    if (token == "l") {numbers_.push(log(num));}
    if (token == "L") {numbers_.push(log10(num));}
    if (token == "S") {numbers_.push(asin(num));}
    if (token == "C") {numbers_.push(acos(num));}
    if (token == "T") {numbers_.push(atan(num));}
    if (token == "q") {numbers_.push(sqrt(num));}
}

void s21::Calculator::UnaryMinusPlus(char c, size_t index) {
    if ((c == '-' && (index == 0 || expression_[index - 1] == '(')) ||
        (c == '+' && (index == 0 || expression_[index - 1] == '(')))
        rpn_expression_.push("0.0");
}








