#include "table.h"
#include <malloc.h>
#include <math.h>
#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
  #define M_PI 3.141592653
#endif

#define THRESH 0.001

/**
 * CMSC 212, Fall 2008, Project #6
 * Public Test #11, public11.c
 *
 * Tests the growing of an array, making sure it can handle the insert of a
 * "large" number (360) of key/value pairs.
 *
 * Link with the array table implementation using shared libraries.
 * 
 * NOTE: Also link with -lm (math library)
 */

static void memory_leak_check();
static void test_function();

static void assert_equals(int truth, int putative, int line_no);
static int int_comprar(const void *a, const void *b);
static int float_comprar(const void *a, const void *b);
static void delete_float(void *p);
static void check_alloc(void *p);
static void verify_angle(Table *t, int deg, float rad, int line_no);

int main(int argc, char **argv) {
  memory_leak_check();
  return 0;
}

void memory_leak_check() {
  unsigned int memory_used;

  mcheck_pedantic(NULL);
  memory_used= mallinfo().uordblks;
  test_function();
  memory_used= mallinfo().uordblks - memory_used;

  if (memory_used != 0)
    printf("Memory leak detected (%d bytes)\n", memory_used);
  else printf("No memory leak detected.\n");
}

void test_function() {
  Table deg_2_rad; /* Lookup table for degrees to radians. */
  int q;

  deg_2_rad= create(int_comprar, NULL, float_comprar, delete_float);

  for (q= 0; q < 360; q++) {
    float *rad= malloc(sizeof(float));
    check_alloc(rad);
    *rad= q * M_PI / 180;
    insert(&deg_2_rad, (void*)(long)q, (void*)rad);
  }

  assert_equals(360, size(deg_2_rad), __LINE__);

  /* Test lookups for a few simple angles */
  verify_angle(&deg_2_rad, 0, 0, __LINE__);
  verify_angle(&deg_2_rad, 15, M_PI/12, __LINE__);
  verify_angle(&deg_2_rad, 30, M_PI/6, __LINE__);
  verify_angle(&deg_2_rad, 45, M_PI/4, __LINE__);

  verify_angle(&deg_2_rad, 90, M_PI/2, __LINE__);
  verify_angle(&deg_2_rad, 180, M_PI, __LINE__);
  verify_angle(&deg_2_rad, 270, 3*M_PI/2, __LINE__);

  clear(&deg_2_rad);
}

void assert_equals(int truth, int putative, int line_no) {
  if (putative != truth) {
    printf("Expected %d, got %d at line %d\n", truth, putative, line_no);
  }
}

int int_comprar(const void *a, const void *b) {
  if ((int)(long)a < (int)(long)b)
    return -1;
  if ((int)(long)a > (int)(long)b)
    return 1;
  return 0;
}

int float_comprar(const void *a, const void *b) {
  if (*(float*)a < *(float*)b)
    return -1;
  if (*(float*)a > *(float*)b)
    return 1;
  return 0;
}

void delete_float(void *p) {
  free((float*)p);
}

void check_alloc(void *p) {
  if (p == NULL) {
    fprintf(stderr, "Error: couldn't allocate memory.\n");
    exit(1);
  }
}

void verify_angle(Table *t, int deg, float rad, int line_no) {
  void *value;
  assert_equals(1, lookup(*t, (void*)(long)deg, &value), line_no);
  assert_equals(1, fabs(*(float*)value - rad) < THRESH, line_no);
}
