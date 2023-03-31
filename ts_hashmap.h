#include <pthread.h>

// A hashmap entry stores the key, value
// and a pointer to the next entry
typedef struct ts_entry_t
{
   int key;
   int value;
   struct ts_entry_t *next;
   pthread_mutex_t lock;
} ts_entry_t;

/**
 * To support arbitrary key and value types, you can use a combination
 * of void pointers and function pointers to handle the different types
 * of data that can be stored.
 */

// A hashmap contains an array of pointers to entries,
// the capacity of the array, and the size (number of entries stored)
typedef struct ts_hashmap_t
{
   ts_entry_t **table;
   int capacity;
   int size;
   pthread_mutex_t lock;
} ts_hashmap_t;

typedef struct thread_args
{
   ts_hashmap_t *hashmap;
   int key;
   int value;
} thread_args;

// function declarations
ts_hashmap_t *initmap(int capacity);
int get(ts_hashmap_t *hashmap, int key);
int put(ts_hashmap_t *hashmap, int key, int value);
int del(ts_hashmap_t *hashmap, int key);
double lf(ts_hashmap_t *hashmap);
void printmap(ts_hashmap_t *hashmap);