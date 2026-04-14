#include "../headers/hash_table.h"

void HashTableCtor(HashTable_t* table, int capasity)
{
    table->arrate_list = (List_t* ) calloc(capasity, sizeof(List_t));

    for (int i = 0; i < capasity; i++)
    {
        LISTCTOR(table->arrate_list[i], SIZE_LIST);
    }

    table->capasity = capasity;
}

void HashTableDtor(HashTable_t* table)
{
    for (int i = 0; i < table->capasity; i++)
        ListDtor(&table->arrate_list[i]);

    free(table->arrate_list);    
}

void HashTableAppendElem(HashTable_t* table, char* elem, int hash_func(HashTable_t*, char*))
{
    int index = hash_func(table, elem);
    LISTAppendAfter(table->arrate_list[index], 0, elem);
}

int hash_func_1 (HashTable_t* table, char* elem)
{
    int hash = 0;

    while(*elem != '\0')
    {
        hash += *elem;
        elem++;
    }

    hash = hash % table->capasity; 
    return hash;
}

