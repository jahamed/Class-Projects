/*
Name=Javed Ahamed
Glue Logon=jahamed
UID=109365000
Sec=0202
*/
/*"I pledge on my honor that I have not given or received any unauthorized
assistance on this assignment."*/

/*The purpose of this project was to implement a generic Table structure that
 *could store non predetermined data types and one that has the ability to use
 *different data structures to store these types. However in this project we are
 *using a linked list as the data structure of choice.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "table.h"
#include "list.h"


static void verify(void *ptr);
static void clear_helper(List_node *node, Table *table);
static int exists(void ** arrayIn, int size, void * element);

/*This function verifies if an allocation failed or not*/
static void verify(void *ptr) {
  if (ptr == NULL) {
    printf("Error: memory allocation failed!\n");
    exit(-1);
  }
}

/*This function returns a table structure that has been initialized properly, in
 * this implementation using a linked list as the contents field of the table*/
Table create(Key_compare_fn compare_key, Key_delete_fn delete_key,
             Data_compare_fn compare_data, Data_delete_fn delete_data) {
  Table new;
  /*the comparison functions cannot be NULL*/
  if(compare_key == NULL || compare_data == NULL){
    printf("Error: NULL pointer passed in as comparison function.\n");
    exit(-1);
  }

  new.key_compare_fn = compare_key;
  new.data_compare_fn = compare_data;
  new.key_delete_fn = delete_key;
  new.data_delete_fn = delete_data;
  new.contents = malloc(sizeof(List));
  verify(new.contents);
  ((List *) (new.contents))->head = NULL;
  return new;
}

/*This function frees the memory associted with the Table param and resets it to
 *an empty table*/
void reset(Table *table) {
  Table new;
  if (table != NULL){
    /*the Table new keeps the Table param's function pointers*/
    new = create(table->key_compare_fn, table->key_delete_fn, 
                 table->data_compare_fn, table->data_delete_fn);
    clear(table);
    *table= new;
  }
}

/*This function inserts the data item with corresponding key into the Table, not
 *replacing the old item if the key is preexisting*/
int insert(Table *table, void *key, void *item) {
  List_node *new_node, *temp_node;
  void * ignore;
  
  /*ignore is used just to fulfill the lookup function parameters*/
  if (table == NULL || lookup(*table, key, &ignore) == 1)
    return -1;

  new_node= malloc(sizeof(List_node));
  verify(new_node);

  temp_node= ((List *) table->contents)->head;
  /*initialize the new node*/
  new_node->key= key;
  new_node->data= item;
  new_node->next= NULL;
  /*this means the list is empty*/
  if(temp_node == NULL){
    ((List *) table->contents)->head = new_node;
    return 1;
  }
  /*otherwise if the list is not empty add to end*/
  while(temp_node->next != NULL){
    temp_node= temp_node->next;
  }
  temp_node->next= new_node;
  return 1;
}

/*this function returns the number of items in the table*/
int size(Table table) {
  int ret= 0;
  List_node *curr = ((List *) table.contents)->head;

  while(curr != NULL) {
    curr= curr->next;
    ret++;
  }

  return ret;
}

/*this function searches the list for an item with key key, returning 1 if so.
 *If a key is found the variable item is set to the data of that key*/
int lookup(Table table, void *key, void **item) {
  List_node *curr = ((List *) table.contents)->head;

  while (curr != NULL) {
    if (table.key_compare_fn(curr->key, key) == 0) {
      if (item != NULL)
        *item= curr->data;
      return 1;
    }
    curr= curr->next;
  }

  return -1;
}

/*this is a helper function which returns 1 if the element exists already in the
 *array passed in of size size.*/
static int exists(void ** arrayIn, int size, void * element){
  int i;

  for(i=0; i<size; i++){
    if(arrayIn[i] == element){
      return 1;
    }
  }
  return 0;
}

/*This function returns an allocated array that contains all the keys present in
 *the table in increasing order using the comparison function*/
void **get_keys(Table table){ 
  List_node * temp_node = ((List *) table.contents)->head;
  void * smallest_key;
  void ** return_array;
  int i;
 
  if(size(table) == 0){
    return NULL;
  }

  return_array = calloc(size(table), sizeof(void *));
  verify(return_array);

  for(i=0; i<size(table); i++){
    smallest_key = temp_node->key;
    
    while(temp_node != NULL){
      /*conditions for resetting the smallest key*/
      if(exists(return_array, size(table), smallest_key) == 1 ||
      ((table.key_compare_fn(temp_node->key, smallest_key) == -1 && 
      exists(return_array, size(table), 
      temp_node->key) == 0))){
        smallest_key = temp_node->key;
      }

      temp_node = temp_node->next;
    }

    return_array[i] = smallest_key;
    temp_node = ((List *) table.contents)->head;
  }

  return return_array;
}

/*this function returns an allocated array that contains all the unique data
 * values in the table in increasing order*/
void **get_values(Table table, int *num_values){
  List_node * temp_node = ((List *) table.contents)->head;
  void * smallest_value;
  void ** return_array, ** temp_array;
  int i, s;
  int unique_values = 0;

  if(size(table) == 0 || num_values == NULL){
    return NULL;
  }

  temp_array = calloc(size(table), sizeof(void *));
  verify(temp_array);
  /*count the number of unique values in the list and store them to temp_array*/
  while(temp_node != NULL){
    if(exists(temp_array, unique_values, temp_node->data) == 0){
      temp_array[unique_values] = temp_node->data;
      unique_values++;
    }

    temp_node = temp_node->next;
  }

  temp_node = ((List *) table.contents)->head;
  /*sets the param to number unique values*/
  *num_values = unique_values;
  /*uses unique values to allocate the return array*/
  return_array = calloc(unique_values, sizeof(void *));
  verify(return_array);
  
  for(i=0; i<unique_values; i++){
    smallest_value = temp_array[0];
    
    for(s=0; s<unique_values; s++){
      /*conditions for resetting smallest_value*/
      if(exists(return_array, unique_values, smallest_value) == 1 ||
      ((table.data_compare_fn(temp_array[s], smallest_value) == -1) && 
      exists(return_array, unique_values, temp_array[s]) == 0)){
        smallest_value = temp_array[s];
      }
    }

    return_array[i] = smallest_value;
  }
  free(temp_array);
  return return_array;
}

/*This function traverses the table, applying the visiter_fn function to each
 * key/data pair*/
void visit(Table table, Visit_fn visitor_fn) {
  List_node *curr;

  if (visitor_fn == NULL)
    return;

  curr= ((List *) table.contents)->head;

  while (curr != NULL) {
    (*visitor_fn)(curr->key, curr->data);
    curr= curr->next;
  }
}

/*This function removes the item referenced by key key from the Table*/
int delete(Table *table, void *key) {
  List_node *prev= NULL, *curr;
  void * ignore;

  if(table == NULL)
    return -1;
  
  /*key cannot be found to delete*/
  if(lookup(*table, key, &ignore) == -1){
    return -1;
  }

  curr= ((List *) table->contents)->head;

  while (curr != NULL && table->key_compare_fn(curr->key, key) != 0) {
    prev= curr;
    curr= curr->next;
  }

  if (curr == NULL)
    return -1;

  if (prev != NULL)
    prev->next= curr->next;
  else ((List *) table->contents)->head= curr->next;

  free(curr);

  return 1;
}

/*This function returns the current capacity of a linked list, which is 
 *really how much memory is available. So This returns INT_MAX*/
int current_capacity(Table table){
  return INT_MAX;
}

/*This function frees all memory associated with the table param*/
void clear(Table *table) {
  if (table != NULL) {
    clear_helper(((List *) table->contents)->head, table);
    free(table->contents);
    table->contents = NULL;
  }
}

/*this is a helper function for use with clear*/
void clear_helper(List_node *node, Table *table) {
  if (node != NULL) {
    clear_helper(node->next, table);
    if(table->data_delete_fn != NULL){
      table->data_delete_fn(node->data);
    }
    if(table->key_delete_fn != NULL){
      table->key_delete_fn(node->key);
    }
    free(node);
    node= NULL;
  }
}
