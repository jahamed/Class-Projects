/*
Name=Javed Ahamed
Glue Logon=jahamed
UID=109365000
Sec=0202
*/
/*"I pledge on my honor that I have not given or received any unauthorized
assistance on this assignment."*/

/*the purpose of this file is to modify the int_main file to work with the void*
 *implementation of either the list shared library of the array shared lib*/
#include <stdio.h>
#include <stdlib.h>
#include "table.h"

static int compare_ints(const void * x, const void * y);

/*this is the integer comparison function that must be passed into create*/
static int compare_ints(const void * x, const void * y){
  if(((int) (long) x) == ((int) (long) y)){
    return 0;
  }else if(((int) (long) x) < ((int) (long) y)){
    return -1;
  }else{
    return 1;
  }
}

int main() {
  int number_read, cur_size;
  Table list= create(compare_ints, NULL, compare_ints, NULL);
  void * occurrences, *large_key, *large_value;
  void ** key_list;
  while (!feof(stdin)) {

    /*read in the number from the file*/
    scanf("%d ", &number_read);

    if (lookup(list, (void *) (long) number_read, &occurrences) == 1) {

      delete(&list, (void *) (long) number_read);
      insert(&list, (void *) (long) number_read, 
            (void *) ((long) occurrences + 1));

    } else insert(&list, (void *) (long) number_read, 
                 (void *) ((long) 1));

  }

  cur_size= size(list);
  while (cur_size != 0) {

    key_list= get_keys(list);
    large_key= key_list[cur_size - 1];
    lookup(list, large_key, &large_value);
    printf("%d occurred %d time(s)\n", (int) (long) large_key, 
          (int) (long) large_value);
    delete(&list, large_key);
    cur_size= size(list);
    free(key_list);

  }
  return 0;
}
