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

void HashTableAppendElem(HashTable_t* table, char* elem, int hash_func(HashTable_t*, const char*))
{
    int index = hash_func(table, elem);
    //printf("index = %d\n", index);
    LISTAppendAfter(table->arrate_list[index], 0, elem);
}

int hash_func_1 (HashTable_t* table, const char* elem)
{
    int hash = 0;
//    FILE* log = fopen("log.txt", "w");
//    printf("[%s] \"\n", elem);
    while(*elem != '\0')
    {
//        fprintf(log, "%d [%c] %d\n", hash, *elem, *elem);
        hash += *elem;
        elem++;
    }
   
    // printf("hash0 = %d\n", hash);
    hash = hash % table->capasity; 
    // printf("hash = %d\n", hash);

//    fclose(log);
    return hash;
}

char* HashTableGetElem(HashTable_t* table, char* elem, int hash_func(HashTable_t*, const char*))
{
    int index = hash_func(table, elem);
    List_t list = table->arrate_list[index];
    int index_in_list = 0;

    while (list.data[index_in_list] != NULL)
    {
        if (strcmp(elem, list.data[index_in_list]) == 0)
        {
            return list.data[index_in_list];
        }
    
        index_in_list = list.next[index_in_list];
    }

    return NULL;
}
