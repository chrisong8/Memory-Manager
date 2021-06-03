
#include <stdio.h>
#include "mem.h"
#include "mem_impl.h"

void print_heap(FILE * f) {
  FreeNode* head = freeList;
  while (head) {
    uintptr_t address = (uintptr_t)head;
    fprintf(f, "Address: %lu, Size: %lu \n", address, head->size);
    head = head->next;
  }
  fclose(f);
}