#if !defined(NODE_H)
#define NODE_H


typedef struct node {
  char ch;
  struct node *next;
} Node;


Node* initialize(char char_in, Node* next_in);
char returnchar(Node * tempnode);

#endif
