#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <immintrin.h>

#include "list.h"

typedef struct 
{
    List_t* arrate_list;
    int capasity;
} HashTable_t;

void HashTableCtor (HashTable_t* table, int capasity);
void HashTableDtor (HashTable_t* table);

void  HashTableAppendElem (HashTable_t* table, char* elem, uint32_t hash_func(HashTable_t*, const char*));
char* HashTableSearchElem (HashTable_t* table, const char* elem, uint32_t hash_func(HashTable_t*, const char*));

extern "C" uint32_t hash_func_crc32_s(HashTable_t* table, const char* elem);

uint32_t hash_func_0            (HashTable_t* table, const char* elem);
uint32_t hash_func_sum          (HashTable_t* table, const char* elem);
uint32_t hash_func_first_letter (HashTable_t* table, const char* elem);
uint32_t hash_func_strlen       (HashTable_t* table, const char* elem);
uint32_t hash_func_roll         (HashTable_t* table, const char* elem);
uint32_t hash_func_crc32        (HashTable_t* table, const char* elem);

void HashTablePrint(HashTable_t* table);

#define SIZE_LIST 10
#define HASH_TABLE_SIZE 4001

#endif
