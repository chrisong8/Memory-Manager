
#include <stdint.h>
#include <stdio.h>


#include "mem.h"
#include "mem_impl.h"

// Returns a block of storage at location p back to the pool of free storage.
// If p is null, function returns immedietly
// If block is adjactnt to one or more free blocks, free blocks should
// be combines into a single larger block
void freemem(void* p){
  check_heap();
  uintptr_t headerSize = 16;
  if (p == NULL){
    return;
  }
  FreeNode* pNode = (FreeNode*)((uintptr_t)p - headerSize);
  FreeNode* temp = freeList;
  

  if (temp == NULL){ //freeList is empty
    freeList = pNode;
    freeList->next = NULL;
  } else if ((uintptr_t)pNode < (uintptr_t)temp){ //inserted at front
      pNode->next = temp;
      freeList = pNode;
      temp = pNode;
  }else{ // find spot to insert
    while ((uintptr_t)pNode > (uintptr_t)temp->next && temp->next != NULL){
      temp = temp->next;
    }
    pNode->next = temp->next;
    temp->next = pNode;
  }
  
  //combining nodes
  // do we need to combine bottom of temp with top of p
  if ((uintptr_t)temp + temp->size + headerSize == (uintptr_t) pNode){
    temp->size += pNode->size + headerSize;
    temp->next = pNode->next;
  }
  // do we need to combine end of p with the next node
  if ((uintptr_t)pNode + pNode->size + headerSize == (uintptr_t)pNode->next && pNode->next != NULL){
    pNode->size += pNode->next->size + headerSize;
    pNode->next = pNode->next->next;
  }
  check_heap();
}
