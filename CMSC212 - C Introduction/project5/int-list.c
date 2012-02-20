/*
Name=Javed Ahamed
Glue Logon=jahamed
UID=109365000
Sec=0202
*/
/*"I pledge on my honor that I have not given or received any unauthorized
assistance on this assignment."*/

/*the purpose of this project was to implement linked list (storing ints)
 *functions, specifically having to code get_keys and get_values since the
 *other methods were given to us.*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "int-list.h"

static void verify(void *ptr);
static void clear_helper(List_node *node);
static int exists(int * arrayIn, int size, int element);

static void verify(void *ptr) {
  if (ptr == NULL) {
    printf("Error: memory allocation failed!\n");
    exit(-1);
  }
}

Table create(void) {
  Table new= NULL;
  return new;
}

void reset(Table *table) {
  clear(table);
  if (table != NULL)
    *table= create();
}

int insert(Table *table, int key, int item) {
  List_node *new_node;
  int ignore;

  if (table == NULL || lookup(*table, key, &ignore) == 1)
    return -1;

  new_node= malloc(sizeof(*new_node));
  verify(new_node);

  new_node->key= key;
  new_node->data= item;
  new_node->next= *table;
  *table= new_node;

  return 1;
}

int size(Table table) {
  int ret= 0;
  List_node *curr;

  curr= table;

  while (curr != NULL) {
    curr= curr->next;
    ret++;
  }

  return ret;
}

int lookup(Table table, int key, int *item) {
  List_node *curr;

  curr= table;

  while (curr != NULL) {
    if (curr->key == key) {
      if (item != NULL)
        *item= curr->data;
      return 1;
    }
    curr= curr->next;
  }

  return -1;
}

/*this is a helper function that tells if an element key already 
 *exists in arrayIn, returning 1 if so*/
static int exists(int * arrayIn, int size, int element){
  int i;

  for(i=0; i<size; i++){
    if(arrayIn[i] == element){
      return 1;
    }
  }
  return 0;
}

/*this function returns an allocated array that contains all the keys in the
 *table in increasing sorted order*/
int *get_keys(Table table){ 
  Table temp_table = table;
  int smallest_key;
  int * return_array;
  int i;
  
  return_array = calloc(size(table), sizeof(int));
  verify(return_array);
  
  for(i=0; i<size(table); i++){
    smallest_key = temp_table->key;
    
    while(temp_table != NULL){
      /*conditions for replacing the smallest_key*/
      if(exists(return_array, size(table), smallest_key) == 1 ||
      (temp_table->key < smallest_key && exists(return_array, size(table), 
      temp_table->key) == 0)){
        smallest_key = temp_table->key;
      }

      temp_table = temp_table->next;
    }

    return_array[i] = smallest_key;
    temp_table = table;
  }

  return return_array;
}

/*this function returns all the unique datas in the linked list in increasing
 *order, contained in an allocated array*/
int *get_values(Table table, int *num_values){
  Table temp_table = table;
  int smallest_key;
  int * return_array, * temp_array;
  int i, s;
  int unique_values = 0;

  temp_array = calloc(size(table), sizeof(int));
  /*count the number of unique values in the list and store them to temp_array*/
  while(temp_table != NULL){
    if(exists(temp_array, unique_values, temp_table->data) == 0){
      temp_array[unique_values] = temp_table->data;
      unique_values++;
    }

    temp_table = temp_table->next;
  }
    temp_table = table;


  *num_values = unique_values;
  return_array = calloc(unique_values, sizeof(int));
  verify(return_array);
  
  for(i=0; i<unique_values; i++){
    smallest_key = temp_array[0];
    
    for(s=0; s<unique_values; s++){
      /*conditions for changing the smallest_key*/
      if(exists(return_array, unique_values, smallest_key) == 1 ||
      (temp_array[s] < smallest_key && exists(return_array, unique_values, 
      temp_array[s]) == 0)){
        smallest_key = temp_array[s];
      }
    }

    return_array[i] = smallest_key;
  }
  /*we dont need the temp_array anymore*/
  free(temp_array);
  return return_array;
}


void visit(Table table, Visit_fn visitor_fn) {
  List_node *curr;

  if (visitor_fn == NULL)
    return;

  curr= table;

  while (curr != NULL) {
    (*visitor_fn)(curr->key, curr->data);
    curr= curr->next;
  }
}

int delete(Table *table, int key) {
  List_node *prev= NULL, *curr;

  if (table == NULL)
    return -1;

  curr= *table;

  while (curr != NULL && curr->key != key) {
    prev= curr;
    curr= curr->next;
  }

  if (curr == NULL)
    return -1;

  if (prev != NULL)
    prev->next= curr->next;
  else *table= curr->next;

  free(curr);

  return 1;
}

void clear(Table *table) {
  if (table != NULL) {
    clear_helper(*table);
    *table= NULL;
  }
}

void clear_helper(List_node *node) {
  if (node != NULL) {
    clear_helper(node->next);
    free(node);
    node= NULL;
  }
}
