#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h> //for random_seed
#include "mem.h"

// excecute large number of calls to freemem and getmem
// implement --> bench [ntrials] [pctget] [pctlarge] [small_limit] [large_limit] [random_seed]
int main(int argc, char** argv){
  int ntrials = 10000;
  int pctget =  50;
  int pctlarge =  10;
  int small_limit = 200;
  int large_limit = 20000;
  int random_seed = clock();
  if (argc > 1){
    ntrials = atoi(argv[1]);
  }
  if (argc > 2) {
    pctget = atoi(argv[2]);
  }
  if (argc > 3){
    pctlarge = atoi(argv[3]);
  }
  if (argc > 4){
    small_limit = atoi(argv[4]);
  }
  if (argc > 5){
    large_limit = atoi(argv[5]);
  }
  if (argc > 6){
    random_seed = atoi(argv[6]);
  }


  srand(random_seed);
  void* memory[ntrials];
  int mem_index = 0;
  int mem_size;
  clock_t t;
  uintptr_t total_size = 0;
  uintptr_t total_free = 0;
  uintptr_t n_free_blocks = 0;
  t = clock();
  for (int i = 0; i < ntrials; i++){
    if (rand() % 100 < pctget){ // getting memory
      if (rand() % 100 < pctlarge){ //request large block greater than small_limit
	mem_size = rand() % (large_limit - small_limit) + small_limit; 
      }else{ //request small block
	mem_size = rand() % small_limit + 1; 
      }
      memory[mem_index] = getmem(mem_size);
      //initializing first 16 bytes to 0xFE
      if (memory[mem_index] != NULL){
	uintptr_t mymem = (uintptr_t) memory[mem_index];
	int j = 0;
	while (j < 16 && j < mem_size){
	  *((unsigned char*)(mymem+j)) = 0xFE;
	  j++;
	}
      }
      mem_index++;
    }else{ //free memory
      if (mem_index > 0){
	// free a random block and update memory[] in O(1)
	int free_index = rand() % mem_index;
	freemem(memory[free_index]);
	memory[free_index] = memory[mem_index - 1]; // fill in gap wth memory at the end
	mem_index--;
      }
      
    }
    //printing to stdout
    if(i % (ntrials / 10) == 0){
      get_mem_stats(&total_size, &total_free, &n_free_blocks);
      clock_t curr = clock() - t;
      printf("Total CPU time: %f seconds \n", ((float)curr)/CLOCKS_PER_SEC);
      printf("Total amount of storage acquired: %ld \n",total_size);
      printf("Blocks on free list: %ld \n", n_free_blocks);
      printf("Average number of bytes in free storage blocks: %f \n\n", total_free / (double) n_free_blocks); 
    }

  }
  
  return 0;
}
