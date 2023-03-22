//
// Created by Qyburn Bongo on 3/16/23.
//

#include "parser.h"

std::list<std::string> s21::Parser::ExpressionToRpn(
    const std::string &expression) {
  std::list<std::string> rpn_expression;
  std::stack<char> operators;

  for (size_t i = 0; i < expression.size(); ++i) {
    char c = expression[i];
    if ((isdigit(c) || c == 'X')) {
      std::string d{};
      if (c == 'X') {
        d = "X";
      } else {
        d = std::to_string(ParseOfDigitFromExpression(i, expression));
        --i;
      }
      rpn_expression.push_back(d);

    } else if (isalpha(c) && c != 'm') {
      c = CheckFuncIs(i, expression);

      operators.push(c);

    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' ||
               c == ')' || c == '^' || c == 'm') {
      if (c == 'm') i += 2;
      UnaryMinusPlus(c, i, expression, rpn_expression);

      ConditionsByPrecedence(c, operators, rpn_expression);
    }
  }
  PopFromStackEnd(operators, rpn_expression);

  return rpn_expression;
}

double s21::Parser::ParseOfDigitFromExpression(size_t &index,
                                               const std::string &expression) {
  std::size_t pos = index;
  double digit{};
  digit = std::stod(expression.substr(pos), &pos);
  index += pos;
  return digit;
}

int s21::Parser::GetPrecedence(char c) const {
  int precedence;
  if (c == '(')
    precedence = 0;
  else if (c == ')')
    precedence = -1;
  else if (c == '+' || c == '-')
    precedence = 1;
  else if (c == '*' || c == '/' || c == 'm')
    precedence = 2;
  else if (c == '^')
    precedence = 3;
  else
    precedence = 4;
  return precedence;
}

char s21::Parser::CheckFuncIs(size_t &index, const std::string &expression) {
  char symbol_func{};
  size_t next_symbol = index + 1;
  if (expression[index] == 's' && expression[next_symbol] == 'i') {
    index = index + 2;
    symbol_func = 's';
  }
  if (expression[index] == 'c') {
    index = index + 2;
    symbol_func = 'c';
  }
  if (expression[index] == 't') {
    index = index + 2;
    symbol_func = 't';
  }
  if (expression[index] == 'l' && expression[next_symbol] == 'n') {
    index = index + 1;
    symbol_func = 'l';
  }
  if (expression[index] == 'l' && expression[next_symbol] == 'o') {
    index = index + 2;
    symbol_func = 'L';
  }
  if (expression[index] == 'a' && expression[next_symbol] == 's') {
    index = index + 3;
    symbol_func = 'S';
  }
  if (expression[index] == 'a' && expression[next_symbol] == 'c') {
    index = index + 3;
    symbol_func = 'C';
  }
  if (expression[index] == 'a' && expression[next_symbol] == 't') {
    index = index + 3;
    symbol_func = 'T';
  }
  if (expression[index] == 's' && expression[next_symbol] == 'q') {
    index = index + 3;
    symbol_func = 'q';
  }
  return symbol_func;
}

void s21::Parser::PopFromStack(char c, std::stack<char> &operators,
                               std::list<std::string> &rpn_expression) {
  while (!operators.empty()) {
    if (operators.top() == '(') {
      break;
    }
    if (GetPrecedence(operators.top()) < GetPrecedence(c)) {
      break;
    }
    PushRpnExpression(operators, rpn_expression);
  }
}

void s21::Parser::PopFromStackEnd(std::stack<char> &operators,
                                  std::list<std::string> &rpn_expression) {
  while (!operators.empty()) {
    PushRpnExpression(operators, rpn_expression);
  }
}

void s21::Parser::PushRpnExpression(std::stack<char> &operators,
                                    std::list<std::string> &rpn_expression) {
  std::string op = {operators.top()};
  rpn_expression.push_back(op);
  operators.pop();
}

void s21::Parser::ConditionsByPrecedence(
    char c, std::stack<char> &operators,
    std::list<std::string> &rpn_expression) {
  if (operators.empty() || c == '(' ||
      GetPrecedence(c) > GetPrecedence(operators.top()) ||
      (c == '^' && operators.top() == '^'))
    operators.push(c);
  else if (c == ')') {
    while (operators.top() != '(') {
      PushRpnExpression(operators, rpn_expression);
    }
    operators.pop();
  } else {
    PopFromStack(c, operators, rpn_expression);
    operators.push(c);
  }
}

void s21::Parser::UnaryMinusPlus(char c, size_t index,
                                 const std::string &expression,
                                 std::list<std::string> &rpn_expression) {
  if ((c == '-' && (index == 0 || expression[index - 1] == '(')) ||
      (c == '+' && (index == 0 || expression[index - 1] == '(')))
    rpn_expression.push_back("0.0");
}

void s21::Parser::PrintRpnExpression(std::list<std::string> &rpn_expression) {
  std::list<std::string> rpn_expression2 = rpn_expression;
  while (!rpn_expression2.empty()) {
    std::cout << rpn_expression2.front();
    rpn_expression2.pop_front();
  }
}
