#include <stdio.h>

#include "ast.h"

/**
 * CMSC 212, 2008 Fall, Project #4
 * Public Test #9, public09.c
 *
 * Tests copy() behavior.
 */

static void check_equals(AST_node *expr[], int line_no);

int main(int argc, char **argv) {

  AST_node *exprs1[2], *exprs2[2], *exprs3[2], *exprs4[2];

  exprs1[0]= create_int_constant_node(5);
  exprs1[1]= copy(exprs1[0]);

  exprs2[0]= create_double_constant_node(5.0);
  exprs2[1]= copy(exprs2[0]);

  exprs3[0]= create_variable_node("x");
  exprs3[1]= copy(exprs3[0]);

  exprs4[0]= create_operator_node(PLUS,
                create_operator_node(MINUS,
                  create_operator_node(TIMES,
                    create_int_constant_node(4),
                    create_operator_node(PLUS,
                      create_int_constant_node(3),
                      create_double_constant_node(5.03))),
                  create_operator_node(PLUS,
                    create_int_constant_node(2),
                    create_variable_node("x"))),
                create_variable_node("y"));
  exprs4[1]= copy(exprs4[0]);


  check_equals(exprs1, __LINE__);
  check_equals(exprs2, __LINE__);
  check_equals(exprs3, __LINE__);
  check_equals(exprs4, __LINE__);

  clear(&exprs1[0]);
  clear(&exprs1[1]);
  clear(&exprs2[0]);
  clear(&exprs2[1]);
  clear(&exprs3[0]);
  clear(&exprs3[1]);
  clear(&exprs4[0]);
  clear(&exprs4[1]);

  return 0;
}

void check_equals(AST_node *expr[], int line_no) {
  if(equal(expr[0], expr[1]))
    printf("Equal!\n");
  else
    printf("Error: Not equal at line %d!\n", line_no);
}
