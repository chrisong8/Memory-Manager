/*
 * Header file containing declaration of function used internally 
 * in the memory manager implementaion
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define MIN_SIZE 7200
#define HEADERSIZE 16
#define BOUND 8

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