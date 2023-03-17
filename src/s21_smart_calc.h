#ifndef SRC_S21_SMART_CALC_H_
#define SRC_S21_SMART_CALC_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  SIN,
  COS,
  TAN,
  LOG,
  ASIN,
  ACOS,
  ATAN,
  SQRT,
  LN,
  MOD,
  PLUS,
  MINUS,
  MULT,
  DIV,
  POW,
  BKT_OP,
  BKT_CL,
  OPERATOR,
  U_MINUS,
  U_PLUS,
  NUMBER,
  X
} type_t;

// typedef struct Node Node;
typedef struct List {
  double digit;  // data
  int precedence;
  type_t type;
  struct List *next;  // pointer for the next node
} Node;

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-7
#define SIZE_ARRAY sizeof(strF) / sizeof(strF[0])

void push(Node **pList, double digit);
double pop(Node **pList);
void print_list(Node *list);
int is_empty(Node *list);
Node *new_node(double digit);
double peek(Node *list);
void enqueue(Node **rear, Node **front, double digit);
char peek_ch(char *string);
int check_number(char *str);
// int enqueue_op(Node **rear, Node **front, char c);
void enqueue_op(Node **rear, Node **front, char **str, int *numIn);
int parser_str_to_que(Node **rear, Node **front, char *str);
int parser_digit_from_str_to_que(Node **rear, Node **front, char **str);
double calculate_expression(Node **stack_n, Node **stack_op, double d,
                            int precedence);
int resolution(Node **rear, Node **front, double *result);
double calc_binary_stack(Node **stack_op, Node **stack_n);
double calc_binary_res(double num1, double num2, int op);
double calc_unary_stack(Node **stack_op, Node **stack_n);
double calc_unary_res(double num, int op);
double sum(double num1, double num2);
double sub(double num1, double num2);
double mul(double num1, double num2);
double division(double num1, double num2);
int launch(char *str, double *result);
int validation(char *str);

#endif  // SRC_S21_SMART_CALC_H_
