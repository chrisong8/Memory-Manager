
#include <stdio.h>
#include "mem.h"
#include "mem_impl.h"
#include <assert.h>

FreeNode* runner;
FreeNode* freeList = NULL;
// from mem_impl
uintptr_t totalSize = 0;
uintptr_t freeSize = 0;
uintptr_t freeBlocks = 0;


void check_heap(){ 
    FreeNode* runner = freeList;
    while (runner != NULL && runner->next != NULL) {
    assert(runner->size >= 16);
    assert(runner < runner->next);
    assert(runner->size >= MIN_SIZE);
    uintptr_t tempEnd = (uintptr_t) runner + runner->size + HEADERSIZE;
    assert(tempEnd < (uintptr_t) runner->next);
    assert(tempEnd != (uintptr_t) runner->next);
    runner = runner->next;
  }
}

// Rounds uintptr to the closest number that is > parameter and can be / 16
uintptr_t roundUp(uintptr_t num) {
  if (num % 16 == 0) {
    return num;
  }
  return num / 16 * 16 + 16;
}

// Remove block from free list
void removeB(FreeNode* block) {
  if (block == freeList) {
    freeList = freeList->next;
  } else {
    FreeNode* runner = freeList;
    while (runner->next != block) {
      runner = runner->next;
    }
    runner->next = block->next;
  }
  block->next = NULL;
  freeBlocks--;
  freeSize = freeSize - block->size;
}

// Transform 1 free block into 2 blocks
void split(FreeNode* block, uintptr_t size) {
  uintptr_t reducSize = block->size - (size + HEADERSIZE + BOUND);
  FreeNode* new = (FreeNode*) (((uintptr_t)block) + size + HEADERSIZE + BOUND);
  new->next = block->next;
  new->size = reducSize;
  block->next = new;
  block->size = size;
  freeBlocks++;
  freeSize -= HEADERSIZE + 16;
}

// Insert block into the free list
void insert(FreeNode* block) {
  if (!block) {
    return;
  } else if (!freeList || freeList == NULL) {
    freeList = block;
  } else if ((uintptr_t)freeList >= (uintptr_t)block) {
      block->next = freeList;
      freeList = block;
  } else {
    FreeNode* runner = freeList;
    while (runner->next && ((uintptr_t)runner < (uintptr_t)block)) {
      runner = runner->next;
    }
    block->next = runner->next;
    runner->next = block;
  }
  freeSize = freeSize + block->size;
  freeBlocks++;
}