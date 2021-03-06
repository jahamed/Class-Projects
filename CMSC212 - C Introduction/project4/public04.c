#include <stdio.h>

#include "ast.h"

/**
 * CMSC 212, 2008 Fall, Project #4
 * Public Test #4, public04.c
 *
 * Tests print() on more complex trees, that also shouldn't need parenthesis.
 */

static void print_expr(AST_node *expr);

int main(int argc, char **argv) {

  AST_node *expr1, *expr2, *expr3;

  expr1= create_operator_node(EQUALS,
          create_operator_node(MODULUS,
            create_int_constant_node(1),
            create_int_constant_node(2)),
          create_operator_node(MODULUS,
            create_int_constant_node(3),
            create_int_constant_node(2)));

  print_expr(expr1);

  expr2= create_operator_node(NOT_EQUALS,
            create_operator_node(PLUS,
              create_int_constant_node(3),
              create_int_constant_node(1)),
            create_operator_node(MINUS,
              create_int_constant_node(3),
              create_int_constant_node(1)));
  print_expr(expr2);

  expr3= create_operator_node(NOT_EQUALS,
          create_variable_node("y"),
          create_operator_node(UNARY_MINUS,
            create_variable_node("x"),
            NULL));
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
