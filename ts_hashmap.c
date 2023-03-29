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

#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ts_hashmap.h"

/**
 * Creates a new thread-safe hashmap.
 *
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
    ts_entry_t *entry = hashmap->table[i];
    while (entry != NULL)
    {
      if (entry->key == key)
      {
        value = entry->value;
      }
    }
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
  // any issues if you try to put(hashmap, INT_MAX, value) ?
  int hash = hash(key) % hashmap->capacity;

  pthread_mutex_lock(&hashmap->mutex);
  ts_entry_t *entry = hashmap->table[hash];

  while (entry != NULL)
  {
    if (entry->key == key){
      int old_value = entry->value;
      entry->value = value;
      pthread_mutex_unlock(&hashmap->mutex);
      return old_value;
    }
    entry = entry->next;
  }

  // doesn't exist
  // make new entry at idx size
  // update pointer
  // update size

  // if adding exceeds capacity ? allow it?
  ts_entry_t *new_entry = malloc(sizeof(ts_entry_t));
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = hashmap->table[hash];
  hashmap->table[hash] = new_entry;
  hashmap->size++;

  pthread_mutex_unlock(&hashmap->mutex);

  return INT_MAX;
}

/**
 * Removes an entry in the hashmap
 * @param hashmap a pointer to the hashmap
 * @param key a key to search
 * @return the value associated with the given key, or INT_MAX if key not found
 */
int del(ts_hashmap_t *hashmap, int key)
{
  // TODO

  return INT_MAX;
}

/**
 * @return the load factor of the given hashmap
 */
double lf(ts_hashmap_t *hashmap)
{
  return (double)hashmap->size / (double)hashmap->capacity;
}

/**
 * Hashing function
 */
int hash(int key)
{
  int hash = INT_MAX;

  return hash;
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