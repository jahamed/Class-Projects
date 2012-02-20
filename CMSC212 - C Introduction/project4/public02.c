#include <stdio.h>

#include "ast.h"

/**
 * CMSC 212, 2008 Fall, Project #4
 * Public Test #2, public02.c
 *
 * Tests print() on several trees involving operators, both binary and unary.
 */

static void print_expr(AST_node *expr);

int main(int argc, char **argv) {

  AST_node *expr1, *expr2, *expr3;

  expr1= create_operator_node(PLUS,
      create_int_constant_node(4),
      create_int_constant_node(-10));

  print_expr(expr1);

  expr2= create_operator_node(MINUS,
      create_variable_node("x"),
      create_int_constant_node(42));
  print_expr(expr2);

  expr3= create_operator_node(UNARY_MINUS,
      create_variable_node("y"),
      NULL);
  print_expr(expr3);

  clear(&expr1);
  clear(&expr2);
  clear(&expr3);

  return 0;
}

void print_expr(AST_node *expr) {
  print(expr);
  printf("\n");
}
