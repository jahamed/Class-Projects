#include <stdio.h>

#include "ast.h"

/**
 * CMSC 212, 2008 Fall, Project #4
 * Public Test #5, public05.c
 *
 * Tests print() on some even more complex trees, that need parenthesis.
 */

static void print_expr(AST_node *expr);

int main(int argc, char **argv) {

  AST_node *expr1, *expr2, *expr3;

  expr1= create_operator_node(PLUS,
      create_operator_node(PLUS,
        create_int_constant_node(1),
        create_operator_node(PLUS,
          create_double_constant_node(5.25),
          create_int_constant_node(-2))),
      create_int_constant_node(-10));

  print_expr(expr1);

  expr2= create_operator_node(TIMES,
          create_operator_node(PLUS,
             create_variable_node("x"),
             create_variable_node("y")),
          create_variable_node("z"));
  print_expr(expr2);

  expr3= create_operator_node(POWER,
          create_variable_node("e"),
          create_operator_node(PLUS,
            create_variable_node("alpha"),
            create_int_constant_node(1)));
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
