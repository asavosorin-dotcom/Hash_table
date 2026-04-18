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
    List_t list = table->arrate_list[index];
    char* list_elem = list.data[1];

    for (int index_elem = 1; list_elem != NULL; list_elem = list.data[index_elem++])
    {
        if (strcmp(list_elem, elem) == 0) return ;
    }

    LISTAppendAfter(table->arrate_list[index], 0, elem);
}

int hash_func_0 (HashTable_t* table, const char* elem)
{
    return 0;
}

int hash_func_sum (HashTable_t* table, const char* elem)
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

int hash_func_first_letter(HashTable_t* table, const char* elem)
{
    int hash = *elem %  table->capasity;
    return hash;
}

int hash_func_strlen(HashTable_t* table, const char* elem)
{
    int hash = strlen(elem) % table->capasity;
    return hash;
}

int hash_func_roll(HashTable_t* table, const char* elem)
{
    int hash = 0;
    int mask = 0;

    while (*elem != '\0')
    {
        mask = hash & (1 << 31);
        hash = (hash << 1) + mask;
    }

    hash = hash % table->capasity;
    return hash;
}

char* HashTableSearchElem(HashTable_t* table, char* elem, int hash_func(HashTable_t*, const char*))
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

void HashTablePrint(HashTable_t* table)
{
    FILE* exel_table = fopen("./debug/table.csv", "w");
    List_t* list = &table->arrate_list[0];
    char* elem = list->data[1];

    for (int i = 0; i < table->capasity; i++)
    {
        list = &table->arrate_list[i];
        elem = list->data[1];

        int index_in_list = 1;

        for (; elem != NULL; index_in_list++) 
        {
            elem = list->data[index_in_list];
            //fprintf(exel_table, "%s\t", elem);
        }
        fprintf(exel_table, "%d\t", index_in_list - 1);
    }

    fclose(exel_table);
}
