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
 * @param map a pointer to the map
 * @param key a key to search
 * @return the value associated with the given key, or INT_MAX if key not found
 */
int get(ts_hashmap_t *map, int key)
{
  // TODO
  return INT_MAX;
}

/**
 * Associates a value associated with a given key.
 * @param map a pointer to the map
 * @param key a key
 * @param value a value
 * @return old associated value, or INT_MAX if the key was new
 */
int put(ts_hashmap_t *map, int key, int value)
{
  // TODO
  return INT_MAX;
}

/**
 * Removes an entry in the map
 * @param map a pointer to the map
 * @param key a key to search
 * @return the value associated with the given key, or INT_MAX if key not found
 */
int del(ts_hashmap_t *map, int key)
{
  // TODO
  return INT_MAX;
}

/**
 * @return the load factor of the given map
 */
double lf(ts_hashmap_t *map)
{
  return (double)map->size / map->capacity;
}

/**
 * Prints the contents of the map
 */
void printmap(ts_hashmap_t *map)
{
  for (int i = 0; i < map->capacity; i++)
  {
    printf("[%d] -> ", i);
    ts_entry_t *entry = map->table[i];
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