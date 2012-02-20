#include <stdio.h>

#include "ast.h"

/**
 * CMSC 212, 2008 Fall, Project #4
 * Public Test #1, public01.c
 *
 * Tests print() on several single-node trees.
 */

static void print_expr(AST_node *expr);

int main(int argc, char **argv) {

  AST_node *expr1, *expr2, *expr3;

  expr1= create_int_constant_node(4);
  print_expr(expr1);

  expr2= create_double_constant_node(-2.0);
  print_expr(expr2);

  expr3= create_variable_node("my_var");
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
