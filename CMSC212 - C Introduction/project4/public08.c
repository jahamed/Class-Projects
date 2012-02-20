#include <stdio.h>

#include "ast.h"

/**
 * CMSC 212, 2008 Fall, Project #4
 * Public Test #8, public08.c
 *
 * Tests equal() on a *few* trees.
 */

static void check_equals(AST_node *expr[], int line_no);

int main(int argc, char **argv) {

  AST_node *exprs1[2], *exprs2[2], *exprs3[2], *exprs4[2], *exprs5[2],
           *exprs6[2], *exprs7[2];

  exprs1[0]= create_int_constant_node(5);
  exprs1[1]= create_int_constant_node(5);

  exprs2[0]= create_int_constant_node(5);
  exprs2[1]= create_double_constant_node(5.0);

  exprs3[0]= create_double_constant_node(5.0);
  exprs3[1]= create_double_constant_node(6.25);

  exprs4[0]= create_variable_node("x");
  exprs4[1]= create_variable_node("x");

  exprs5[0]= create_variable_node("x");
  exprs5[1]= create_variable_node("y");

  exprs6[0]= create_operator_node(PLUS,
                create_operator_node(MINUS,
                  create_operator_node(TIMES,
                    create_int_constant_node(4),
                    create_operator_node(PLUS,
                      create_int_constant_node(3),
                      create_int_constant_node(5))),
                  create_operator_node(PLUS,
                    create_int_constant_node(2),
                    create_variable_node("x"))),
                create_variable_node("y"));
  exprs6[1]= create_operator_node(PLUS,
                create_operator_node(MINUS,
                  create_operator_node(TIMES,
                    create_int_constant_node(4),
                    create_operator_node(PLUS,
                      create_int_constant_node(3),
                      create_int_constant_node(5))),
                  create_operator_node(PLUS,
                    create_int_constant_node(2),
                    create_variable_node("x"))),
                create_variable_node("y"));

  exprs7[0]= create_operator_node(PLUS,
                create_operator_node(MINUS,
                  create_operator_node(TIMES,
                    create_int_constant_node(4),
                    create_operator_node(PLUS,
                      create_int_constant_node(3),
                      create_int_constant_node(5))),
                  create_operator_node(PLUS,
                    create_int_constant_node(2),
                    create_variable_node("x"))),
                create_variable_node("y"));
  exprs7[1]= create_operator_node(PLUS,
                create_operator_node(MINUS,
                  create_operator_node(TIMES,
                    create_int_constant_node(4),
                    create_operator_node(PLUS,
                      create_int_constant_node(3),
                      create_int_constant_node(5))),
                  create_operator_node(PLUS,
                    create_int_constant_node(2),
                    create_variable_node("x"))),
                create_operator_node(UNARY_MINUS,
                  create_variable_node("y"),
                  NULL));

  print(exprs7[0]);
  printf("\n");
  print(exprs7[1]);
  printf("\n");

  check_equals(exprs1, __LINE__);
  check_equals(exprs2, __LINE__);
  check_equals(exprs3, __LINE__);
  check_equals(exprs4, __LINE__);
  check_equals(exprs5, __LINE__);
  check_equals(exprs6, __LINE__);
  check_equals(exprs7, __LINE__);

  clear(&exprs1[0]);
  clear(&exprs1[1]);
  clear(&exprs2[0]);
  clear(&exprs2[1]);
  clear(&exprs3[0]);
  clear(&exprs3[1]);
  clear(&exprs4[0]);
  clear(&exprs4[1]);
  clear(&exprs5[0]);
  clear(&exprs5[1]);
  clear(&exprs6[0]);
  clear(&exprs6[1]);
  clear(&exprs7[0]);
  clear(&exprs7[1]);

  return 0;
}

void check_equals(AST_node *expr[], int line_no) {
  if(equal(expr[0], expr[1]))
    printf("Equal\n");
  else
    printf("Not equal at line %d\n", line_no);
}
