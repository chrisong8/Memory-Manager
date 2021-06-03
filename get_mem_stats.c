
#include <stdio.h>
#include <stdint.h>

#include "mem.h"
#include "mem_impl.h"

// Stores statistics about the current state of the memory manager
// total_size - total ammount of storage in bytes aquired by the memory manager
// total_free - total ammount of storage in bytes that is stored on the free list
// n_free_blocks - total ammount of individual blocks stored on free list
void get_mem_stats(uintptr_t* total_size,
		   uintptr_t* total_free,
		   uintptr_t* n_free_blocks){
  //not sure how to ensure we keep 
  FreeNode* temp = freeList;
  uintptr_t totsize = 0;
  uintptr_t totfree = 0;
  uintptr_t numblocks = 0;
  while(temp != NULL){
    totfree +=temp->size;
    numblocks++;
    temp = temp->next;
  }
  *total_size = totsize;
  *total_free = totfree;
  *n_free_blocks = numblocks;
  
}
