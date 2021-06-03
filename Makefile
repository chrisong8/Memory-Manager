
bench: bench.o freemem.o get_mem_stats.o getmem.o mem_utils.o print_heap.o
	gcc -Wall -std=c99 -g -o bench bench.o freemem.o get_mem_stats.o getmem.o mem_utils.o print_heap.o

bench.o: bench.c mem.h
	gcc -Wall -std=c11 -g -c bench.c

freemem.o: freemem.c mem_impl.h
	gcc -Wall -std=c11 -g -c freemem.c

get_mem_stats.o: get_mem_stats.c mem.h mem_impl.h
	gcc -Wall -g -std=c11 -c get_mem_stats.c

getmem.o: getmem.c mem.h mem_impl.h
	gcc -Wall -g -std=c11 -c getmem.c

mem_utils.o:  mem_utils.c mem_impl.h
	gcc -Wall -std=c11 -g -c mem_utils.c

print_heap.o: print_heap.c mem.h mem_impl.h
	gcc -Wall -g -std=c11 -c print_heap.c

clean:
	rm -f *.o bench
