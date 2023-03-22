//
// Created by Qyburn Bongo on 3/11/23.
//

#include "validator.h"

#include <string>

#define success false;
#define failure true;

bool s21::Validator::CheckNumber(size_t &index,
                                 const std::string &expression) const {
  bool err = success;
  int count_dot{};
  auto i = index;
  for (; i < expression.size(); ++i) {
    char c = expression[i];
    if (isdigit(c) || ((c == '.'))) {
      if (c == '.') count_dot++;
    } else {
      index = i;
      break;
    }
  }
  if (count_dot > 1) err = failure;
  index = i;
  return err;
}

bool s21::Validator::IsNotValid(const std::string &expression) const {
  bool error = success;
  int brck_open_count{}, brck_close_count{};
  char check[] = "+-*/^m";
  if (expression.size() > 255 || expression.empty()) error = failure;
  for (size_t i = 0; i < expression.size() && !error; ++i) {
    char first = expression[0];
    size_t last = expression.size() - 1;
    char current = expression[i];
    char next = expression[i + 1];
    char prev{};
    if (isdigit(current) && next == '.') {
      error = CheckNumber(i, expression);
      if (i > last) i = last;
      current = expression[i];
      next = expression[i + 1];
    }
    if (i != 0) prev = expression[i - 1];
    if (current == 'e' && !isdigit(prev)) error = failure;
    if (strspn(&current, check) && strspn(&prev, check)) error = failure;
    if (current == '(') brck_open_count++;
    if (current == ')') brck_close_count++;
    if (brck_open_count < brck_close_count) error = failure;
    if (i == last && brck_open_count != brck_close_count) error = failure;

    if ((prev == '(' && (current == '*' || current == '/' || current == '^' ||
                         current == 'm')) ||
        (first == '*' || first == '/' || first == '^' || first == 'm' ||
         first == '.') ||
        (!isdigit(expression[last]) && expression[last] != ')' &&
         expression[last] != 'X')) {
      error = failure;
    }
    if (current == '.' && (!isdigit(prev) || !isdigit(next))) error = failure;
    if (current == '(' && next == ')') error = failure;
    if (prev == '(' && !isdigit(current) && current != 'X' && next == ')')
      error = failure;
    if ((current == '(' || isdigit(current)) && prev == ')') error = failure;
    if (i != last) {
      if ((current == ')') && (!strspn(&next, check) && next != ')'))
        error = failure;
      if ((isdigit(current)) &&
          (!strspn(&next, check) && next != ')' && !isdigit(next)) &&
          next != 'e')
        error = failure;
      if (current == 'X' &&
          (!strspn(&next, check) && next != ')' && next != 'X'))
        error = failure;
    }
    if (current == 'X' && prev == 'X') error = failure;
    if (i > 0 && current == 'X' &&
        (!strspn(&prev, check) && prev != '(' && prev != 'X'))
      error = failure;
  }
  return error;
}