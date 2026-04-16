#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef struct 
{
    List_t* arrate_list;
    int capasity;
} HashTable_t;

void HashTableCtor(HashTable_t* table, int capasity);
void HashTableDtor(HashTable_t* table);

void HashTableAppendElem(HashTable_t* table, char* elem, int hash_func(HashTable_t*, const char*));
int hash_func_1 (HashTable_t* table, const char* elem);
char* HashTableGetElem(HashTable_t* table, char* elem, int hash_func(HashTable_t*, const char*));

#define SIZE_LIST 10

#endif
