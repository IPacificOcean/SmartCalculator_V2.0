//
// Created by Qyburn Bongo on 3/11/23.
//
#include <string>
#include  <cstring>

#include "validation.h"
#define success  false;
#define failure  true;


bool s21::Validation::IsValid() const {
    bool error = success;
    int bracketOpen = 0, bracketClose = 0;
    if (expression_.size() > 255 || expression_.empty()) error = failure;
    for (size_t i = 0; i < expression_.size() && !error; ++i) {
        char prev = 0;
        char next = expression_[i + 1];
        char check[] = "+-*/^m";
        if (i != 0) prev = expression_[i - 1];
        if (strspn(&expression_[i], check) && strspn(&prev, check)) error = failure;
        if (expression_[i] == '(') {
            bracketOpen++;
        }
        if (expression_[i] == ')') {
            bracketClose++;
        }
        if (bracketOpen < bracketClose) error = failure;
        if (i == ((expression_.size()) - 1) && bracketOpen != bracketClose) {
            error = failure;
        }
        if ((prev == '(' &&
             (expression_[i] == '*' || expression_[i] == '/' || expression_[i] == '^' || expression_[i] == 'm')) ||
            (expression_[0] == '*' || expression_[0] == '/' || expression_[0] == '^' || expression_[0] == 'm' ||
             expression_[0] == '.') ||
            (!isdigit(expression_[(expression_.size()) - 1]) && expression_[(expression_.size()) - 1] != ')')) {
            error = failure;
        }
        if (expression_[i] == '.' && (!isdigit(prev) || !isdigit(next))) error = failure;
        if (expression_[i] == '(' && next == ')') error = failure;
        if (prev == '(' && !isdigit(expression_[i]) && next == ')') error = failure;
    }
    return error;

}
