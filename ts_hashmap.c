/*
 * File: ts_hashmap.c
 * Author: Emilee Oquist
 * Version: 1.0
 * License: MIT
 *
 * Description: Implements a simplified version of a classic dynamically
 * allocated hashmap in C that introduces the concept of mutex locks and
 * how they're used to make thread-safe structures.
 */

// initialize the lock
// pthread_mutex_t *lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
// pthread_mutex_init(lock, NULL);
// pthread_mutex_lock(&hashmap->lock);

// done with lock; deallocate
// pthread_mutex_destroy(lock);
// free(lock);
// lock = NULL;
// pthread_mutex_unlock(&hashmap->lock);

#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ts_hashmap.h"

/**
 * Creates a new thread-safe hashmap.
 * @param capacity initial capacity of the hashmap.
 * @return a pointer to a new thread-safe hashmap.
 */
ts_hashmap_t *initmap(int capacity)
{
  ts_hashmap_t *hashmap = malloc(sizeof(ts_hashmap_t));

  // Note to self: -> notation is needed because hashmap is a ts_hashmap_t pointer
  hashmap->table = malloc(capacity * sizeof(ts_entry_t *));
  hashmap->capacity = capacity;
  hashmap->size = 0;

  return hashmap;
}


/**
 * Obtains the value associated with the given key.
 * @param hashmap a pointer to the hashmap
 * @param key a key to search
 * @return the value associated with the given key, or INT_MAX if key not found
 */
int get(ts_hashmap_t *hashmap, int key)
{
  int value = INT_MAX;
  for (int i = 0; i < hashmap->capacity; i++)
  {
    pthread_mutex_lock(&hashmap->lock);
    ts_entry_t *entry = hashmap->table[i];
    while (entry != NULL)
    {
      if (entry->key == key)
      {
        value = entry->value;
      }
    }
    pthread_mutex_unlock(&hashmap->lock);
  }
  return value;
}


/**
 * Associates a value associated with a given key.
 * @param hashmap a pointer to the hashmap
 * @param key a key
 * @param value a value
 * @return old associated value, or INT_MAX if the key was new
 */
int put(ts_hashmap_t *hashmap, int key, int value)
{
  int hash = key % hashmap->capacity;
  pthread_mutex_lock(&hashmap->lock);
  ts_entry_t *entry = hashmap->table[hash];

  while (entry != NULL)
  {
    if (entry->key == key)
    {
      int old_value = entry->value;
      entry->value = value;

      pthread_mutex_unlock(&hashmap->lock);
      return old_value;
    }
    entry = entry->next;
  }

  ts_entry_t *new_entry = malloc(sizeof(ts_entry_t));
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = entry;

  hashmap->size++;
  pthread_mutex_unlock(&hashmap->lock);
  return INT_MAX;
}


/**
 * Removes an entry in the hashmap.
 * @param hashmap a pointer to the hashmap
 * @param key a key to search
 * @return the value associated with the given key, or INT_MAX if key not found
 */
int del(ts_hashmap_t *hashmap, int key)
{
  int hash = key % hashmap->capacity;
  int old_value = INT_MAX;
  pthread_mutex_lock(&hashmap->lock);
  ts_entry_t *previous_entry = NULL;
  ts_entry_t *entry = hashmap->table[hash];

  while (entry != NULL)
  {
    if (entry->key == key) // entry we want to get rid of
    {
      old_value = entry->value;
      if (previous_entry == NULL) { // entry is head
        hashmap->table[hash] = entry->next;
      }
      else{ 
        previous_entry->next = entry->next; // connect the prev and next
      }
      hashmap->size--;
      pthread_mutex_unlock(&hashmap->lock);
      return old_value;
    }
    previous_entry = entry;
    entry = entry->next;
  }

  pthread_mutex_unlock(&hashmap->lock);
  return old_value;
}


/**
 * @return the load factor of the given hashmap
 */
double lf(ts_hashmap_t *hashmap)
{
  
  return (double)hashmap->size / (double)hashmap->capacity;
}


/**
 * Prints the contents of the hashmap
 */
void printmap(ts_hashmap_t *hashmap)
{
  for (int i = 0; i < hashmap->capacity; i++)
  {
    printf("[%d] -> ", i);
    ts_entry_t *entry = hashmap->table[i];
    while (entry != NULL)
    {
      printf("(%d,%d)", entry->key, entry->value);
      if (entry->next != NULL)
        printf(" -> ");
      entry = entry->next;
    }
    printf("\n");
  }
}