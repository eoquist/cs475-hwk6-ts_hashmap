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
	rand(); // testing purposes
	int num_threads = 25;
	int capacity = 1000;
	ts_hashmap_t *ts_hashmap = initmap(capacity);

	// allocate space to hold threads
	pthread_t *threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
	for (int i = 0; i < num_threads; i++)
	{
		// create args
		int key = rand() % capacity;
		int value = rand();
		thread_args args = {ts_hashmap, key, value};
		pthread_create(&threads[i], NULL, put(ts_hashmap,key,value), NULL);
		// pthread_create(&threads[i], NULL, get, &args);
		// pthread_create(&threads[i], NULL, del, &args);
		// pthread_create(&threads[i], NULL, lf, &args);
	}
	// wait for threads to finish
	for (int i = 0; i < num_threads; i++)
	{
		pthread_join(threads[i], NULL);
	}

	// clean up
	free(threads);
	threads = NULL;

	return 0;
}
