
#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include "mem_impl.h"

#define BLOCK 10000000

void* getmem(uintptr_t size) {
  check_heap();
  if (size <= 0) {
    return NULL;
  }
  
  uintptr_t blockSize;
  if (size % 16 == 0) {
    blockSize = size;
  } else {
    blockSize = (size / 16) * 16 + 16;
  }
  
  FreeNode* head = freeList;
  if (blockSize < MIN_SIZE) {
    blockSize = MIN_SIZE;
  }
  while (head && head->size < blockSize) {
    head = head->next;
  }
  if (!head) {
    uintptr_t more = blockSize + HEADERSIZE + BLOCK + BOUND;
    head = (FreeNode*) malloc(more);
    head->size = blockSize + BLOCK;
    head->next = NULL;
    totalSize += more;
    insert(head);
  }
  if (head->size > (blockSize + MIN_SIZE + HEADERSIZE)) {
    split(head, blockSize);
  }
  
  removeB(head);

  void* ans = (void*) ((uintptr_t)head) + HEADERSIZE;
  check_heap();
  return ans;
}
