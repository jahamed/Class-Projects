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
 *using a dynamic array as the data structure of choice instead of a linked 
 *list like the previous project.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "table.h"
#include "array.h"

#define START_CAPACITY 10

static void verify(void *ptr);
static int exists(void ** arrayIn, int size, void * element, Table table,
  int which);

static void verify(void *ptr){
  if(ptr == NULL){
    printf("Error: memory allocation failed!\n");
    exit(-1);
  }
}

/*This function returns a table structure that has been initialized properly, in
 *this implementation using a dynamic array as the contents field of the table*/
Table create(Key_compare_fn compare_key, Key_delete_fn delete_key,
             Data_compare_fn compare_data, Data_delete_fn delete_data){
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
  /*make contents field an Array Wrapper */
  new.contents = malloc(sizeof(Array));
  verify(new.contents);
  ((Array *) new.contents)->node_arr = calloc(10, sizeof(Node));
  /*set the size tracker in the wrapper to 0*/
  ((Array *) new.contents)->size = 0;
  /*set the capacity tracker in the wrapper to 10*/
  ((Array *) new.contents)->capacity = 10;
  return new;
}

/*This function frees the memory associated with the Table param and resets it
 *to an empty table as if create(params...) had just been called again*/
void reset(Table *table){
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
 *replacing the old item if the key is preexisting. The items are inserted in an
 *ascending sorted order by key to make lookup more effecient*/
int insert(Table *table, void *key, void *item){
  void * ignore;
  int i, index_to_insert = 0, size_table = size(*table);
  Array *table_casted = ((Array *) table->contents);

  /*ignore is used just to fulfill the lookup function parameters*/
  if (table == NULL || lookup(*table, key, &ignore) == 1 )
    return -1;
  
  /*check if adding 1 element will require array expansion, then do it*/
  if(size_table + 1 >= (0.75 * current_capacity(*table))){
    table_casted->node_arr = realloc(table_casted->node_arr, 
      current_capacity(*table) * 2 * sizeof(Node));
    verify(table_casted->node_arr);
    table_casted->capacity *= 2;
  }

  /*find index to insert new_node*/
  for(i=0; i<size_table; i++){
    if(table->key_compare_fn(key, table_casted->node_arr[i].key) == -1
      ||table->key_compare_fn(key, table_casted->node_arr[i].key) == 0){
      index_to_insert = i;
      break;
    }else{
      index_to_insert = i+1;
    }
  }

  /*shift elements of the array*/
  for(i=current_capacity(*table)-1; i>index_to_insert; i--){
    table_casted->node_arr[i] = table_casted->node_arr[i-1];
  }
  table_casted->node_arr[index_to_insert].key = key;
  table_casted->node_arr[index_to_insert].data = item;

  /*increment the size variable in the wrapper*/
  table_casted->size++;

  return 1;
}

/*this function returns the number of elements in the table*/
int size(Table table){
  return ((Array *) table.contents)->size;
}

/*this function searches the list for an item with key key, returning 1 if so.
 *If the key is found the param item is set to the data element of that key if
 *item is not NULL*/
int lookup(Table table, void *key, void **item){
  int i, compare_result;
  int size_array = size(table);
  Array *table_casted = ((Array *) table.contents);

  for(i=0; i<size_array; i++){
    compare_result = table.key_compare_fn(table_casted->node_arr[i].key, key);
    if(compare_result == 0){
      if(item != NULL)
        *item = table_casted->node_arr[i].data;
      return 1;
    }else if(compare_result == 1){ /*key is too small not found*/
      return -1;
    }
  }
  return -1;
}

/*this is a helper function which returns 1 if the element exists already in the
 *array passed in of size size.*/
static int exists(void ** arrayIn, int size, void * element, Table table, 
  int which){
  int i;
  
  if(which == 1){
    for(i=0; i<size; i++){
      if(table.data_compare_fn(arrayIn[i], element) == 0){
        return 1;
      }
    }
  }else{
    for(i=0; i<size; i++){
      if(table.key_compare_fn(arrayIn[i], element) == 0){
        return 1;
      }
    }
  }
  return 0;
}

/*This function returns a dynamically allocated array that contains all the keys
 *in the table in increasing sorted order*/
void **get_keys(Table table){
  int i, size_table = size(table);
  void ** return_array;
  Array *table_casted = ((Array *) table.contents);
  
  if(size_table == 0){
    return NULL;
  }

  return_array = calloc(size_table, sizeof(void *));
  verify(return_array);
  
  /*fill the return_array with keys of table*/
  for(i=0; i<size_table; i++){
    return_array[i] = table_casted->node_arr[i].key;
  }
  return return_array;
}

/*This function returns a dynamically allocated array that contains all the
 *unique values present in the table in increasing sorted order*/
void **get_values(Table table, int *num_values){
  void * smallest_value;
  void ** return_array, ** temp_array;
  int a, i, s;
  int unique_values = 0, size_table = size(table);
  Array *table_casted = ((Array *) table.contents);

  if(size_table == 0 || num_values == NULL){
    return NULL;
  }
  
  temp_array = calloc(size_table, sizeof(void *));
  verify(temp_array);

  for(a=0; a<size_table; a++){
    if(exists(temp_array, unique_values, 
      table_casted->node_arr[a].data, table, 1) == 0){
      temp_array[unique_values] = table_casted->node_arr[a].data;
      unique_values++;
    }
  }

  /*sets the param to number unique values*/
  *num_values = unique_values;
  /*uses unique_values to allocate the return array*/
  return_array = calloc(unique_values, sizeof(void *));
  verify(return_array);

  for(i=0; i<unique_values; i++){
    smallest_value = temp_array[0];
    
    for(s=0; s<unique_values; s++){
      /*conditions for resetting smallest_value*/
      if(exists(return_array, unique_values, smallest_value, table, 1) == 1 ||
      ((table.data_compare_fn(temp_array[s], smallest_value) == -1) && 
      exists(return_array, unique_values, temp_array[s], table, 1) == 0)){
        smallest_value = temp_array[s];
      }
    }

    return_array[i] = smallest_value;
  }
  free(temp_array);
  return return_array;
}

/*This function applies the visitor_fn function to each key/data pair in the 
 *Table.*/
void visit(Table table, Visit_fn visitor_fn){
  int size_table = size(table);
  int i;

  if(visitor_fn == NULL)
    return;
  
  for(i=0; i<size_table; i++){
    visitor_fn(((Array *) table.contents)->node_arr[i].key, 
      ((Array *) table.contents)->node_arr[i].data);
  }
}

/*This function deletes the item key combo with param key from the table,
 *returning 1 if successful and -1 if not*/
int delete(Table *table, void *key){
  void *ignore;
  Array *table_casted = ((Array *) table->contents);
  int a, size_table = size(*table);
  int index_to_delete;

  if(table == NULL || lookup(*table, key, &ignore) == -1){
    return -1;
  }

  /*resize array if necessary*/
  if(size(*table) - 1 <= (0.25 * current_capacity(*table)) && 
    (current_capacity(*table) / 2 >= 10)){
    table_casted->node_arr = realloc(table_casted->node_arr, 
      current_capacity(*table) / 2 * sizeof(Node));
    verify(table_casted->node_arr);
    table_casted->capacity /= 2;
  }
  
  /*find the index to delete*/
  for(a=0; a<size_table; a++){
    if(table->key_compare_fn(table_casted->node_arr[a].key, key) == 0){
      index_to_delete = a;
      break;
    }
  }

  /*call data delete and key delete functions on the key and data in this node*/
  if(table->data_delete_fn != NULL){
    table->data_delete_fn(table_casted->node_arr[index_to_delete].data);
  }
  if(table->key_delete_fn != NULL){
    table->key_delete_fn(table_casted->node_arr[index_to_delete].key);
  }

  /*shift elements down when deleting if not deleting last element*/
  if(index_to_delete != size_table-1){
    for(a=index_to_delete; a<size_table; a++){
      table_casted->node_arr[a] = table_casted->node_arr[a+1];
    }
  }

  table_casted->size--;
  return 1;
}

/*this function returns the current capacity of the table, meaning the number of
 *elements it can currently store*/
int current_capacity(Table table){
 return ((Array *) table.contents)->capacity;
}

/*this function frees all the memory associated with the table. It might not be
 *safe to call functions on the Table after it has been freed*/
void clear(Table *table){
  int i, size_table=size(*table);
  Array *table_casted = ((Array *) table->contents);

  /*loop through array, calling key and data delete functions on elements
   *when necessary*/
  for(i=0; i<size_table; i++){
    if(table->data_delete_fn != NULL){
      table->data_delete_fn(table_casted->node_arr[i].data);
    }
    if(table->key_delete_fn != NULL){
      table->key_delete_fn(table_casted->node_arr[i].key);
    }
  }
  free(table_casted->node_arr);
  free(table->contents);
  table->contents = NULL;
}

