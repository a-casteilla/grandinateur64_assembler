#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pointer.h"

#define NUMBER_OF_POINTERS 25LU

int
main ()
{
  void * list[256];
  void * random_pointer;
  size_t len_of_list;
  bool has_passed = true;

  for (size_t i = 0; i < 256; i++) {
    if (i == NUMBER_OF_POINTERS) {
      list[i] = NULL;
    } else {
      list[i] = malloc(20 * i);
    }
  }

  /* Test of pointerlen with a non-void string of pointers */
  len_of_list = pointerlen((const void **)list);

  if (len_of_list == NUMBER_OF_POINTERS) {
    fprintf(stderr, "pointerlen with non-empty input: OK \n");
  } else {
    fprintf(stderr, "pointerlen with non-empty input: \x1b[31mFAILED\x1b[0m\n");
    fprintf(stderr, "Expected : %lu\n", NUMBER_OF_POINTERS);
    fprintf(stderr, "Actual output : %lu\n", len_of_list);
  }

  /* Test of pointerlen with a void string of pointers */
  random_pointer = list;
  free(list[0]);
  list[0] = NULL;

  len_of_list = pointerlen((const void **)list);

  if (len_of_list == 0) {
    fprintf(stderr, "pointerlen with empty input: OK \n");
  } else {
    fprintf(stderr, "pointerlen with empty input: \x1b[31mFAILED\x1b[0m\n");
    fprintf(stderr, "Expected : 0\n");
    fprintf(stderr, "Actual output : %lu\n", len_of_list);
  }

  /* Test of mempointer with a non-void table */
  for (size_t i = 0; i < NUMBER_OF_POINTERS; i++) {
    has_passed &=
      (mempointer((const void **)list, list[i], NUMBER_OF_POINTERS)
       == (const void **)(list + i));
  }

  has_passed &= (mempointer((const void **)list, random_pointer, NUMBER_OF_POINTERS) == NULL);

  if (has_passed) {
    fprintf(stderr, "mempointer with non-empty input: OK \n");
  } else {
    fprintf(stderr, "mempointer with non-empty input: \x1b[31mFAILED\x1b[0m\n");
  }

  /* Test of mempointer with a void table */
  for (size_t i = 0; i < NUMBER_OF_POINTERS; i++) {
    has_passed &=
      (mempointer((const void **)list, list[i], 0) == NULL);
  }

  has_passed &= (mempointer((const void **)list, random_pointer, NUMBER_OF_POINTERS) == NULL);

  if (has_passed) {
    fprintf(stderr, "mempointer with empty input: OK \n");
  } else {
    fprintf(stderr, "mempointer with empty input: \x1b[31mFAILED\x1b[0m\n");
  }

  exit(EXIT_SUCCESS);
}
