/*
Name=Javed Ahamed
Glue Logon=jahamed
UID=109365000
Sec=0202
*/
/*"I pledge on my honor that I have not given or received any unauthorized
assistance on this assignment."*/

/*this source file is the tester suite to judge submit server implementions of
 *list.c and array.c and judge if they are correct or not*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "table.h"

static void invalid();
static void int_int_test();
static void string_string_test();
static int int_visitorfn(void *key, void *data);

/*global variables to help with visitorfns*/
static int int_visitorfn_count = 0;

/*this method is called when the table implementation is invalid*/
static void invalid(){
  printf("Invalid table implementation.\n");
  exit(-1);
}

/*this is the string cmp function, to pass in as function pointer to the Table*/
static int string_cmp(const void *x, const void *y) {
  return strcmp(x, y);
}

/*this is the integer comparison function, can pass it in for key and data cmp*/
static int int_cmp(const void *x, const void *y){
  if(x == y){
    return 0;
  }else if((int) (long) x < (int) (long) y){
    return -1;
  }else{
    return 1;
  }
}

/*this function checks if the size of test, and the passed in size match*/
static void size_test(Table test, int idealsize){
  if(size(test) != idealsize){
    invalid();
  }
}

/*this function uses the lookup function on integers, and fails when the
 *integers were not found in the table*/
static void int_lookup_test(Table test, void *key, void *item){
  void * temp_item = item;
  if(lookup(test, key, &temp_item) == -1){
    invalid();
  }else if((int) (long) temp_item != (int) (long) key*2){
    invalid();
  }
}

int main() {
  int_int_test(); 
  string_string_test();
  /*if it hasnt failed yet.... congratz!*/
  printf("Correct table implementation.\n");
  exit(0);
  return 0;
}


/*this function tests table.h functions on integers*/
static void int_int_test(){
  Table test = create(int_cmp, NULL, int_cmp, NULL);
  void * lookup_holder;
  void ** keys_array, ** values_array;
  int i, get_values_int;

  /*is empty table really empty?*/
  size_test(test, 0);

  /*get_values with empty table*/
  if(get_values(test, &get_values_int) != NULL){ invalid(); }
  
  /*insert 255 elements into table, key = i value = i*2*/
  for(i=1; i<=255; i++){
    insert(&test, (void *) (long) i, (void *) (long) (i*2));
  }
 
  /*is the size 255?*/
  size_test(test, 255);
  
  /*lookup start, middle, end*/
  int_lookup_test(test, (void *) (long) 1, (void *) (long) 2);
  int_lookup_test(test, (void *) (long) 125, (void *) (long) 250);
  int_lookup_test(test, (void *) (long) 255, (void *) (long) 510);

  /*lookup something not in table*/
  if(lookup(test, (void *) (long) 666, &lookup_holder) != -1){ invalid(); }
  
  /*check if lookup_holder is set*/
  if(lookup(test, (void *) (long) 125, &lookup_holder) != 1){ invalid(); }
  if((int) (long) lookup_holder != 250){ invalid(); }

  /*test null pointer set as lookup_holders place*/
  if(lookup(test, (void *) (long) 1, NULL) != 1){ invalid(); }
  if((int) (long) lookup_holder != 250){ invalid(); }

  /*get the keys and values arrays, check values size, check keys and values*/
  keys_array = get_keys(test);
  values_array = get_values(test, &get_values_int);
  
  if(get_values_int != 255){
    invalid();
  }
  
  for(i=0; i<255; i++){
    if(int_cmp((void *) (long) (i+1), keys_array[i]) != 0){
      invalid();
    }
    if(int_cmp((void *) (long) ((i+1)*2), values_array[i]) != 0){
      invalid();
    }
  }
  free(keys_array);
  free(values_array);

  /*test if num_values is NULL*/
  if(get_values(test, NULL) != NULL){ invalid(); }

  /*Tests visit with real function*/
  visit(test, int_visitorfn);

  /*this checks if the global variable is equal to the num elements visited*/
  if(int_visitorfn_count != 255)
    invalid();

  /*reset int_visitorfn_count*/
  int_visitorfn_count = 0;

  keys_array = get_keys(test);
  values_array = get_values(test, &get_values_int);
  
  if(get_values_int != 255){
    invalid();
  }
  
  /*tests to make sure after visiting, the same elements are there*/
  for(i=0; i<255; i++){
    if(int_cmp((void *) (long) (i+1), keys_array[i]) != 0){
      invalid();
    }
    if(int_cmp((void *) (long) (((i+1)*2)), values_array[i]) != 0){
      invalid();
    }
  }
  free(keys_array);
  free(values_array);

  /*Tests visit with NULL function*/
  visit(test, NULL);

  /*make sure visit with NULL did not change the global*/
  if(int_visitorfn_count != 0)
    invalid();

  keys_array = get_keys(test);
  values_array = get_values(test, &get_values_int);
 
  /*check that there are still 255 values*/
  if(get_values_int != 255){
    invalid();
  }
  
  for(i=0; i<255; i++){
    if(int_cmp((void *) (long) (i+1), keys_array[i]) != 0){
      invalid();
    }
    if(int_cmp((void *) (long) (((i+1)*2)), values_array[i]) != 0){
      invalid();
    }
  }
  free(keys_array);
  free(values_array);

  /*tests delete with NULL pointer as table*/
  if(delete(NULL, (void *) (long) 0) != -1){
    invalid();
  }
  
  /*tests deleting from start, middle, end*/
  if(delete(&test, (void *) (long) (1)) != 1)
    invalid();
  if(delete(&test, (void *) (long) (125)) != 1)
    invalid();
  if(delete(&test, (void *) (long) (255)) != 1)
    invalid();

  /*checks that size should now be 252*/
  size_test(test, 252);

  /*make sure that the deleted elements really are deleted*/
  if(lookup(test, (void *) (long) 1, &lookup_holder) != -1){ invalid(); }
  if(lookup(test, (void *) (long) 125, &lookup_holder) != -1){ invalid(); }
  if(lookup(test, (void *) (long) 255, &lookup_holder) != -1){ invalid(); }

  /*try deleting something that has been deleted already*/
  if(delete(&test, (void *) (long) (1)) != -1)
    invalid();

  /*insert deleted elements back in, checking it works*/
  if(insert(&test, (void *) (long) (001), (void *) (long) (002)) != 1)
    invalid();
  if(insert(&test, (void *) (long) (125), (void *) (long) (250)) != 1)
    invalid();
  if(insert(&test, (void *) (long) (255), (void *) (long) (510)) != 1)
    invalid();

  /*insert elements again and check for return value of -1*/
  if(insert(&test, (void *) (long) (001), (void *) (long) (003)) != -1)
    invalid();
  if(insert(&test, (void *) (long) (125), (void *) (long) (251)) != -1)
    invalid();
  if(insert(&test, (void *) (long) (255), (void *) (long) (511)) != -1)
    invalid();

  /*make sure that the last failed insertion did not change the values*/
  lookup(test, (void *) (long) 001, &lookup_holder);
  if((int) (long) lookup_holder != 2){ invalid(); }
  lookup(test, (void *) (long) 125, &lookup_holder);
  if((int) (long) lookup_holder != 250){ invalid(); }
  lookup(test, (void *) (long) 255, &lookup_holder);
  if((int) (long) lookup_holder != 510){ invalid(); }

  /*test insert when null pointer passed in as table*/
  if(insert(NULL, (void *) (long) (101), (void *) (long) (010)) != -1){
    invalid();
  }

  /*check if the insertions brought the table back to normal state*/
  keys_array = get_keys(test);
  values_array = get_values(test, &get_values_int);
    /*makes sure the size is back to 255*/  
  if(get_values_int != 255){
    invalid();
  }
  
  for(i=0; i<255; i++){
    if(int_cmp((void *) (long) (i+1), keys_array[i]) != 0){
      invalid();
    }
    if(int_cmp((void *) (long) ((i+1)*2), values_array[i]) != 0){
      invalid();
    }
  }
  free(keys_array);
  free(values_array);

  /*resets the table*/
  reset(&test);

  /*checks that the size after resetting is back to 0*/
  size_test(test, 0);

  /*makes sure lookup on resetted table does not work*/
  if(lookup(test, (void *) (long) 1, &lookup_holder) != -1)
    invalid();

  /*try deleting an element from the empty table*/
  if(delete(&test, (void *) (long) 125) != -1)
    invalid();

  int_visitorfn_count = 0;

  /*make sure after visiting empty table that the global is still 0*/
  visit(test, int_visitorfn);
  if(int_visitorfn_count != 0){ invalid(); }

  reset(&test);

  /*create a new table, adding duplicate values*/ 
  test = create(int_cmp, NULL, int_cmp, NULL);

  for(i=0; i<50; i++){
    insert(&test, (void *) (long) i, (void *) (long) (i*2));
    insert(&test, (void *) (long) i, (void *) (long) (i*2));
  }
  insert(&test, (void *) (long) 49, (void *) (long) 999);

  keys_array = get_keys(test);
  values_array = get_values(test, &get_values_int);
  
  if(get_values_int != 50){
    invalid();
  }
  for(i=0; i<50; i++){
    if(int_cmp((void *) (long) (i), keys_array[i]) != 0){
      invalid();
    }
    if(int_cmp((void *) (long) ((i)*2), values_array[i]) != 0){
      invalid();
    }
  }
  
  free(keys_array);
  free(values_array);


  
  /*just clear at the end free memory n stuff*/
  clear(&test);
}

/*this is the int visitor function*/
static int int_visitorfn(void *key, void *data){
  ++int_visitorfn_count;
  return 1;
}

/*this function will test with key and values both being allocated strings*/
static void string_string_test(){
  Table test = create(string_cmp, NULL, string_cmp, NULL);
  char * insert_me;

  /*is empty table really empty?*/
  size_test(test, 0);

  insert_me = calloc(7, sizeof(char));
  strcpy(insert_me, "hi lol");

  insert(&test, insert_me, "bye");
  
  size_test(test, 1);
  free(insert_me);
}
