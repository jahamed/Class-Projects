/*
Name=Javed Ahamed
Glue Logon=jahamed
UID=109365000
Sec=0202
*/
/*"I pledge on my honor that I have not given or received any unauthorized
assistance on this assignment."*/

/*This source file contains the declarations of the structures that build the 
 *dynamically allocated array data structure*/

typedef struct array_node {
  void *key;
  void *data;
} Node;

typedef struct array {
  Node *node_arr;
  int size;
  int capacity;
} Array;


