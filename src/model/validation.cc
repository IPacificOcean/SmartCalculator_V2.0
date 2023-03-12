//
// Created by Qyburn Bongo on 3/11/23.
//
#include <string>
//#include  <cstring>

#include "validation.h"
#define success  false;
#define failure  true;


bool s21::Validation::CheckNumber(size_t &index) const {
    bool err = success;
    int count_dot{};
    for (auto i = index; i < expression_.size(); ++i) {
        char c = expression_[i];
        if (isdigit(c) || ((c == '.'))) {
            if (c == '.') count_dot++;
        } else {
            index = i;
            break;
        }
    }
    if (count_dot > 1) err = failure;
    return err;
}

bool s21::Validation::IsValid() const {
    bool error = success;
    int brck_open_count{}, brck_close_count{};
    char check[] = "+-*/^m";
    if (expression_.size() > 255 || expression_.empty()) error = failure;
    for (size_t i = 0; i < expression_.size() && !error; ++i) {
        char first = expression_[0];
        size_t last = expression_.size() - 1;
        char current = expression_[i];
        char next = expression_[i + 1];
        char prev{};
        if (isdigit(current) && next == '.') {
            error = CheckNumber(i);
            current = expression_[i];
            next = expression_[i + 1];
        }
        if (i != 0) prev = expression_[i - 1];
        if (current == 'e' && !isdigit(prev)) error = failure;
        if (strspn(&current, check) && strspn(&prev, check)) error = failure;
        if (current == '(') brck_open_count++;
        if (current == ')') brck_close_count++;
        if (brck_open_count < brck_close_count) error = failure;
        if (i == last && brck_open_count != brck_close_count) error = failure;
        if ((prev == '(' &&
             (current == '*' || current == '/' || current == '^' || current == 'm')) ||
            (first == '*' || first == '/' || first == '^' || first == 'm' ||
             first == '.') ||
            (!isdigit(expression_[last]) && expression_[last] != ')')) {
            error = failure;
        }
        if (current == '.' && (!isdigit(prev) || !isdigit(next))) error = failure;
        if (current == '(' && next == ')') error = failure;
        if (prev == '(' && !isdigit(current) && next == ')') error = failure;
        if ((current == '(' || isdigit(current)) && prev == ')') error = failure;
        if (i != last) {
            if ((current == ')') && (!strspn(&next, check) && next != ')')) error = failure;
            if ((isdigit(current)) && (!strspn(&next, check) && next != ')' && !isdigit(next))) error = failure;
        }
    }
    return error;
}