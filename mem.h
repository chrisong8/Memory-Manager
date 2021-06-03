

#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stdio.h>
// Returns a pointer to a new block of size bytes of memory
void* getmem(uintptr_t size);

// Puts block of storage at location p back into free storage
void freemem(void* p);

// Stores statistics about the current state of the memory amnager
// total_size - total ammount of bytes
// tota_free - total ammount of storage in bytes that is on the free list
// n_free_blocks - total numer of blocks stored on the free list
void get_mem_stats(uintptr_t* total_size,
		   uintptr_t* total_free,
		   uintptr_t* n_free_blocks);

// Prints a formatted list on file f showing the blocks on the free list.
// each line of output describes one freee block in hexadecimal
void print_heap(FILE* f);

#endif
