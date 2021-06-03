/*
 * Header file containing decleration of function used internally 
 * in the memory manager implementaion
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define MIN_SIZE 96
// sizeof(uintptr), just making life easier
#define HEADERSIZE 16
#define BOUND 16

// data structure for a single block of memory
typedef struct FreeNode {
  uintptr_t size;
  struct FreeNode* next;
} FreeNode;

// storage acquired
uintptr_t totalSize;
// free storage, free block count
uintptr_t totfree;
uintptr_t numblocks;
// head/front
FreeNode* freeList;

void check_heap();
void removeB(FreeNode* block);
void split(FreeNode* block, uintptr_t blockSize);
void insert(FreeNode* block);