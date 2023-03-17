#include "s21_smart_calc.h"

void print_list(Node *list) {
  for (Node *pTmp = list; pTmp != NULL; pTmp = pTmp->next) {
    printf(" digit : %.6lf\n", pTmp->digit);
    printf(" precedence : %d\n", pTmp->precedence);
    printf(" type : %d\n", pTmp->type);
    printf(" adres of Node : %p\n", pTmp);
  }
}

void push(Node **pList, double digit) {
  Node *pTmp = new_node(digit);
  pTmp->next = *pList;
  *pList = pTmp;
}

double pop(Node **pList) {
  Node *p = *pList;
  double digit = p->digit;
  *pList = p->next;
  free(p);
  return digit;
}

void enqueue(Node **rear, Node **front, double digit) {
  Node *pTmp = new_node(digit);
  if (*front == NULL) {
    *front = pTmp;
    *rear = pTmp;
  } else {
    (*rear)->next = pTmp;
    *rear = pTmp;
  }
}

double dequeue(Node **rear, Node **front) {
  if (*front == NULL) {
    printf("\n Queue underflow");
    exit(EXIT_FAILURE);
  }
  Node *pDel = *front;
  *front = (*front)->next;
  if (*front == NULL) {
    *rear = NULL;
  }
  double d = pDel->digit;
  free(pDel);
  return d;
}

int is_empty(Node *list) { return list == NULL; }

Node *new_node(double digit) {
  Node *pTmp = (Node *)malloc(sizeof(Node));
  if (!is_empty(pTmp)) {
    pTmp->digit = digit;
    pTmp->next = NULL;
    // pTmp->type = 0;
    return pTmp;
  } else {
    printf("\n Heap owerflow");
    exit(EXIT_FAILURE);
  }
}
// позволяет посмотреть, какой символ на верхушке стека
double peek(Node *list) {
  if (!is_empty(list)) {
    return list->digit;
  } else {
    exit(EXIT_FAILURE);
  }
}

// позволяет посмотреть, какой символ под указателем
char peek_ch(char *string) { return *string; }
// проверяет корректность числа и возвращает 1 если в числе несколько точек
int check_number(char *str) {
  int count_dot = 0;
  char c;
  int err = 0;
  while (*str) {
    c = peek_ch(str);
    if (isdigit(c) || ((c == '.'))) {
      if (c == '.') count_dot++;
      // printf("simbollll: %c\n", c);
    } else {
      break;
    }
    str++;
  }
  if (count_dot > 1) err = 1;
  return err;
}

// записывает число из строки в очередь, выдает ошибку если в числе несколько
// точек
int parser_digit_from_str_to_que(Node **rear, Node **front, char **str) {
  double d;
  int error = SUCCESS;
  if (!check_number(*str)) {
    d = strtod((const char *)*str, str);
    enqueue(rear, front, d);
    (*rear)->precedence = NUMBER;
    (*rear)->type = NUMBER;
    // printf("digit: %lf\n", d);
    // print_list(*rear);
  } else {
    error = FAILURE;
  }
  return error;
}
// парсит строку выражения и записывает в "очередь" в виде лексем
int parser_str_to_que(Node **rear, Node **front, char *str) {
  int numIn = 0, error = SUCCESS;
  while (*str) {
    if (isdigit(peek_ch(str))) {
      error = parser_digit_from_str_to_que(rear, front, &str);
      numIn++;
      if (error == FAILURE) break;
    } else {
      enqueue_op(rear, front, &str, &numIn);
      // print_list(*rear);
    }
  }
  return error;
}
// записывает оператор или функцию из строки в очередь
void enqueue_op(Node **rear, Node **front, char **str, int *numIn) {
  char *strF[] = {"sin",  "cos",  "tan", "log", "asin", "acos",
                  "atan", "sqrt", "ln",  "mod", "+",    "-",
                  "*",    "/",    "^",   "(",   ")"};
  int index = -1, unary = 0;
  for (size_t i = 0; i < SIZE_ARRAY; i++) {
    if (strlen(strF[i]) != 1) {
      if (!strncmp(*str, strF[i], 3) || !strncmp(*str, strF[i], 4) ||
          !strncmp(*str, strF[i], 2)) {
        index = (int)i;
        break;
      }
    } else {
      if (!strncmp(*str, strF[i], 1)) {
        if ((peek_ch(strF[i]) == '-') || (peek_ch(strF[i]) == '+')) {
          if (*numIn == 0 ||
              ((*rear)->digit == BKT_OP && (*rear)->precedence == 0)) {
            unary = 1;
          }
        }
        index = (int)i;
        break;
      }
    }
  }
  enqueue(rear, front, index);
  char c = peek_ch(strF[index]);
  if (c == '(') {
    (*rear)->precedence = 0;
  } else if ((c == '+' || c == '-')) {
    if (unary) {
      (*rear)->digit = (c == '-') ? U_MINUS : U_PLUS;
    }
    (*rear)->precedence = 1;
  } else if (c == '*' || c == '/' || c == 'm') {
    (*rear)->precedence = 2;
  } else if (c == '^') {
    (*rear)->precedence = 3;
  } else if (c == ')') {
    (*rear)->precedence = 5;
  } else {
    (*rear)->precedence = 4;
  }
  (*rear)->type = OPERATOR;
  *str += strlen(strF[index]);
  *numIn += strlen(strF[index]);
}
// рассчитывает результат строки выыражения. Возвращает итоговое число.

int resolution(Node **rear, Node **front, double *result) {
  Node *stack_n = NULL, *stack_op = NULL;
  double d;
  int error = 1;
  int precedence = 0;
  while (*front) {
    if ((*front)->type == OPERATOR) {
      precedence = (*front)->precedence;
      d = dequeue(rear, front);
      calculate_expression(&stack_n, &stack_op, d, precedence);
      d = -1;
    } else {
      d = dequeue(rear, front);
      push(&stack_n, d);
      stack_n->precedence = NUMBER;
      d = -1;
    }
  }
  while (!is_empty(stack_op)) {
    precedence = stack_op->precedence;
    calculate_expression(&stack_n, &stack_op, d, precedence);
  }
  *result = pop(&stack_n);
  if (!isfinite(*result)) error = FAILURE;
  while (!is_empty(stack_n)) {
    pop(&stack_n);
    error = FAILURE;
  }

  // printf("\n\nstack numbers:\n");
  // print_list(stack_n);
  // printf("\nstack operators:\n\n");
  // // print_list(stack_op);
  return error;
}

double calculate_expression(Node **stack_n, Node **stack_op, double d,
                            int precedence) {
  double result;
  if (is_empty(*stack_op)) {
    push(stack_op, d);
    (*stack_op)->precedence = precedence;
  } else if ((int)d == BKT_OP) {
    push(stack_op, d);
    (*stack_op)->precedence = precedence;
  } else if ((int)d == BKT_CL) {
    while (!((int)peek(*stack_op) == BKT_OP)) {
      if ((*stack_op)->precedence == 4) {
        // push(stack_op, peek(*stack_op));
        result = calc_unary_stack(stack_op, stack_n);
        push(stack_n, result);
      } else {
        result = calc_binary_stack(stack_op, stack_n);
        push(stack_n, result);
      }
    }
    pop(stack_op);
  } else {
    if ((int)d == POW && peek(*stack_op) == POW) {
      push(stack_op, d);
    } else {
      while (!is_empty(*stack_op) && (precedence <= (*stack_op)->precedence)) {
        if ((*stack_op)->precedence == 4) {
          // push(stack_op, d);
          result = calc_unary_stack(stack_op, stack_n);
          push(stack_n, result);

        } else {
          result = calc_binary_stack(stack_op, stack_n);
          push(stack_n, result);
          if (is_empty(*stack_op)) break;
        }
      }

      if (d != -1) {
        push(stack_op, d);
        (*stack_op)->precedence = precedence;
      }
    }
  }
  return 0;
}

double calc_binary_stack(Node **stack_op, Node **stack_n) {
  double op = pop(stack_op);
  double num2 = pop(stack_n);
  double num1 = (op == U_MINUS || op == U_PLUS) ? 0 : pop(stack_n);
  return calc_binary_res(num1, num2, op);
}

double calc_binary_res(double num1, double num2, int op) {
  double result = 0;
  if (op == PLUS) result = sum(num1, num2);
  if (op == U_PLUS) result = sum(num1, num2);
  if (op == MINUS) result = sub(num1, num2);
  if (op == MULT) result = mul(num1, num2);
  if (op == U_MINUS) result = sub(num1, num2);
  if (op == DIV) result = division(num1, num2);
  if (op == MOD) result = fmod(num1, num2);
  if (op == POW) result = pow(num1, num2);
  return result;
}

double calc_unary_stack(Node **stack_op, Node **stack_n) {
  double op = pop(stack_op);
  double num = pop(stack_n);
  return calc_unary_res(num, op);
}

double calc_unary_res(double num, int op) {
  double result = 0;
  if (op == SIN) result = sin(num);
  if (op == COS) result = cos(num);
  if (op == TAN) result = tan(num);
  if (op == LOG) result = log10(num);
  if (op == ASIN) result = asin(num);
  if (op == ACOS) result = acos(num);
  if (op == ATAN) result = atan(num);
  if (op == SQRT) result = sqrt(num);
  if (op == LN) result = log(num);
  return result;
}

double sum(double num1, double num2) { return num1 + num2; }
double sub(double num1, double num2) { return num1 - num2; }
double mul(double num1, double num2) { return num1 * num2; }
double division(double num1, double num2) { return num1 / num2; }
// start program!!!

int validation(char *str) {
  int error = SUCCESS;
  int bracketOpen = 0, bracketClose = 0;
  if (strlen(str) > 255 || !(*str)) error = FAILURE;
  for (size_t i = 0; str[i] != '\0' && error; i++) {
    char prev = 0;
    char next = str[i + 1];
    char check[] = "+-*/^m";
    if (i != 0) prev = str[i - 1];
    if (strspn(&str[i], check) && strspn(&prev, check)) error = FAILURE;
    if (str[i] == '(') {
      bracketOpen++;
    }
    if (str[i] == ')') {
      bracketClose++;
    }
    if (bracketOpen < bracketClose) error = FAILURE;
    if (i == (strlen(str) - 1) && bracketOpen != bracketClose) {
      error = FAILURE;
    }
    if ((prev == '(' &&
         (str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == 'm')) ||
        (str[0] == '*' || str[0] == '/' || str[0] == '^' || str[0] == 'm' ||
         str[0] == '.') ||
        (!isdigit(str[strlen(str) - 1]) && str[strlen(str) - 1] != ')')) {
      error = FAILURE;
    }
    if (str[i] == '.' && (!isdigit(prev) || !isdigit(next))) error = FAILURE;
    if (str[i] == '(' && next == ')') error = FAILURE;
    if (prev == '(' && !isdigit(str[i]) && next == ')') error = FAILURE;
  }
  return error;
}

int launch(char *str, double *result) {
  int error = SUCCESS;
  Node *front = NULL, *rear = NULL;
  error = validation(str);
  if (error == SUCCESS) {
    error = parser_str_to_que(&rear, &front, str);
    if (error == SUCCESS) {
      error = resolution(&rear, &front, result);
    }
  }
  return error;
}

// int main() {
//   // char *str =
//   "sqrt(4)+9.235+2^3^sin(cos(10))-564-sqrt(25)+28.6*35mod99^2^3";
//   // char *str = "1+2+3+(3+5)*2+3/(1-4)^3*(3^((2+1)+1))/(((1)))+2";
//   char str[255] =
//       "-5+(-1+2)*4*cos(+2*7.5-2)+sin(cos(2*5))-sqrt(2^log(5-1))+ln(55/"
//       "(2+7))+asin(0.5)+tan(50)";
//   // char str[] = "22222222222222222+0";
//   // создаем указатели для "очереди"
//   // Node *front = NULL, *rear = NULL;
//   // parser_str_to_que(&rear, &front, str);
//   double result;
//   int error;
//   error = launch(str, &result);
//   // INFINITY
//   printf("EXPRESSION= %s\n", str);
//   printf("RESULT= %lf\n", result);
//   printf("STATUS= %s\n", error ? "SUCCESS" : "FAILURE");

//   return 0;
// }

/*
Описание алгоритма вычисления арифметического выражения в постфиксной форме:

1. Создается стек с заданным типом данных ExpType result.
2. Выражение просматривается слева направо, при этом возможно 2 случая:
   i. Встретился операнд, тогда от пользователя запрашивается его значение и
добавляется на вершину стека result. ii. Встретилась операция, тогда из стека
result изымаются 2 операнда, над ними совершается указанная операция, и
результат добавляется в стек.
3. При полном проходе выражения в стеке останется численный результат
выражения с заданными значениями.*/

// Приоритеты : 1 - '-', '+'; 2 - '*', '/'; 3 - '^'; 4 - 'function'

// finite Аргументы:
// x – проверяемое число с плавающей точкой.
// Возвращаемое значение:
// 0 - если аргумент плюс или минус бесконечность или не число (NAN).
// Отличное от нуля значение, если проверяемый аргумент – конечное число.
// Описание:
// Функции finite, finitef, finitel проверяют, является ли аргумент конечным
// числом, то есть проверяют, что аргумент не плюс/минус бесконечность и не
// является нечисловым значением (не NAN).
