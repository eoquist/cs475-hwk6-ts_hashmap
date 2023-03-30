/*
 * File: main.c
 * Author: Emilee Oquist
 * Version: 1.0
 * License: MIT
 *
 * Description: Tests the thread-safe hashmap 'ts_hashmap.c' file
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "ts_hashmap.h"

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("Usage: %s <num threads> <hashmap capacity>\n", argv[0]);
		return 1; // !!!
	}
	else if (argc > 3)
	{
		printf("Arguments for %s that will be used are: <num threads %s > <hashmap capacity %s >\n", argv[0], argv[1], argv[2]);
		printf("All other arguments for %s will be lost.\n", argv[0]);
		// !!!
	}

	if( argv[1] >= 0 ){
		printf("You must have give the hashmap a capacity larger than 0");
		// !!!
	}

	// Write your test
	srand(time(NULL));
	int num_threads = atoi(argv[1]);
	int capacity = (unsigned int)atoi(argv[2]);
	ts_hashmap_t *ts_hashmap = initmap(capacity);

	// Index Calculation In the example above, to calculate the array index, you take the key of the entry and
	// (1) cast it into an unsigned int, then
	// (2) modulo by the size of the array. That should tell you which array position to hone in on.
	// Because the array element points to the head of the entry list (or NULL), you can then walk the list of entries to search for a key.
	
	
	
	// create any number of threads, and each thread continuously puts/gets/dels 1000s of keys into the same shared hashmap. 
	// Use the printmap() function that I provided to print out the contents of the map after the threads join back up.

    // You may want to figure out how to “control” the randomness your tests so that you can repeat the same test on a 
	// single-threaded version vs. a multi-threaded version and produce the same output. 



	return 0;
}
